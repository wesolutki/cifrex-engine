#pragma once

#include "Types.hpp"

#include <memory>
#include <re2/re2.h>

class Ex
{
public:
    Ex();
    Ex(std::string regex);

    RegexMatches match(std::string const& data) const;

private:
    std::shared_ptr<re2::RE2> re;
};
