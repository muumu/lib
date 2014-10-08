#ifndef STATIC_INITIALIZER_H
#define STATIC_INITIALIZER_H

#include <type_traits>

template <typename T>
struct function_traits
    : public function_traits<decltype(&T::operator())>
{};
// For generic types, directly use the result of the signature of its 'operator()'

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.

    typedef ReturnType result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };
};

template <class T>
class static_initializer {
public:
    template <class I, class... Args>
    static typename std::decay<T>::type get(I init, Args... ctor_args) {
        static static_initializer si(init, ctor_args...);
        return std::move(si.obj_);
    }
private:
    T obj_;
    template <class I, class... Args>
    static_initializer(I init, Args... ctor_args) : obj_(ctor_args...) {
        init(obj_);
    }
};

class static_initializer2 {
public:
    template <class I, class... Args>
    static auto get(I init, Args... ctor_args) {
        typedef typename std::remove_reference<typename function_traits<decltype(init)>::template arg<0>::type>::type T;
        //typedef typename function_traits<decltype(init)>::result_type T;
        static static_initializer_impl<T> si(init, ctor_args...);
        //return std::move(si.obj_);
        return si.obj_;
    }
private:
    template <class T>
    struct static_initializer_impl {
        T obj_;
        template <class I, class... Args>
        static_initializer_impl(I init, Args... ctor_args) : obj_(ctor_args...) {
            init(obj_);
        }

    };
};


#endif // STATIC_INITIALIZER_H
