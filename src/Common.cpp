#include <Common.hpp>
#include <fstream>
#include <stdexcept>
#include <format>

Common::RuntimeFailure::RuntimeFailure(const std::string &s) :
    std::runtime_error(s)
{
}
Common::RuntimeFailure::RuntimeFailure(const char *s) :
    std::runtime_error(s)
{
}

std::string Common::readFile(std::filesystem::path filePath)
{
    std::string path = filePath.string();
    std::ifstream file(path.c_str());

    if (!file) {
        throw Common::RuntimeFailure("Could not open file '{}'", path);
    }

    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}