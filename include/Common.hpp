#pragma once
#include <string>
#include <filesystem>

namespace Common
{
    std::string readFile(std::filesystem::path filePath);
}