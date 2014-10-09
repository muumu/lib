#include "../functional.h"
#include "../stringlib.h"
#include <vector>

int main() {
    std::vector<std::string> source = {"a?", "ab?", "abc?", "abcd?"};
    std::cout << util::to_string(source) << std::endl; // {a?,ab?,abc?,abcd?}

    {
        auto output = util::map(source,
            [](const std::string& str) { return str.substr(0, str.size() - 1); });
        std::cout << util::to_string(output) << std::endl; // {a,ab,abc,abcd}
    }

    {
        auto output = util::map(source, &std::string::size);
        std::cout << util::to_string(output) << std::endl; // {2,3,4,5}
    }

    // g++ -std=c++1y sample_functional.cpp
}
