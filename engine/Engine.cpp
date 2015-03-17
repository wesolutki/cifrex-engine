#include "Engine.hpp"

#include "FileLoader.hpp"

#include <string>
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

vector<string> Engine::search(std::string const& inputPath, std::vector<std::string> const& extensions) const
{
    vector<string> matches;
    if (ok())
    {
        for (string const& filePath : FileLoader::getFilePaths(inputPath, extensions))
        {
            ifstream file;
            FileLoader::openFile(filePath, file);
            string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

            for (Vex const& vex : exs)
            {
                vector<string> const vexMatches = vex.match(data);
                for (string const& v : vexMatches)
                    matches.push_back(v);
            }
        }
    }
    cout<<"matches count: " << matches.size() << endl;
    return matches;
}
