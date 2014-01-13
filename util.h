#ifndef UTIL_H
#define UTIL_H

namespace util {

template <typename T>
inline void delete_if_needed(T) {}

template <typename T>
inline void delete_if_needed(T* p) {
    delete p;
}

template <typename ReturnType, typename... Args>
inline void delete_if_needed(ReturnType (*)(Args... args)) {};

template <typename Functor, typename... Args>
inline void exec_functor(Functor f, Args&... args) {
    f(args...);
};

template <typename Functor, typename... Args>
inline void exec_functor(Functor* f, Args&... args) {
    (*f)(args...);
};

}; // namespace util


#endif
