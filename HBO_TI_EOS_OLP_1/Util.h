//
// Created by stolij on 2022-05-19.
//

#ifndef HBO_TI_EOS_OLP_1_UTIL_H
#define HBO_TI_EOS_OLP_1_UTIL_H

#include "SysCalls.h"

#include <string>
#include <cstdint>

namespace Util
{
    std::string GetLine(int32_t fileDescriptor);

    pid_t Exec(const std::vector<std::string> &arguments, int32_t stdinDescriptor = STDIN_FILENO, int32_t stdoutDescriptor = STDOUT_FILENO, const std::vector<std::string> &environmentVariables = {});
    void ExecWait(const std::vector<std::string> &arguments, int32_t stdinDescriptor = STDIN_FILENO, int32_t stdoutDescriptor = STDOUT_FILENO, const std::vector<std::string> &environmentVariables = {});
    void WaitForProcess(pid_t process);
}

#endif //HBO_TI_EOS_OLP_1_UTIL_H
