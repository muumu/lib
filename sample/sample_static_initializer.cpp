#include <unordered_map>
#include <functional>
#include <array>
#include <iostream>
#include "static_initializer.hpp"


class Bar {
private:
    static const int Size = 100;
    static const int* arr_a;
    static const std::array<int, Size> arr_b;
public:
    void print_head(int n) {
        std::cout << "head " << n << " of arr_a\n";
        for (int i = 0; i < n; ++i) {
            std::cout << arr_a[i] << std::endl;
        }
        std::cout << "head " << n << " of arr_b\n";
        for (int i = 0; i < n; ++i) {
            std::cout << arr_b[i] << std::endl;
        }
    }
};

const int* Bar::arr_a = static_initializer<int[Bar::Size]>::get(
    [](int* arr) {
        for (int i = 0; i < Bar::Size; ++i) {
            arr[i] = i * i;
        }
    });

const std::array<int, Bar::Size> Bar::arr_b =
    static_initializer<std::array<int, Bar::Size> >::get(
    [](std::array<int, Bar::Size>& arr) {
        for (int i = 0; i < Bar::Size; ++i) {
            arr[i] = i * i * i;
        }
    });


int get_code(char c) {
    static auto mp = static_initializer<std::unordered_map<char, int> >::get(
        [](std::unordered_map<char, int>& mp) {
            for (int i = 0; i < 26; ++i) {
                mp['A' + i] = i;
            }
            for (int i = 26; i < 52; ++i) {
                mp['a' + i - 26] = i;
            }
        });
    return mp[c];
}

int get_code_innerclass(char c) {
    class Map {
    private:
        std::unordered_map<char, int> mp_;
        Map() {
            for (int i = 0; i < 26; ++i) {
                mp_['A' + i] = i;
            }
            for (int i = 26; i < 52; ++i) {
                mp_['a' + i - 26] = i;
            }
        }
    public:
        static std::unordered_map<char, int> get() {
            static Map obj;
            return std::move(obj.mp_);
        }
    };
    static auto mp = Map::get();
    return mp[c];
}

template <class Map, class RevMap>
void make_reverse_map(const Map& mp, RevMap& rev_mp) {
    auto it = std::begin(mp);
    while (it != std::end(mp)) {
        rev_mp[it->second] = it->first;
        ++it;
    }
}

template <class RevMap, class Map>
RevMap reverse_map(const Map& mp) {
    return std::move(static_initializer<RevMap>::
        get(std::bind(make_reverse_map<Map, RevMap>, mp, std::placeholders::_1)));
}

class Foo {
private:
    typedef std::unordered_map<std::string, int> FooMap;
    typedef std::unordered_map<int, std::string> FooRevMap;
    static const FooMap mp;
    static const FooRevMap rev_mp;
public:
    void print() {
        std::cout << "foo => " << mp.at("foo") << std::endl;
        std::cout << "892 => " << rev_mp.at(892) << std::endl;
    }
};

const Foo::FooMap Foo::mp = {{"foo", 398}, {"bar", 892}};
const Foo::FooRevMap Foo::rev_mp = reverse_map<Foo::FooRevMap>(mp);


int main() {
    std::cout << get_code('A') << std::endl;
    std::cout << get_code('B') << std::endl;
    std::cout << get_code('Z') << std::endl;
    std::cout << get_code('a') << std::endl;
    std::cout << get_code('b') << std::endl;
    std::cout << get_code('z') << std::endl;
    std::cout << get_code_innerclass('z') << std::endl;
    Foo().print();
    Bar().print_head(5);
}
