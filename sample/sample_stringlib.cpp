#include <iostream>
#include "../stringlib.h"

int main() {
    std::cout << util::to_string(2) << std::endl;
    //std::vector<int> vec = {0, 1, 2, 3};
    std::vector<int> vec(4, 1);
    //util::dump(vec);
    util::dump(4, "test", vec);
}
