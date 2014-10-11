#ifndef UTIL_H
#define UTIL_H

#include <memory>
#include <vector>


namespace util {

#define DEF_HAS_TYPE(X) template <typename T>\
    class has_ ## X\
    {\
        typedef char true_type;\
        struct false_type{ true_type _[2]; };\
        template <typename U>\
        static true_type has_iterator_checker(typename U::X *);\
        template <typename U>\
        static false_type has_iterator_checker(...);\
    public:\
        static const bool value = (sizeof(has_iterator_checker<T>(0)) == sizeof(true_type));\
    };

#define DEF_HAS_METHOD(X) struct has_ ## X ## _impl\
    {\
        template <class T>\
        static std::true_type check(decltype(declval<T>().X)*);\
        template <class T>\
        static std::false_type check(...);\
    };\
    template <class T>\
    class has_ ## X : public decltype(has_ ## X ## _impl::check<T>(nullptr)) {};


template <class T, class Alloc = typename std::allocator<T> >
struct convertible_vector : public std::vector<T, Alloc> {
    template <class S>
    operator S() const {
        return S(std::begin(*this), std::end(*this));
    }
};


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

DEF_HAS_TYPE(iterator)
DEF_HAS_TYPE(mapped_type)
DEF_HAS_TYPE(first_type)
DEF_HAS_TYPE(second_type)

template <typename T>
struct is_pair {
    static const bool value = has_first_type<T>::value && has_second_type<T>::value;
};

template <template<class, class, class...> class Container, class T1, class T2, class... Ts>
struct is_map {
    static const bool value = std::is_same<
        typename Container<T1, T2, Ts...>::value_type,
        std::pair<const T1, T2> >::value;
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
