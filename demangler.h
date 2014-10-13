#ifndef UTIL_DEMANGLER_H
#define UTIL_DEMANGLER_H

#include <typeinfo>
#include <cxxabi.h>

namespace util {

template <typename T>
std::string demangle(T) {
    int status;
    char* name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
    std::string ret(name);
    free(name);
    return ret;
}

} // namespace util

#endif // UTIL_DEMANGLER_H
