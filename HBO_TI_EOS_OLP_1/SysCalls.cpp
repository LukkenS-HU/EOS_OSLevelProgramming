//
// Created by stolij on 2022-05-18.
//

#include "SysCalls.h"

#include <sys/syscall.h>


namespace SysCalls
{
    ssize_t Read(int32_t fd, uint8_t *buf, size_t amount)
    {
        return syscall(SYS_read, fd, buf, amount);
    }

    ssize_t Read(int32_t fd, std::vector<uint8_t> &data)
    {
        return Read(fd, data.data(), data.size());
    }

    ssize_t FSeek(int32_t fd, off_t offset, int32_t pos)
    {
        return syscall(SYS_lseek, fd, offset, pos);
    }

    int32_t CreateFile(const std::string &path, mode_t mode)
    {
        return syscall(SYS_creat, path.c_str(), mode);
    }

    ssize_t Write(int32_t fileDescriptor, const uint8_t *buf, size_t amount)
    {
        return syscall(SYS_write, fileDescriptor, buf, amount);
    }

    ssize_t Write(int32_t fileDescriptor, const std::vector<uint8_t> &data)
    {
        return Write(fileDescriptor, data.data(), data.size());
    }

    ssize_t Write(int32_t fileDescriptor, const std::string &data)
    {
        return Write(fileDescriptor, (uint8_t *)data.data(), data.size());
    }

    int32_t OpenFile(const std::string &path, int flags)
    {
        return syscall(SYS_open, path.c_str(), flags);
    }

    int32_t OpenFile(const std::string &path, int flags, mode_t mode)
    {
        return syscall(SYS_open, path.c_str(), flags, mode);
    }

    int32_t Close(int32_t fileDescriptor)
    {
        return syscall(SYS_close, fileDescriptor);
    }

    pid_t Fork()
    {
        return syscall(SYS_fork);
    }

    pid_t Wait(int *waitStatus)
    {
        return syscall(SYS_wait4, waitStatus);
    }

    pid_t WaitPID(pid_t pid, int *waitStatus, int options)
    {
        return syscall(SYS_waitid, pid, waitStatus, options);
    }

    int32_t ExecVE(const std::string &path, const std::vector<std::string> &arguments, const std::vector<std::string> &environmentVariables)
    {
        std::vector<const char *> argumentCStrs;
        std::vector<const char *> environmentVariableCStrs;

        for (auto &argument : arguments)
            argumentCStrs.emplace_back(argument.c_str());

        for (auto &environmentVariable : environmentVariables)
            environmentVariableCStrs.emplace_back(environmentVariable.c_str());

        const char **sysCallArguments = argumentCStrs.empty() ? nullptr : argumentCStrs.data();
        const char **sysCallEnvironmentVariables = environmentVariableCStrs.empty() ? nullptr : environmentVariableCStrs.data();

        return syscall(SYS_execve, path.c_str(), sysCallArguments, sysCallEnvironmentVariables);
    }

    pid_t GetPID()
    {
        return syscall(SYS_getpid);
    }

    pid_t GetParentPID()
    {
        return syscall(SYS_getppid);
    }

    int32_t Pipe(int32_t &readEnd, int32_t &writeEnd)
    {
        int32_t fileDescriptors[2];
        int32_t result = syscall(SYS_pipe, fileDescriptors);
        if (result != 0)
            return result;

        readEnd = fileDescriptors[0];
        writeEnd = fileDescriptors[1];

        return result;
    }

    int32_t Pipe(int32_t &readEnd, int32_t &writeEnd, int32_t flags)
    {
        int32_t fileDescriptors[2];
        int32_t result = syscall(SYS_pipe2, fileDescriptors, flags);
        if (result != 0)
            return result;

        readEnd = fileDescriptors[0];
        writeEnd = fileDescriptors[1];

        return result;
    }

    int32_t DuplicateDescriptor(int32_t oldDescriptor)
    {
        return syscall(SYS_dup, oldDescriptor);
    }

    int32_t DuplicateDescriptor(int32_t oldDescriptor, int32_t newDescriptor)
    {
        return syscall(SYS_dup2, oldDescriptor, newDescriptor);
    }

    int32_t DuplicateDescriptor(int32_t oldDescriptor, int32_t newDescriptor, int32_t flags)
    {
        return syscall(SYS_dup3, oldDescriptor, newDescriptor, flags);
    }
}