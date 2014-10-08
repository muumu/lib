#include <iostream>
#include "indexmapper.h"

int main() {
    std::vector<std::vector<int> > sets = {{3, 5, 6}, {2, 5, 3, 4}};
    IndexMapper<2, 6> mapper;
    mapper.make_map(sets);
    std::cout << mapper.to_string();
}
