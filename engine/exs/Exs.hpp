#pragma once

#include "Vex.hpp"
#include "Tex.hpp"
#include "Fex.hpp"

#include <vector>

class Exs
{
public:
    bool isVexs() const;
    bool match(std::string const& data);

    std::vector<Vex> vexs;
    std::vector<Tex> texs;
    std::vector<Fex> fexs;
};
