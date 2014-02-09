#ifndef STRINGLIB_H
#define STRINGLIB_H

#include <string>
#include <sstream>
#include <type_traits>
#include "util.h"

namespace util {

template <typename T>
std::string to_string(const T& t,
    typename std::enable_if<!is_container<T>::value && !std::is_array<T>::value>::type* = 0)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

const std::string& to_string(const std::string& str) {
    return str;
}

std::string to_string(char c) {
    return std::string(1, c);
}

std::string to_string(const char* str) {
    return str;
}

template <typename S, typename T>
std::string to_string(const std::pair<S, T>& pair) {
    return "{" + to_string(pair.first) + "," + to_string(pair.second) + "}";
}

template <typename T>
std::string to_string(const T& cont,
    typename std::enable_if<is_container<T>::value || std::is_array<T>::value>::type* = 0)
{
    if (std::begin(cont) == std::end(cont)) {
        return "";
    }
    std::string str = "{";
    for (const auto& elem : cont) {
        str += to_string(elem) + ",";
    }
    str.back() = '}';
    return str;
}

template <typename T, typename... Args>
std::string to_string(const T& arg, const Args&... args) {
    return to_string(arg) + to_string(args...);
}

template <typename T>
void dump(const T& arg) {
    std::cout << to_string(arg) << std::endl;
}

template <typename T, typename... Args>
void dump(const T& arg, const Args&... args) {
    std::cout << to_string(arg) << std::endl;
    dump(args...);
}

};


#endif // STRINGLIB_H
