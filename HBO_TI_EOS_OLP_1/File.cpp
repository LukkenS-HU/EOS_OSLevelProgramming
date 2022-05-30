//
// Created by stolij on 2022-05-18.
//

#include "File.h"
#include "Util.h"

#include "SysCalls.h"

#include <stdexcept>

File::File(const std::string &path, int flags)
{
    _fileDescriptor = SysCalls::OpenFile(path, flags);
    ValidateFileDescriptor();
}

File::File(const std::string &path, int flags, mode_t mode)
{
    _fileDescriptor = SysCalls::OpenFile(path, flags, mode);
    ValidateFileDescriptor();
}

File::~File()
{
    SysCalls::Close(_fileDescriptor);
}

size_t File::GetSize()
{
    ssize_t currentOffset = FTell();
    size_t end = FSeek(0, SEEK_END);
    FSeek(currentOffset, SEEK_SET);

    return end;
}

ssize_t File::FTell()
{
    return FSeek(0, SEEK_SET);
}

ssize_t File::FSeek(ssize_t offset, off_t seekDir)
{
    return SysCalls::FSeek(_fileDescriptor, offset, seekDir);
}

std::streamsize File::WriteBytes(const std::vector<uint8_t> &bytes)
{
    return SysCalls::Write(_fileDescriptor, bytes.data(), bytes.size());
}

std::streamsize File::ReadBytes(std::vector<uint8_t> &output)
{
    return SysCalls::Read(_fileDescriptor, output.data(), output.size());
}

void File::ValidateFileDescriptor()
{
    if (!IsValid())
        throw std::runtime_error("An error occurred when trying to open the file.");
}

bool File::IsValid()
{
    return _fileDescriptor > 0;
}

std::string File::ReadLine()
{
    return Util::GetLine(_fileDescriptor);
}

std::streamsize File::WriteLine(const std::string &line)
{
    return SysCalls::Write(_fileDescriptor, (uint8_t *)line.data(), line.size());
}
