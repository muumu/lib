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
    class T1, class T2, class... Ts,
    template<class, class, class...> class Container,
    class Func,
    typename std::enable_if<util::has_iterator<Container<T1, T2, Ts...> >::value>::type* = nullptr,
    typename std::enable_if<!is_map<Container, T1, T2, Ts...>::value>::type* = nullptr
    >
auto map(const Container<T1, T2, Ts...>& source, Func fun) {
    Container<decltype(
        to_functor(fun)(std::declval<typename Container<T1, T2, Ts...>::value_type>())
        ), T2> dest(source.size());
    std::transform(source.begin(), source.end(), dest.begin(), to_functor(fun));
    return dest;
}

template <
    template<class, class, class...> class Map,
    class Func,
    class Key, class Value, class... Ts,
    typename std::enable_if<util::has_iterator<Map<Key, Value, Ts...> >::value>::type* = nullptr,
    typename std::enable_if<is_map<Map, Key, Value, Ts...>::value>::type* = nullptr,
    typename std::enable_if<util::is_pair<
        decltype(
            util::to_functor(std::declval<Func>())(
                std::declval<typename Map<Key, Value, Ts...>::value_type>())
        )
        >::value>::type* = nullptr
    >
auto map(const Map<Key, Value, Ts...>& source, Func fun) {
    using pair_type = decltype(to_functor(fun)(
        std::declval<typename Map<Key, Value, Ts...>::value_type>()));
    using key_type = typename pair_type::first_type;
    using value_type = typename pair_type::second_type;
    Map<key_type, value_type> dest;
    for (auto&& elem : source) {
        dest.insert(util::to_functor(fun)(elem));
    }
    return dest;
}

template <
    template<class, class, class...> class Map,
    class Func,
    class Key, class Value, class... Ts,
    typename std::enable_if<util::has_iterator<Map<Key, Value, Ts...> >::value>::type* = nullptr,
    typename std::enable_if<is_map<Map, Key, Value, Ts...>::value>::type* = nullptr,
    typename std::enable_if<!util::is_pair<
        decltype(
            util::to_functor(std::declval<Func>())(
                std::declval<typename Map<Key, Value, Ts...>::value_type>())
        )
        >::value>::type* = nullptr
    >
auto map(const Map<Key, Value, Ts...>& source, Func fun) {
    using value_type = decltype(
        util::to_functor(std::declval<Func>())(
            std::declval<typename Map<Key, Value, Ts...>::value_type>())
        );
    util::convertible_vector<value_type> dest;
    for (auto&& elem : source) {
        dest.push_back(util::to_functor(fun)(elem));
    }
    return dest;
}


}
