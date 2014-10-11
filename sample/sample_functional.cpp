#include "../functional.h"
#include "../stringlib.h"
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>

int main() {
    std::vector<std::string> source = {"a?", "ab?", "abc?", "abcd?"};
    util::print(source); // {a?,ab?,abc?,abcd?}

    {
        auto output = util::map(source,
            [](const std::string& str) { return str.substr(0, str.size() - 1); });
        util::print(output); // {a,ab,abc,abcd}
    }

    {
        auto output = util::map(source, &std::string::size);
        util::print(output); // {2,3,4,5}
    }
    {
        std::map<std::string, int> src_map = {{"RED", 0}, {"GREEN", 1}, {"BLUE", 2}};
        util::print(src_map);
        auto result_map = util::map(src_map,
            [](const std::pair<std::string, int>& pair) {
                return std::make_pair(util::to_lower(pair.first), pair.second);
            });
        util::print(result_map);
    }
    {
        std::unordered_map<std::string, int> src_map = {{"RED", 0}, {"GREEN", 1}, {"BLUE", 2}};
        util::print(src_map);
        auto result_map = util::map(src_map,
            [](const std::pair<std::string, int>& pair) {
                return std::make_pair(util::to_lower(pair.first), pair.second);
            });
        util::print(result_map);
    }

    {
        std::unordered_map<std::string, int> src_map = {{"RED", 0}, {"GREEN", 1}, {"BLUE", 2}};
        util::print(src_map);
        auto result = util::map(src_map,
            [](const std::pair<std::string, int>& pair) {
                return pair.first + ": " + util::to_string(pair.second);
            });
        std::list<std::string> result_list = util::map(src_map,
            [](const std::pair<std::string, int>& pair) {
                return pair.first + ": " + util::to_string(pair.second);
            });
        util::print(result);
    }


    // g++ -std=c++1y sample_functional.cpp
}
