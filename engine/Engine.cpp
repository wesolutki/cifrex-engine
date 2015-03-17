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

Matches Engine::search(std::string const& inputPath, Extensions const& extensions) const
{
    Matches matches;
    if (ok())
    {
        for (string const& filePath : FileLoader::getFilePaths(inputPath, extensions))
        {
            cout << filePath << endl;
            ifstream file;
            FileLoader::openFile(filePath, file);
            string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

            for (Vex const& vex : exs)
            {
                RegexMatches const vexMatches = vex.match(data);
                for (string const& match : vexMatches)
                {
                    matches.emplace_back(filePath, match);
                }
            }
        }
    }
    cout<<"Matches count: " << matches.size() << endl;
    return matches;
}
