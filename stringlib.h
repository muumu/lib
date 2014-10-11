#ifndef STRINGLIB_H
#define STRINGLIB_H

#include <string>
#include <sstream>
#include <type_traits>
#include "util.h"

namespace util {

std::string to_lower(const std::string& str) {
    std::string ret(str);
    std::transform(str.begin(), str.end(), ret.begin(), ::tolower);
    return ret;
}

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

std::string to_string(const char* str) {
    return str;
}

std::string to_string(char c) {
    return std::string(1, c);
}

std::string enclose(const std::string& str, const std::string& enc) {
    std::string s;
    s.reserve(str.size() + 2 * enc.size());
    s += enc; s += str; s += enc;
    return s;
}

std::string enclose(char ch, const std::string& enc) {
    std::string s;
    s.reserve(1 + 2 * enc.size());
    s += enc;
    s.push_back(ch);
    s += enc;
    return s;
}

std::string add_double_quotes(const std::string& str) {
    return enclose(str, "\"");
}

std::string add_single_quotes(char ch) {
    return enclose(util::to_string(ch), "\'");
}

template <typename T>
std::string formatted_string(const T& arg);

std::string formatted_string(const std::string& str) {
    return add_double_quotes(str);
}

std::string formatted_string(char ch) {
    return add_single_quotes(ch);
}

template <typename S, typename T>
std::string to_string(const std::pair<S, T>& pair) {
    return "{" + formatted_string(pair.first) + "," + formatted_string(pair.second) + "}";
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
        str += formatted_string(elem) + ",";
    }
    str.back() = '}';
    return str;
}

template <typename T, typename... Args>
std::string to_string(const T& arg, const Args&... args) {
    return to_string(arg) + to_string(args...);
}

template <typename T>
std::string formatted_string(const T& arg) {
    return util::to_string(arg);
}

template <typename T>
void print(const T& arg) {
    std::cout << util::formatted_string(arg) << std::endl;
}


template <typename T, typename... Args>
void print(const T& arg, const Args&... args) {
    print(arg);
    print(args...);
}

};


#endif // STRINGLIB_H
