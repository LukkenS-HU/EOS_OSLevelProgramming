#include <iostream>
#include <map>

#include <CLI/CLI.hpp>

static const constexpr char UPPERCASE_START = 'A';
static const constexpr char UPPERCASE_END = 'Z';

static const constexpr char LOWERCASE_START = 'a';
static const constexpr char LOWERCASE_END = 'z';

static const constexpr char UPPER_LOWER_DISTANCE = 0x20;
static const constexpr uint8_t ALPHABET_SIZE = 26;

static const std::map<char, uint8_t> AsciiToAlphabetMap = {
        { 'a', 0 },  { 'b', 1 },  { 'c', 2 },  { 'd', 3 },
        { 'e', 4 },  { 'f', 5 },  { 'g', 6 },  { 'h', 7 },
        { 'i', 8 },  { 'j', 9 }, { 'k', 10 }, { 'l', 11 },
        { 'm', 12 }, { 'n', 13 }, { 'o', 14 }, { 'p', 15 },
        { 'q', 16 }, { 'r', 17 }, { 's', 18 }, { 't', 19 },
        { 'u', 20 }, { 'v', 21 }, { 'w', 22 }, { 'x', 23 },
        { 'y', 24 }, { 'z', 25 }
};

static const std::map<uint8_t, char> AlphabetToAscii = {
        { 0, 'a' },  { 1, 'b' },  { 2, 'c' },  { 3, 'd' },
        { 4, 'e' },  { 5, 'f' },  { 6, 'g' },  { 7, 'h' },
        { 8, 'i' },  { 9, 'j' }, { 10, 'k' }, { 11, 'l' },
        { 12, 'm' }, { 13, 'n' }, { 14, 'o' }, { 15, 'p' },
        { 16, 'q' }, { 17, 'r' }, { 18, 's' }, { 19, 't' },
        { 20, 'u' }, { 21, 'v' }, { 22, 'w' }, { 23, 'x' },
        { 24, 'y' }, { 25, 'z' },
};

struct {
    std::string Input;
    int8_t RotationAmount = 3;
} Arguments;

static bool IsUpperCase(char input)
{
    return input >= UPPERCASE_START && input < UPPERCASE_END;
}

static bool IsLowerCase(char input)
{
    return input >= LOWERCASE_START && input <= LOWERCASE_END;
}

static bool ShouldRotateChar(char input)
{
    return IsUpperCase(input) || IsLowerCase(input);
}

static char ToUpper(char input)
{
    if (IsLowerCase(input))
        return input - UPPER_LOWER_DISTANCE;

    return input;
}

static char ToLower(char input)
{
    if (IsUpperCase(input))
        return input + UPPER_LOWER_DISTANCE;

    return input;
}

static char RotateChar(char input, int8_t amount)
{
    char inputLower = ToLower(input);
    if (!AsciiToAlphabetMap.contains(inputLower))
        return input;

    int16_t alphabetIndex = AsciiToAlphabetMap.at(inputLower);
    alphabetIndex = (alphabetIndex + amount) % ALPHABET_SIZE;
    if (alphabetIndex < 0)
        alphabetIndex += ALPHABET_SIZE;

    return AlphabetToAscii.at(alphabetIndex);
}

static void RotateInPlace(std::string &input, int8_t amount)
{
    for (auto &character : input)
        if (ShouldRotateChar(character))
            character = RotateChar(character, amount);
}

static std::string Rotate(std::string input, int8_t amount)
{
    RotateInPlace(input, amount);
    return input;
}

int main(int argc, char **argv)
{
    CLI::App app { "ROTx de/enciphering program" };
    app.add_option("-i,--input", Arguments.Input, "The input text to rotate, if this argument is not supplied, the input will be read from stdin.");
    app.add_option("-r,--rotation-amount", Arguments.RotationAmount, "The amount that the input should be shifted.");

    CLI11_PARSE(app, argc, argv)

    if (Arguments.Input.empty())
        std::getline(std::cin, Arguments.Input);

    std::cout << Rotate(Arguments.Input, Arguments.RotationAmount) << std::endl;
    return 0;
}
