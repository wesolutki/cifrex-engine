#include "Ex.hpp"

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

vector<string> Ex::match(string const& data) const
{
    std::vector<string> output;

    StringPiece input(data);

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
            output.push_back(strings[named.second-1]);
            cout << "Value for capturing group named " << named.first << " is " << strings[named.second-1] << endl;
        }
    }
    return std::move(output);
}
