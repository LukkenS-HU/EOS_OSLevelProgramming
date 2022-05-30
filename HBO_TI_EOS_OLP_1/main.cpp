#include "Config.h"
#include "File.h"
#include "Util.h"
#include "SysCalls.h"

#include <map>
#include <functional>
#include <optional>

#include <fmt/format.h>

typedef std::function<int32_t()> CommandHandler_t;

static int32_t HandleNewFileCommand();
static int32_t HandleLSCommand();
static int32_t HandleFindCommand();
static int32_t HandleSeekTestCommand();

[[noreturn]]
static int32_t HandleExitCommand();

std::map<std::string, CommandHandler_t> _commandsMap = {
        { "new_file", HandleNewFileCommand },
        { "ls", HandleLSCommand },
        { "find", HandleFindCommand },
        { "seekTest", HandleSeekTestCommand },
        { "exit", HandleExitCommand }
};

struct {
    std::string Prompt;
} Configuration;

static int32_t LastErrorCode = 0;

static inline void WriteToStdOut(const std::string &text)
{
    SysCalls::Write(STDOUT_FILENO, text);
}

static inline void WriteLineToStdOut(const std::string &text)
{
    WriteToStdOut(text);
    WriteToStdOut("\n");
}

static std::string RequestInput(std::optional<std::string> prompt)
{
    if (prompt)
        WriteToStdOut(*prompt);

    return Util::GetLine(STDIN_FILENO);
}

static void LoadPrompt()
{
    File rcFile(RC_PATH, O_RDONLY);
    Configuration.Prompt = rcFile.ReadLine();
}

[[noreturn]]
int main()
{
    LoadPrompt();

    std::string input;
    while (true)
    {
        input = RequestInput(Configuration.Prompt);
        if (_commandsMap.contains(input))
            LastErrorCode = _commandsMap.at(input)();
        else
            WriteLineToStdOut(fmt::format(COMMAND_NOT_FOUND_MESSAGE, input));
    }
}

static int32_t HandleNewFileCommand()
{
    std::string text = RequestInput("Vul een tekst in: ");
    if (text.empty())
        return -1;

    std::string fileName = RequestInput("Vul een bestandsnaam/pad in: ");
    if (fileName.empty())
        return -2;

    File outputFile(fileName, O_CREAT | O_RDWR);
    outputFile.WriteLine(text);

    return 0;
}

static int32_t HandleLSCommand()
{
    Util::ExecWait({"/usr/bin/ls"}, STDIN_FILENO, STDOUT_FILENO);
    return 0;
}

static int32_t HandleFindCommand()
{
    int32_t inputPipe;
    int32_t outputPipe;
    SysCalls::Pipe(inputPipe, outputPipe);

    std::string searchText = RequestInput("Tekst om te zoeken: ");
    if (searchText.empty())
        return -1;

    Util::Exec({"/usr/bin/find", "."}, STDIN_FILENO, outputPipe);
    Util::ExecWait({"/usr/bin/grep", searchText}, inputPipe, STDOUT_FILENO);

    SysCalls::Close(inputPipe);
    SysCalls::Close(outputPipe);
}

static int32_t HandleSeekTestCommand()
{
    std::vector<uint8_t> xVector = {'x'};

    {
        File seekFile("seek", O_CREAT | O_RDWR);

        seekFile.WriteBytes(xVector);
        seekFile.FSeek(SEEK_TEST_FILE_SIZE - 2, SEEK_CUR);
        seekFile.WriteBytes(xVector);
    }

    {
        File loopFile("loop", O_CREAT | O_RDWR);

        loopFile.WriteBytes(xVector);

        std::vector<uint8_t> nullByteVector = {'\0'};
        for (size_t i = 0; i < SEEK_TEST_FILE_SIZE - 2; i++)
            loopFile.WriteBytes(nullByteVector);

        loopFile.WriteBytes(xVector);
    }

    return 0;
}

[[noreturn]]
static int32_t HandleExitCommand()
{
    exit(0);
}