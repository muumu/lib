#ifndef STATIC_INITIALIZER_H
#define STATIC_INITIALIZER_H

#include <type_traits>

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


#endif // STATIC_INITIALIZER_H
