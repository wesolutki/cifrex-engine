#pragma once

#include "Types.hpp"
#include "exs/Exs.hpp"

struct EngineOptions
{
    EngineOptions(bool verbose = false) : verbose(verbose){}

    bool verbose;
};

class Engine
{
public:
    Engine();
    Engine(EngineOptions const& options, std::vector<Vex> const& vexs);
    bool ok() const;
    Matches searchInString(std::string const& data) const;
    Matches searchInFile(std::string const& filePath) const;
    FileMatches search(std::string const& inputPath, Extensions const& extensions) const;

private:
    EngineOptions options;
    std::vector<Vex> exs;
};
