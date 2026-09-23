#include "cli_parser.hpp"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstddef>

namespace
{
std::string trim(const std::string &value)
{
    const std::size_t first = value.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
    {
        return std::string();
    }

    const std::size_t last = value.find_last_not_of(" \t\n\r");
    return value.substr(first, last - first + 1U);
}

bool parseVector(const char *argument, std::vector<double> &values,
                 std::string &errorMessage)
{
    const std::string text(argument == nullptr ? "" : argument);
    if (text.size() < 2U || text.front() != '[' || text.back() != ']')
    {
        errorMessage = "coefficient vector must use [value,value] syntax";
        return false;
    }

    const std::string body = text.substr(1U, text.size() - 2U);
    if (trim(body).empty())
    {
        errorMessage = "coefficient vector must not be empty";
        return false;
    }

    std::size_t start = 0U;
    while (start <= body.size())
    {
        const std::size_t separator = body.find(',', start);
        const std::size_t length = separator == std::string::npos
                                       ? body.size() - start
                                       : separator - start;
        const std::string token = trim(body.substr(start, length));
        if (token.empty())
        {
            errorMessage = "coefficient vector contains an empty value";
            return false;
        }

        char *end = nullptr;
        errno = 0;
        const double value = std::strtod(token.c_str(), &end);
        if (end == token.c_str() || *end != '\0' || errno == ERANGE ||
            !std::isfinite(value))
        {
            errorMessage = "coefficient vector contains an invalid value";
            return false;
        }
        values.push_back(value);

        if (separator == std::string::npos)
        {
            break;
        }
        start = separator + 1U;
    }

    return true;
}

bool hasNonZeroCoefficient(const std::vector<double> &values)
{
    for (const double value : values)
    {
        if (value != 0.0)
        {
            return true;
        }
    }
    return false;
}
}

bool parseCommandLine(int argc, char *argv[], ParsedInput &input,
                      std::string &errorMessage)
{
    input = ParsedInput();
    errorMessage.clear();

    if (argc != 3 || argv == nullptr)
    {
        errorMessage = "expected numerator and denominator coefficient vectors";
        return false;
    }

    if (!parseVector(argv[1], input.numerator, errorMessage) ||
        !parseVector(argv[2], input.denominator, errorMessage))
    {
        return false;
    }

    if (!hasNonZeroCoefficient(input.denominator))
    {
        errorMessage = "denominator must contain a non-zero coefficient";
        return false;
    }

    return true;
}
