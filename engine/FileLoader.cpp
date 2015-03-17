#include "FileLoader.hpp"

#include <boost/filesystem.hpp>
#include <fstream>
#include <string>

using namespace std;
namespace fs = boost::filesystem;

bool FileLoader::openFile(string const& filename, std::ifstream & file)
{
    fs::file_type fileType = fs::status(fs::path(filename)).type();
    switch (fileType)
    {
    case fs::regular_file:
        //cout << "Opening regular file: " << filename << " ... ";
        file.open(filename.c_str());
        if (!file.is_open())
        {
            cout << "Failed!" << endl;
            return false;
        }
        //cout << "Success!" << endl;
        return true;
    case fs::directory_file:
        cout << "Path: " << filename << " points to directory! File path is needed!" << endl;
        break;
    case fs::file_not_found:
        cout << "Path: " << filename << " does not exist!" << endl;
        break;
    default:
        cout << "Path: " << filename << " status is strange!" << endl;
        break;
    }
    return false;
}

vector<string> FileLoader::getFilePaths(string const& path, vector<string> const& extensions)
{
    vector<string> results;
    fs::path boostPath(path);
    fs::recursive_directory_iterator itr(boostPath);
    while (itr != fs::recursive_directory_iterator())
    {
        string const& path = itr->path().string();
        string const& extension = fs::extension(itr->path());
        if (fs::regular_file == itr.status().type()
                && (extensions.empty() || extensions.cend() != std::find(extensions.cbegin(), extensions.cend(), extension)))
        {
            results.push_back(path);
        }
        ++itr;
    }
    return results;
}

bool FileLoader::exists(string const& path)
{
    return fs::status(fs::path(path)).type() != fs::file_not_found;
}
