#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cctype>

// custom regex for checking naming conventions
bool isCamelCase(const std::string &str) { return std::regex_match(str, std::regex("^[a-z][a-zA-Z0-9]*$")); }
bool isPascalCase(const std::string &str) { return std::regex_match(str, std::regex("^[A-Z][a-zA-Z0-9]*$")); }
bool isAllCaps(const std::string &str) { return std::regex_match(str, std::regex("^[A-Z][A-Z0-9_]*$")); }

std::pair<int, int> checkConstants(const std::string &content)
{
    int total = 0, incorrect = 0;
    std::regex constRegex(R"(\bconst\s+(?:int|float|double|char|bool|long|short|unsigned|signed)\s+([a-zA-Z_]\w*)\b)");
    auto matches = std::sregex_iterator(content.begin(), content.end(), constRegex);
    auto end = std::sregex_iterator();

    for (auto i = matches; i != end; ++i)
    {
        std::smatch match = *i;
        total++;
        std::string name = match[1];
        if (!isAllCaps(name))
        {
            std::cout << "Bad constant name: " << name << " (should be ALL_CAPS)" << std::endl;
            incorrect++;
        }
    }
    return {total, incorrect};
}

std::pair<int, int> checkVariables(const std::string &content)
{
    int total = 0, incorrect = 0;
    std::regex varRegex(R"(\b(?:int|float|double|char|bool|long|short|unsigned|signed)\s+([a-zA-Z_]\w*)\b)");
    auto matches = std::sregex_iterator(content.begin(), content.end(), varRegex);
    auto end = std::sregex_iterator();

    for (auto i = matches; i != end; ++i)
    {
        std::smatch match = *i;
        total++;
        std::string name = match[1];
        if (!isCamelCase(name))
        {
            std::cout << "Bad variable name: " << name << " (should be camelCase)" << std::endl;
            incorrect++;
        }
    }
    return {total, incorrect};
}

std::pair<int, int> checkClasses(const std::string &content)
{
    int total = 0, incorrect = 0;
    std::regex classRegex(R"(\bclass\s+([a-zA-Z_]\w*)\b)");
    auto matches = std::sregex_iterator(content.begin(), content.end(), classRegex);
    auto end = std::sregex_iterator();

    for (auto i = matches; i != end; ++i)
    {
        std::smatch match = *i;
        total++;
        std::string name = match[1];
        if (!isPascalCase(name))
        {
            std::cout << "Bad class name: " << name << " (should be PascalCase)" << std::endl;
            incorrect++;
        }
    }
    return {total, incorrect};
}

std::pair<int, int> checkFunctions(const std::string &content)
{
    int total = 0, incorrect = 0;
    std::regex funcRegex(R"(\b(?:void|int|float|double|char|bool|long|short|unsigned|signed)\s+([a-zA-Z_]\w*)\s*\()");
    auto matches = std::sregex_iterator(content.begin(), content.end(), funcRegex);
    auto end = std::sregex_iterator();

    for (auto i = matches; i != end; ++i)
    {
        std::smatch match = *i;
        total++;
        std::string name = match[1];
        if (!isCamelCase(name))
        {
            std::cout << "Incorrect function name: " << name << std::endl;
            incorrect++;
        }
    }
    return {total, incorrect};
}

double calculateScore(int totalIdentifiers, int incorrectIdentifiers)
{
    return 100.0 * (totalIdentifiers - incorrectIdentifiers) / totalIdentifiers;
}

int processFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return 1;
    }

    std::cout << std::endl
              << "LintLord is evaluating " << filename << std::endl
              << std::endl;

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    auto [totalConstants, incorrectConstants] = checkConstants(content);
    auto [totalVariables, incorrectVariables] = checkVariables(content);
    auto [totalClasses, incorrectClasses] = checkClasses(content);
    auto [totalFunctions, incorrectFunctions] = checkFunctions(content);

    int totalIdentifiers = totalConstants + totalVariables + totalClasses + totalFunctions;
    int incorrectIdentifiers = incorrectConstants + incorrectVariables + incorrectClasses + incorrectFunctions;

    double score = calculateScore(totalIdentifiers, incorrectIdentifiers);
    std::cout << "LintLord's approval: " << score << "%" << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    return processFile(argv[1]);
}