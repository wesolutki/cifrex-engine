#include "Ex.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;
using namespace re2;

Ex::Ex()
{

}

Ex::Ex(string regex)
    : re(new RE2(regex))
{
    assert(re->ok());
    cout << re->pattern() << " loaded properly" << endl;
    for (pair<string, int> named : re->NamedCapturingGroups())
    {
        cout << "Capturing group named " << named.first << " was found" << endl;
    }
}

Matches Ex::match(string const& data) const
{
    Matches output;

    StringPiece input(data);
    const char* p = input.data();

    std::vector<string> strings(re->NumberOfCapturingGroups());
    RE2::Arg argv[3];
    const RE2::Arg* const args[3] = { &argv[0], &argv[1], &argv[2] };
    argv[0] = &strings[0];
    argv[1] = &strings[1];
    argv[2] = &strings[2];
    while (RE2::FindAndConsumeN(&input, *re, args, re->NumberOfCapturingGroups()))
    {
        for (pair<string, int> named : re->NamedCapturingGroups())
        {
            unsigned int const offset = (input.data() - p);
            unsigned int const lineNumber = 1 + std::count(data.begin(), (data.begin() + offset), '\n');
            output.emplace_back(lineNumber, offset, strings[named.second-1]);
            cout << "[" << lineNumber << ", " << offset << "] " << named.first << " -> " << strings[named.second-1] << endl;
        }
    }
    return std::move(output);
}
