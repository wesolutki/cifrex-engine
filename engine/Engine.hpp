#pragma once

#include "Types.hpp"
#include "exs/Exs.hpp"

class Engine
{
public:
    Engine();
    Engine(std::vector<Vex> const& vexs);
    bool ok() const;
    RegexMatches searchInFile(std::string const& data) const;
    Matches search(std::string const& inputPath, Extensions const& extensions) const;

private:
    std::vector<Vex> exs;
};
