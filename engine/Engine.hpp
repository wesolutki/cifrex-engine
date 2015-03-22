#pragma once

#include "Types.hpp"
#include "exs/Exs.hpp"

class Engine
{
public:
    Engine();
    Engine(std::vector<Vex> const& vexs);
    bool ok() const;
    Matches searchInString(std::string const& data) const;
    Matches searchInFile(std::string const& filePath) const;
    FileMatches search(std::string const& inputPath, Extensions const& extensions) const;

private:
    std::vector<Vex> exs;
};
