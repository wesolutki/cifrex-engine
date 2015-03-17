#include <vector>
#include <string>
#include <tuple>

using RegexMatches = std::vector<std::string>;

using Match = std::tuple<std::string, std::string>;
using Matches= std::vector<Match>;

using Extensions = std::vector<std::string, std::allocator<std::string>>;

using Files = std::vector<std::string>;
