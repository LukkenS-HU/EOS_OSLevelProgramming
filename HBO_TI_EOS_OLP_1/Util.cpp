//
// Created by stolij on 2022-05-19.
//

#include "Util.h"

namespace Util
{
    std::string GetLine(int32_t fileDescriptor)
    {
        char input;
        std::string result;

        while (SysCalls::Read(fileDescriptor, (uint8_t *) &input, sizeof(input)) > 0 && input != EOF && input != '\n')
            result += input;

        return result;
    }

    pid_t Exec(const std::vector<std::string> &arguments, int32_t stdinDescriptor, int32_t stdoutDescriptor, const std::vector<std::string> &environmentVariables)
    {
        pid_t childPid = SysCalls::Fork();
        if (childPid == 0)
        {
            if (stdinDescriptor != STDIN_FILENO)
                SysCalls::DuplicateDescriptor(stdinDescriptor, STDIN_FILENO);

            if (stdoutDescriptor != STDOUT_FILENO)
                SysCalls::DuplicateDescriptor(stdoutDescriptor, STDOUT_FILENO);

            SysCalls::ExecVE(arguments[0], arguments, environmentVariables);
        }

        return childPid;
    }

    void ExecWait(const std::vector<std::string> &arguments, int32_t stdinDescriptor, int32_t stdoutDescriptor, const std::vector<std::string> &environmentVariables)
    {
        pid_t pid = Exec(arguments, stdinDescriptor, stdoutDescriptor, environmentVariables);
        if (pid != 0)
            WaitForProcess(pid);
    }

    void WaitForProcess(pid_t process)
    {
        while (SysCalls::WaitPID(process, nullptr, 0) != -1);

        // This seems a bit hacky, but for some reason, the 'Wait' SysCall does not actually wait long enough
        // for the executed process to actually flush its buffer to the stdout, causing the shell prompt to appear
        // before the exec output.
        usleep(10'000);
    }
}