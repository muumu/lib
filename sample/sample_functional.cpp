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
        auto output = fn::map(source, fn::init);
        print(output); // {"a","ab","abc","abcd"}
    }
    {
        list<string> source = {"", "occupied", "", "occupied"};
        auto output = fn::map(source, &string::empty);
        print(output); // {true,false,true,false}
    }
    {
        array<string, 4> source = {"add", "sub", "mul", "div"};
        auto output = fn::map(source, util::upper);
        print(output); // {"ADD","SUB","MUL","DIV"}
    }
    {
        set<string> source = {"tea", "wine", "milk", "coffee"};
        auto output = fn::map(source, &string::size);
        print(output); // {3,4,6}
    }
    {
        multiset<string> source = {"tea", "wine", "milk", "coffee"};
        auto output = fn::map(source, &string::size);
        print(output); // {3,4,4,6}
    }
    {
        map<string, int> source_map = {{"RED", 0}, {"GREEN", 1}, {"BLUE", 2}};
        auto reversed_map = fn::map(source_map, fn::swap<string, int>);
        print(reversed_map); // {{0,"RED"},{1,"GREEN"},{2,"BLUE"}}
    }
    {
        unordered_map<string, int> source = {{"RED", 0}, {"GREEN", 1}, {"BLUE", 2}};
        auto result = fn::map(source,
            [](const pair<string, int>& p) {
                return make_pair(util::lower(p.first), p.second);
            });
        print(result); // {{"green",1},{"red",0},{"blue",2}}
    }
    {
        multimap<string, int> src_map = {{"RED", 0}, {"RED", 0}, {"GREEN", 1}};
        auto func = [](const pair<string, int>& pair) {
            return pair.first + ": " + util::to_string(pair.second);};
        auto result = fn::map(src_map, func);
        print(result); // {"GREEN: 1","RED: 0","RED: 0"}
        set<string> result_set = fn::map(src_map, func);
        print(result_set); // {"GREEN: 1","RED: 0"}
    }


    // $ g++ -std=c++1y -o sample_functional sample_functional.cpp
    // $ ./sample_functional
    // std::vector<std::string, std::allocator<std::string> >
    //     {"a","ab","abc","abcd"}
    // std::list<bool, std::allocator<bool> >
    //     {true,false,true,false}
    // std::array<std::string, 4ul>
    //     {"ADD","SUB","MUL","DIV"}
    // std::set<unsigned long, std::less<unsigned long>, std::allocator<std::string> >
    //     {3,4,6}
    // std::multiset<unsigned long, std::less<unsigned long>, std::allocator<std::string> >
    //     {3,4,4,6}
    // std::map<int, std::string, std::less<int>, std::allocator<std::pair<int const, std::string> > >
    //     {{0,"RED"},{1,"GREEN"},{2,"BLUE"}}
    // std::unordered_map<std::string, int, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<std::string const, int> > >
    //     {{"green",1},{"red",0},{"blue",2}}
    // util::convertible_vector<std::string, std::allocator<std::string> >
    //     {"GREEN: 1","RED: 0","RED: 0"}
    // std::set<std::string, std::less<std::string>, std::allocator<std::string> >
    //     {"GREEN: 1","RED: 0"}

}
