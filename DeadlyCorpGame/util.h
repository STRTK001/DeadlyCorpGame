//
// Created by Nic on 7/02/2024.
//

#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <vector>


namespace util
{
    /// \brief Transforms the specified string instance so that all characters are lowercase
    /// \param str String to be lowercased
    extern void lower(std::string &str);

    /// \brief Parses a non-negative integer from a string
    /// \param str The string to be parsed
    /// \return The parsed number, or a negative value if the parsing failed
    extern int parsePositiveInt(const std::string &str);

    /// \brief Splits `line` into strings separated by spaces. Puts the first argument into `line`, and all other
    ///        arguments in `args`.
    /// \param line Line to split. Will be set to the first argument after the function returns
    /// \param args List that will be populated with all arguments, starting from the second one (the first will be
    ///             available in `line`).
    ///
    /// Example
    /// @code
    /// std::string line("this is a test");
    /// std::vector<std::string> args;
    /// util::splitArguments(line, args);
    ///
    /// //`line` will contain "this"
    /// //`args` will contain ["is", "a", "test"]
    /// @endcode
    extern void splitArguments(std::string &line, std::vector<std::string> &args);
}



#endif //UTIL_H
