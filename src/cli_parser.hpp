#ifndef CLI_PARSER_HPP
#define CLI_PARSER_HPP

#include <string>
#include <vector>

struct ParsedInput
{
    std::vector<double> numerator;
    std::vector<double> denominator;
};

bool parseCommandLine(int argc, char *argv[], ParsedInput &input,
                      std::string &errorMessage);

#endif
