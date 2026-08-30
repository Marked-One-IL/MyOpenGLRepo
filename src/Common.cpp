#include <Common.hpp>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <format>
#include <stb_image.h>
#include <cstdlib>

Common::RuntimeFailure::RuntimeFailure(const std::string &s) :
    std::runtime_error(s)
{
}
Common::RuntimeFailure::RuntimeFailure(const char *s) :
    std::runtime_error(s)
{
}

void Common::setup()
{
#ifndef READY_TO_DISTRIBUTE
    Common::clearScreen();
    std::filesystem::current_path(PROJECT_ROOT);
#endif
    stbi_set_flip_vertically_on_load(true);
}
void Common::clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
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