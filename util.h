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

template <typename T>
class is_container
{
    typedef char true_type;
    struct false_type{ true_type _[2]; };
    template <typename U>
    static true_type has_iterator_checker(typename U::iterator *);
    template <typename U>
    static false_type has_iterator_checker(...);
public:
    static const bool value = (sizeof(has_iterator_checker<T>(0)) == sizeof(true_type));
};

}; // namespace util


#endif
