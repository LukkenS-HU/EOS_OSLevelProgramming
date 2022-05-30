//
// Created by stolij on 2022-05-18.
//

#ifndef HBO_TI_EOS_OLP_1_SYSCALLS_H
#define HBO_TI_EOS_OLP_1_SYSCALLS_H

#include <unistd.h>
#include <cstdint>

#include <vector>
#include <string>

namespace SysCalls
{
    ssize_t Read(int32_t fd, uint8_t *buf, size_t amount);
    ssize_t Read(int32_t fd, std::vector<uint8_t> &data);

    ssize_t FSeek(int32_t fd, off_t offset, int32_t pos);

    int32_t CreateFile(const std::string &path, mode_t mode);

    ssize_t Write(int32_t fileDescriptor, const uint8_t *buf, size_t amount);
    ssize_t Write(int32_t fileDescriptor, const std::vector<uint8_t> &data);
    ssize_t Write(int32_t fileDescriptor, const std::string &data);

    int32_t OpenFile(const std::string &path, int flags);
    int32_t OpenFile(const std::string &path, int flags, mode_t mode);

    int32_t Close(int32_t fileDescriptor);

    pid_t Fork();

    pid_t Wait(int *waitStatus);
    pid_t WaitPID(pid_t pid, int *waitStatus, int options);

    int32_t ExecVE(const std::string &path, const std::vector<std::string> &arguments = {}, const std::vector<std::string> &environmentVariables = {});
    pid_t GetPID();
    pid_t GetParentPID();

    int32_t Pipe(int32_t &readEnd, int32_t &writeEnd);
    int32_t Pipe(int32_t &readEnd, int32_t &writeEnd, int32_t flags);

    int32_t DuplicateDescriptor(int32_t oldDescriptor);
    int32_t DuplicateDescriptor(int32_t oldDescriptor, int32_t newDescriptor);
    int32_t DuplicateDescriptor(int32_t oldDescriptor, int32_t newDescriptor, int32_t flags);
}


#endif //HBO_TI_EOS_OLP_1_SYSCALLS_H
