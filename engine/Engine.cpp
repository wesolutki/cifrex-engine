#include "Engine.hpp"

#include "FileLoader.hpp"

#include <fstream>
#include <iostream>

using namespace std;

Engine::Engine()
{
}

Engine::Engine(EngineOptions const& options, std::vector<Vex> const& exs)
    : options(options)
    , exs(exs)
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
                if (options.verbose)
                    cout << "Searching file matches: " << filePath << endl;
                matches.emplace_back(filePath, newMatches);
                if (options.verbose)
                    for (Match const& match : newMatches)
                        cout << "\t[" << std::get<0>(match) << ", " << std::get<1>(match) << "] \t" << std::get<2>(match) << endl;
            }
        }
    }
    if (options.verbose)
        cout<<"Matches count: " << matches.size() << endl;
    return matches;
}
