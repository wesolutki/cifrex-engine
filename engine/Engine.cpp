#include "Engine.hpp"

#include "FileLoader.hpp"

#include <fstream>
#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>

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

Matches Engine::searchInFile(std::string const& data) const
{
    Matches matches;
    for (Vex const& vex : exs)
    {
        Matches const vexMatches = vex.match(data);
        matches.insert(matches.end(), vexMatches.begin(), vexMatches.end());
    }
    return matches;
}

FileMatches Engine::search(std::string const& inputPath, Extensions const& extensions) const
{
    FileMatches matches;
    if (ok())
    {
        for (string const& filePath : FileLoader::getFilePaths(inputPath, extensions))
        {
            ifstream file;
            //FileLoader::openFile(filePath, file);

            std::ifstream is(filePath);
            // Determine the file length
            is.seekg(0, std::ios_base::end);
            std::size_t size=is.tellg();
            is.seekg(0, std::ios_base::beg);
            // Create a vector to store the data
            std::string data;
            data.resize(size+1);
            // Load the data
            is.read((char*) &data[0], size);
            // Close the file
            is.close();

            //string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

            Matches const newMatches = searchInFile(data);
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
