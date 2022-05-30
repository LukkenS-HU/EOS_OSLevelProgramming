//
// Created by stolij on 2022-05-18.
//

#ifndef HBO_TI_EOS_OLP_1_FILE_H
#define HBO_TI_EOS_OLP_1_FILE_H

#include <string>

#include <unistd.h>
#include <vector>

#include <fcntl.h>

class File
{
public:
    File(const std::string &path, int flags);
    File(const std::string &path, int flags, mode_t mode);

    ~File();

    File(const File &) = delete;
    File &operator=(const File &) = delete;

    ssize_t FTell();
    size_t GetSize();

    ssize_t FSeek(ssize_t offset, off_t seekDir);

    std::streamsize ReadBytes(std::vector<uint8_t> &output);
    std::streamsize WriteBytes(const std::vector<uint8_t> &bytes);

    std::string ReadLine();
    std::streamsize WriteLine(const std::string &line);

private:
    int32_t _fileDescriptor = -1;

    void ValidateFileDescriptor();
    bool IsValid();
};


#endif //HBO_TI_EOS_OLP_1_FILE_H
