#pragma once

#include <string>
#include <vector>

class FileLoader
{
public:
    static bool openFile(std::string const& filename, std::ifstream & file);
    static std::vector<std::string> getFilePaths(std::string const& path, std::vector<std::string> const& extensions);
    static bool exists(std::string const& path);
};
