#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <set>
#include <time.h>
#include "../stringlib.h"

using namespace std;

int main() {
    string str = util::to_string("She is ", 14, " years old.");
    int a = 4;
    float pi = 3.14;
    const char* c_str = "C++11";
    list<string> langs = {"C++", "Java", "Python", "Haskell"};
    vector<int> vec({0, 1, 2, 3});
    int arr[4] = {4, 5, 6, 7};
    int arr2d[2][2] = {{4, 5}, {6, 7}};
    map<string, string> profile({{"name", "miuna"}, {"age", "14"}});
    set<std::string> member({"madoka", "sayaka", "homura", "mami", "kyouko", "nagisa"});
    vector<vector<int> > vec2d({{0, 1}, {2, 3}, {4, 5}});
    vector<vector<vector<int> > > vec3d({{{0}, {1, 2, 3}}, {{4, 5, 6}, {7, 8, 9, 10}}, {{11, 12}, {13, 14}}});
    std::array<std::array<char, 2>, 2> array2d {{ {{'a', 'b'}}, {{'c', 'd'}} }};
    vector<int> empty;

    util::dump(str, pi, vec, c_str, langs, arr, arr2d, profile, member, vec2d, vec3d, array2d, empty);

    util::dump(-2, "C++14", array<int, 3>({4, 5, 6}), map<string, string>({{"name", "miuna"}, {"age", "14"}}));
}
