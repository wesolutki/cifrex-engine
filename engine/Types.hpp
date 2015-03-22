#include <vector>
#include <string>
#include <tuple>

using FileContent = std::string;

using Match = std::tuple<unsigned int, unsigned int, std::string>;
using Matches = std::vector<Match>;
using FileMatch = std::tuple<std::string, Matches>;
using FileMatches = std::vector<FileMatch>;

using Extensions = std::vector<std::string, std::allocator<std::string>>;

using Files = std::vector<std::string>;
