#pragma once

#include "Types.hpp"

class FileLoader
{
public:
    static bool openFile(std::string const& filename, std::ifstream & file);
    static FileContent loadFile(std::ifstream & file);
    static Files getFilePaths(std::string const& path, Extensions const& extensions);
    static bool exists(std::string const& path);
};
