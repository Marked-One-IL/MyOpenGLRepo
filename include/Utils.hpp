#pragma once
#include <format>
#include <string>
#include <filesystem>
#include <stdexcept>
#include <cassert>

// std::optional         - Recoverable and possible error.
// Utils::RuntimeFailure - Unrecoverable but possible error.
// assert                - Unrecoverable and impossible error.

class Utils
{
public:
    Utils(void) = delete;

    static void initializeRuntime (void);

    class RuntimeFailure : public std::runtime_error
    {
    public:
        template <typename... Args>
        RuntimeFailure(std::format_string<Args...> fmt, Args&&... args);

        RuntimeFailure(const std::string &s);
        RuntimeFailure(const char *s);
    };

    static std::string readFile(std::filesystem::path filePath);
};

template <typename... Args>
inline Utils::RuntimeFailure::RuntimeFailure(std::format_string<Args...> fmt, Args&&... args) :
    std::runtime_error(std::format(fmt, std::forward<Args>(args)...))
{
}