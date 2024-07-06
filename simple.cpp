#include <iostream>
#include <fstream>
#include <string>
#include <regex>

// custom regex for checking naming conventions
bool isCamelCase(const std::string &str) { return std::regex_match(str, std::regex("^[a-z][a-zA-Z0-9]*$")); }
bool isPascalCase(const std::string &str) { return std::regex_match(str, std::regex("^[A-Z][a-zA-Z0-9]*$")); }
bool isAllCaps(const std::string &str) { return std::regex_match(str, std::regex("^[A-Z][A-Z0-9_]*$")); }

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return 1;
    }

    std::cout << std::endl
              << "LintLord is evaluating " << filename << std::endl
              << std::endl;

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    int totalIdentifiers = 0;
    int incorrectIdentifiers = 0;

    std::regex varConstRegex(R"(\b(const\s+)?(?:int|float|double|char|bool|long|short|unsigned|signed)\s+([a-zA-Z_]\w*)\b)");
    auto varConstMatches = std::sregex_iterator(content.begin(), content.end(), varConstRegex);
    auto end = std::sregex_iterator();

    // Check constants
    std::regex constRegex(R"(\bconst\s+(?:int|float|double|char|bool|long|short|unsigned|signed)\s+([a-zA-Z_]\w*)\b)");
    auto constMatches = std::sregex_iterator(content.begin(), content.end(), constRegex);

    for (std::sregex_iterator i = constMatches; i != end; ++i)
    {
        std::smatch match = *i;
        totalIdentifiers++;
        std::string name = match[1];
        if (!isAllCaps(name))
        {
            std::cout << "Incorrect constant name: " << name << " (should be ALL_CAPS)" << std::endl;
            incorrectIdentifiers++;
        }
    }

    // Check variables
    std::regex varRegex(R"(\b(?:int|float|double|char|bool|long|short|unsigned|signed)\s+([a-zA-Z_]\w*)\b)");
    auto varMatches = std::sregex_iterator(content.begin(), content.end(), varRegex);

    for (std::sregex_iterator i = varMatches; i != end; ++i)
    {
        std::smatch match = *i;
        totalIdentifiers++;
        std::string name = match[1];
        if (!isCamelCase(name))
        {
            std::cout << "Incorrect variable name: " << name << " (should be camelCase)" << std::endl;
            incorrectIdentifiers++;
        }
    }

    std::regex classRegex(R"(\bclass\s+([a-zA-Z_]\w*)\b)");
    auto classMatches = std::sregex_iterator(content.begin(), content.end(), classRegex);

    for (std::sregex_iterator i = classMatches; i != end; ++i)
    {
        std::smatch match = *i;
        totalIdentifiers++;
        std::string name = match[1];
        if (!isPascalCase(name))
        {
            std::cout << "Bad class name: " << name << " (should be PascalCase)" << std::endl;
            incorrectIdentifiers++;
        }
    }

    std::regex funcRegex(R"(\b(?:void|int|float|double|char|bool|long|short|unsigned|signed)\s+([a-zA-Z_]\w*)\s*\()");
    auto funcMatches = std::sregex_iterator(content.begin(), content.end(), funcRegex);

    for (std::sregex_iterator i = funcMatches; i != end; ++i)
    {
        std::smatch match = *i;
        totalIdentifiers++;
        std::string name = match[1];
        if (!isCamelCase(name))
        {
            std::cout << "Incorrect function name: " << name << std::endl;
            incorrectIdentifiers++;
        }
    }

    // std::cout << "Total identifiers: " << totalIdentifiers << std::endl;
    // std::cout << "Incorrect identifiers: " << incorrectIdentifiers << std::endl;

    double score = 100.0 * (totalIdentifiers - incorrectIdentifiers) / totalIdentifiers;
    std::cout << "LintLord's approval: " << score << "%" << std::endl;

    return 0;
}