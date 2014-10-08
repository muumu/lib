#include "util.h"
#include <iostream>
#include <functional>
#include <type_traits>

namespace util {
    // receives member function
    template <class Container,
             typename std::enable_if<util::is_container<Container>::value>::type* = nullptr,
             class Func,
             typename std::enable_if<std::is_member_function_pointer<Func>::value>::type* = nullptr>
    Container map(const Container& source, Func fun) {
        Container dest(source);
        for (auto&& elem : dest) {
            (elem.*fun)();
        }
        return dest;
    }
    // receives non-member function
    template <class Container,
             typename std::enable_if<util::is_container<Container>::value>::type* = nullptr,
             class Func,
             typename std::enable_if<!std::is_member_function_pointer<Func>::value>::type* = nullptr>
    Container map(const Container& source, Func fun) {
        Container dest(source);
        auto d_it = dest.begin();
        for (auto s_it = source.begin(); s_it != source.end(); ++s_it, ++d_it) {
            *d_it = fun(*s_it);
        }
        return dest;
    }

}
