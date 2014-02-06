#ifndef STRINGLIB_H
#define STRINGLIB_H

#include <string>
#include <sstream>
#include <vector>

namespace util {

template <typename T>
std::string to_string(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

std::string to_string(const std::string& str) {
    return str;
}

template <typename T>
std::string to_string(const std::vector<T>& vec) {
    if (vec.size() == 0) {
        return "";
    }
    std::string str = to_string(vec[0]);
    for (std::size_t i = 1; i < vec.size(); ++i) {
        str += "," + to_string(vec[i]);
    }
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
