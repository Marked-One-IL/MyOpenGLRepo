#include <Common.hpp>
#include <fstream>
#include <stdexcept>
#include <format>

std::string Common::readFile(std::filesystem::path filePath)
{
    std::string path = filePath.string();
    std::ifstream file(path.c_str());

    if (!file) {
        throw std::runtime_error(std::format("Could not open file '{}'", path));
    }

    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}