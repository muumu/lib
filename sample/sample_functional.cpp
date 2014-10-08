#include "../functional.h"
#include "../stringlib.h"
#include <vector>


std::string repeat(const std::string& str) {
    return str + str;
}

int main() {
    std::vector<std::string> source = {"a?", "ab?", "abc?", "abcd?"};
    std::cout << util::to_string(source) << std::endl;

    {
        auto output = util::map(source, &std::string::pop_back);
        std::cout << util::to_string(output) << std::endl;
    }

    {
        auto output = util::map(source, &repeat);
        std::cout << util::to_string(output) << std::endl;
    }

    // compile: g++ -std=c++1y sample_functional.cpp
    // outputs:
    //
    // {a?,ab?,abc?,abcd?}
    // {a,ab,abc,abcd}
    // {a?a?,ab?ab?,abc?abc?,abcd?abcd?}
}
