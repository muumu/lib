#include "util.h"
#include <iostream>
#include <functional>
#include <type_traits>
#include <algorithm>

namespace util {

template <
    class Func,
    typename std::enable_if<std::is_member_function_pointer<Func>::value>::type* = nullptr
    >
auto to_functor(Func func) {
    return std::mem_fn(func);
}

template <
    class Func,
    typename std::enable_if<!std::is_member_function_pointer<Func>::value>::type* = nullptr
    >
auto to_functor(Func func) {
    return func;
}

template <
    class T, class... Ts,
    template<class, class...> class Container,
    typename std::enable_if<util::is_container<Container<T, Ts...> >::value>::type* = nullptr,
    class Func
    >
auto map(const Container<T, Ts...>& source, Func fun) {
    Container<decltype(
        to_functor(fun)(std::declval<typename Container<T, Ts...>::value_type>())
        )> dest(source.size());
    std::transform(source.begin(), source.end(), dest.begin(), to_functor(fun));
    return dest;
}

}
