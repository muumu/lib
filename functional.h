#include "util.h"
#include <iostream>
#include <functional>
#include <type_traits>
#include <algorithm>

namespace util {

// For custom container that takes one template parameter
template <
    template<class> class Container,
    class Func,
    class T,
    typename std::enable_if<util::has_iterator<Container<T> >::value>::type* = nullptr
    >
auto map(const Container<T>& source, Func fun) {
    Container<decltype(
        to_functor(fun)(std::declval<typename Container<T>::value_type>())
        )> dest;
    std::transform(source.begin(), source.end(),
        util::back_inserter(dest), to_functor(fun));
    return dest;
}

// For non-map containers
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
        ), T2, Ts...> dest;
    std::transform(source.begin(), source.end(),
        util::back_inserter(dest), to_functor(fun));
    return dest;
}

// For set and multiset
template <
    class T1, template <class> class T2, class... Ts,
    template <class, class, class...> class Container,
    class Func,
    typename std::enable_if<util::has_iterator<Container<T1, T2<T1>, Ts...> >::value>::type* = nullptr
    >
auto map(const Container<T1, T2<T1>, Ts...>& source, Func fun) {
    using value_type =
        decltype(to_functor(fun)(std::declval<typename Container<T1, T2<T1>, Ts...>::value_type>()));
    Container<value_type, T2<value_type>, Ts...> dest;
    std::transform(source.begin(), source.end(),
        util::back_inserter(dest), to_functor(fun));
    return dest;
}

// For map type container
template <
    template<class, class, class...> class Map,
    class Func,
    class Key, class Value, class... Ts,
    typename std::enable_if<util::has_iterator<Map<Key, Value, Ts...> >::value>::type* = nullptr,
    typename std::enable_if<is_map<Map, Key, Value, Ts...>::value>::type* = nullptr,
    typename std::enable_if<util::is_pair<
        decltype(util::to_functor(std::declval<Func>())(
        std::declval<typename Map<Key, Value, Ts...>::value_type>()))
        >::value>::type* = nullptr
    >
auto map(const Map<Key, Value, Ts...>& source, Func fun) {
    using pair_type = decltype(to_functor(fun)(
        std::declval<typename Map<Key, Value, Ts...>::value_type>()));
    Map<typename pair_type::first_type, typename pair_type::second_type, Ts...> dest;
    for (auto&& elem : source) {
        dest.insert(util::to_functor(fun)(elem));
    }
    return dest;
}

// For map type container to vector
template <
    template<class, class, class...> class Map,
    class Func,
    class Key, class Value, class... Ts,
    typename std::enable_if<util::has_iterator<Map<Key, Value, Ts...> >::value>::type* = nullptr,
    typename std::enable_if<is_map<Map, Key, Value, Ts...>::value>::type* = nullptr,
    typename std::enable_if<!util::is_pair<
        decltype(util::to_functor(std::declval<Func>())(
        std::declval<typename Map<Key, Value, Ts...>::value_type>()))
        >::value>::type* = nullptr
    >
auto map(const Map<Key, Value, Ts...>& source, Func fun) {
    using value_type =
        decltype(util::to_functor(std::declval<Func>())(
        std::declval<typename Map<Key, Value, Ts...>::value_type>()));
    util::convertible_vector<value_type> dest;
    dest.reserve(source.size());
    for (auto&& elem : source) {
        dest.push_back(util::to_functor(fun)(elem));
    }
    return dest;
}

std::string init(const std::string& str) {
    return str.substr(0, str.size() - 1);
}

std::string slice(const std::string& str, int pos, int len = -1) {
    if (pos < 0) {
        return str.substr(0, str.size() + pos);
    }
    if (len < 0) {
        return str.substr(pos, str.size() - 1);
    }
    return str.substr(pos, len);
}

}
