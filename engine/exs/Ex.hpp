#pragma once

#include <memory>
#include <string>
#include <vector>

#include <re2/re2.h>

class Ex
{
public:
    Ex();
    Ex(std::string regex);

    std::vector<std::string> match(std::string const& data) const;

private:
    std::shared_ptr<re2::RE2> re;
};
