#include "Engine.hpp"

#include "FileLoader.hpp"

#include <fstream>
#include <iostream>

using namespace std;

Engine::Engine()
{
}

Engine::Engine(std::vector<Vex> const& exs)
    : exs(exs)
{
}

bool Engine::ok() const
{
    return !exs.empty();
}

Matches Engine::searchInString(std::string const& data) const
{
    Matches matches;
    for (Vex const& vex : exs)
    {
        Matches const vexMatches = vex.match(data);
        matches.insert(matches.end(), vexMatches.begin(), vexMatches.end());
    }
    return matches;
}

Matches Engine::searchInFile(std::string const& filePath) const
{
    ifstream file;
    FileLoader::openFile(filePath, file);
    return searchInString(FileLoader::loadFile(file));
}

FileMatches Engine::search(std::string const& inputPath, Extensions const& extensions) const
{
    FileMatches matches;
    if (ok())
    {
        for (string const& filePath : FileLoader::getFilePaths(inputPath, extensions))
        {
            Matches const newMatches = searchInFile(filePath);
            if (!newMatches.empty())
            {
                cout << filePath << endl;
                matches.emplace_back(filePath, newMatches);
            }
        }
    }
    cout<<"Matches count: " << matches.size() << endl;
    return matches;
}
