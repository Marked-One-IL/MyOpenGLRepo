#pragma once
#include <iostream>
#include <format>
#include <string>
#include <filesystem>
#include <stdexcept>
#include <cassert>

// std::optional - Recoverable error but possible (Eg: socket closed).
// Common::RuntimeFailure - Unrecoverable error but possible (Eg: shader file is not found).
// LOGICAL_FAILURE - Unrecoverable error but impossible (Eg: index >= v.size()).

#ifndef NDEBUG
#define LOGICAL_FAILURE(expression, ...) \
do { \
    if (!(expression)) { \
        std::cerr << "\nExpression: " << #expression << '\n'; \
        std::cerr << "Message: " << std::format(__VA_ARGS__) << '\n'; \
        assert(false); \
    } \
} while (false)
#else
#define LOGICAL_FAILURE(expression, ...) \
do { } while (false)
#endif

namespace Common
{
    class RuntimeFailure : public std::runtime_error
    {
    public:
        template <typename... Args>
        RuntimeFailure(std::format_string<Args...> fmt, Args&&... args);

        RuntimeFailure(const std::string &s);
        RuntimeFailure(const char *s);
    };

    std::string readFile(std::filesystem::path filePath);
    void clearScreen(void);
}

template <typename... Args>
inline Common::RuntimeFailure::RuntimeFailure(std::format_string<Args...> fmt, Args&&... args) :
    std::runtime_error(std::format(fmt, std::forward<Args>(args)...))
{
}