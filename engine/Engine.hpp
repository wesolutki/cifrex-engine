#pragma once

#include "exs/Exs.hpp"

#include <string>
#include <vector>

class Engine
{
public:
    Engine();
    Engine(std::vector<Vex> const& vexs);
    bool ok() const;
    std::vector<std::string> search(std::string const& inputPath, std::vector<std::string> const& extensions) const;

private:
    std::vector<Vex> exs;
};
