#ifndef FN_FUNCTIONAL_H
#define FN_FUNCTIONAL_H

#include "util.h"
#include <iostream>
#include <functional>
#include <type_traits>
#include <algorithm>

namespace fn {

// For custom container that takes one template parameter
template <
    template<class> class Container,
    class Func,
    class T,
    typename std::enable_if<util::has_iterator<Container<T> >::value>::type* = nullptr
    >
auto map(const Container<T>& source, Func fun) {
    Container<decltype(
        util::functor(fun)(std::declval<typename Container<T>::value_type>())
        )> dest;
    std::transform(source.begin(), source.end(),
        util::back_inserter(dest), util::functor(fun));
    return dest;
}

// For std::array
template <class T, size_t N, class Func>
auto map(const std::array<T, N>& source, Func fun) {
    std::array<T, N> dest;
    std::transform(source.begin(), source.end(), dest.begin(), util::functor(fun));
    return dest;
}

// For non-map containers
template <
    class T1, class T2, class... Ts,
    template<class, class, class...> class Container,
    class Func,
    typename std::enable_if<util::has_iterator<Container<T1, T2, Ts...> >::value>::type* = nullptr,
    typename std::enable_if<!util::is_map<Container, T1, T2, Ts...>::value>::type* = nullptr
    >
auto map(const Container<T1, T2, Ts...>& source, Func fun) {
    Container<decltype(
        util::functor(fun)(std::declval<typename Container<T1, T2, Ts...>::value_type>())
        ), T2, Ts...> dest;
    std::transform(source.begin(), source.end(),
        util::back_inserter(dest), util::functor(fun));
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
        decltype(util::functor(fun)(std::declval<typename Container<T1, T2<T1>, Ts...>::value_type>()));
    Container<value_type, T2<value_type>, Ts...> dest;
    std::transform(source.begin(), source.end(),
        util::back_inserter(dest), util::functor(fun));
    return dest;
}

// For map and multimap
template <
    template <class, class, class, class> class Map,
    template <class> class Compare,
    template <class> class Alloc,
    template <class, class> class Pair,
    class Key,
    class T,
    class Func,
    typename std::enable_if<util::is_map_<
        Map<Key, T, Compare<Key>, Alloc<Pair<const Key, T> > >
        >::value>::type* = nullptr,
    typename std::enable_if<util::is_pair<
        decltype(util::functor(std::declval<Func>())(std::declval<
        typename Map<Key, T, Compare<Key>, Alloc<Pair<const Key, T> > >::value_type
        >()))>::value>::type* = nullptr
    >
auto map(
    const Map<Key, T, Compare<Key>, Alloc<Pair<const Key, T> > >& source,
    Func fun)
{
    using pair_type =
        decltype(util::functor(fun)(std::declval<
        typename Map<Key, T, Compare<Key>, Alloc<Pair<const Key, T> > >::value_type>()));
    using key_type = typename pair_type::first_type;
    using mapped_type = typename pair_type::second_type;
    Map<key_type, mapped_type, Compare<key_type>,
        Alloc<Pair<const key_type, mapped_type> > > dest;
    for (auto&& elem : source) {
        dest.insert(util::functor(fun)(elem));
    }
    return dest;
}

// For unordred_map and unordered_multimap
template <
    template <class, class, class, class, class> class Map,
    template <class> class Hash,
    template <class> class Pred,
    template <class> class Alloc,
    template <class, class> class Pair,
    class Key,
    class T,
    class Func,
    typename std::enable_if<util::is_map_<
        Map<Key, T, Hash<Key>, Pred<Key>, Alloc<Pair<const Key, T> > >
        >::value>::type* = nullptr,
    typename std::enable_if<util::is_pair<
        decltype(util::functor(std::declval<Func>())(std::declval<
        typename Map<Key, T, Hash<Key>, Pred<Key>, Alloc<Pair<const Key, T> > >::value_type
        >()))>::value>::type* = nullptr
    >
auto map(
    const Map<Key, T, Hash<Key>, Pred<Key>, Alloc<Pair<const Key, T> > >& source,
    Func fun)
{
    using pair_type =
        decltype(util::functor(fun)(std::declval<
        typename Map<Key, T, Hash<Key>, Pred<Key>, Alloc<Pair<const Key, T> > >::value_type>()));
    using key_type = typename pair_type::first_type;
    using mapped_type = typename pair_type::second_type;
    Map<key_type, mapped_type, Hash<key_type>, Pred<Key>,
        Alloc<Pair<const key_type, mapped_type> > > dest;
    for (auto&& elem : source) {
        dest.insert(util::functor(fun)(elem));
    }
    return dest;
}

// For map type container to vector
template <
    template<class, class, class...> class Map,
    class Func,
    class Key, class T, class... Ts,
    typename std::enable_if<util::is_map_<Map<Key, T, Ts...> >::value>::type* = nullptr,
    typename std::enable_if<!util::is_pair<
        decltype(util::functor(std::declval<Func>())(
        std::declval<typename Map<Key, T, Ts...>::value_type>()))
        >::value>::type* = nullptr
    >
auto map(const Map<Key, T, Ts...>& source, Func fun) {
    using value_type =
        decltype(util::functor(std::declval<Func>())(
        std::declval<typename Map<Key, T, Ts...>::value_type>()));
    util::convertible_vector<value_type> dest;
    dest.reserve(source.size());
    for (auto&& elem : source) {
        dest.push_back(util::functor(fun)(elem));
    }
    return dest;
}

template <typename First, typename Second>
std::pair<Second, First> swap(const std::pair<First, Second>& p) {
    return std::make_pair(p.second, p.first);
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

#endif // FN_FUNCTIONAL_H
