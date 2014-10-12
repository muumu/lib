#include "../functional.h"
#include "../stringlib.h"
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;
using namespace util;

int main() {

    {
        vector<string> source = {"a?", "ab?", "abc?", "abcd?"};
        auto output = util::map(source, &util::init);
        print(output); // {"a","ab","abc","abcd"}
    }
    {
        list<string> source = {"", "a", "", "ab"};
        auto output = util::map(source, &string::empty);
        print(output); // {true,false,true,false}
    }

    {
        set<string> source = {"a?", "ab?", "ac?", "abcd?"};
        auto output = util::map(source, &string::size);
        print(output); // {2,3,5}
    }
    {
        multiset<string> source = {"a?", "ab?", "ac?", "abcd?"};
        auto output = util::map(source, &string::size);
        print(output); // {2,3,3,5}
    }
    {
        std::map<string, int> source = {{"RED", 0}, {"GREEN", 1}, {"BLUE", 2}};
        auto result = util::map(source,
            [](const pair<string, int>& pair) {
                return make_pair(util::lower(pair.first), pair.second);
            });
        print(result); // {{"blue",2},{"green",1},{"red",0}}
    }
    {
        multimap<string, int> src_map = {{"RED", 0}, {"RED", 0}, {"GREEN", 1}, {"BLUE", 2}};
        auto func = [](const pair<string, int>& pair) {
            return pair.first + ": " + util::to_string(pair.second);};
        auto result = util::map(src_map, func);
        print(result); // {"BLUE: 2","GREEN: 1","RED: 0","RED: 0"}
        set<string> result_set = util::map(src_map, func);
        print(result_set); // {"BLUE: 2","GREEN: 1","RED: 0"}
    }


    // g++ -std=c++1y sample_functional.cpp
}
