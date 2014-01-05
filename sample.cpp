#define BOOST_MPL_LIMIT_STRING_SIZE 64

#include <iostream>
#include <typeinfo>
#include <bitset>
#include <sstream>
#include "bitoplib.h"

#define BINSTR(x) mpl::c_str<bin_string_c<x>::type >::value
#define FBINSTR(x, n) mpl::c_str<format_bin_string<bin_string_c<x>::type, n>::type>::value

namespace mpl = boost::mpl;

typedef unsigned long long ull_t;

struct foo {
    enum {value = 16};
};

int main() {
    char x = 4;
    unsigned y = 11;
    int z = 103;
    unsigned long long w = 4527856554780ULL;
    std::cout << to_bin_str(x) << std::endl;
    std::cout << to_bin_str(y) << std::endl;
    std::cout << to_bin_str(z) << std::endl;
    std::cout << to_bin_str(w) << std::endl;

    const std::size_t n = 5;
    std::cout << to_bin_str(x, n) << std::endl;
    std::cout << to_bin_str(y, n) << std::endl;
    std::cout << to_bin_str(z, n) << std::endl;
    std::cout << to_bin_str(w, n) << std::endl;

    const char x_c = 4;
    const unsigned y_c = 11;
    const int z_c = 103;
    const unsigned long long w_c = 4527856554780ULL;
    std::cout << mpl::c_str<bin_string_c<x_c>::type >::value << std::endl;
    std::cout << BINSTR(y_c) << std::endl;
    std::cout << BINSTR(z_c) << std::endl;
    std::cout << BINSTR(w_c) << std::endl;

    std::cout << mpl::c_str<format_bin_string<bin_string_c<x_c>::type, n>::type>::value << std::endl;
    std::cout << FBINSTR(y_c, n) << std::endl;
    std::cout << FBINSTR(z_c, n) << std::endl;
    std::cout << FBINSTR(w_c, n) << std::endl;
    //std::cout << mpl::c_str<format_bin_string<bin_string_c<y_c>::type, n>::type>::value << std::endl;
    //std::cout << mpl::c_str<format_bin_string<bin_string_c<z_c>::type, n>::type>::value << std::endl;
    //std::cout << mpl::c_str<format_bin_string<bin_string_c<w_c>::type, n>::type>::value << std::endl;

/*
    std::cout << bin_string_c<x_c>::str<n>() << std::endl;
    std::cout << bin_string_c<y_c>::str<n>() << std::endl;
    std::cout << bin_string_c<z_c>::str<n>() << std::endl;
    std::cout << bin_string_c<w_c>::str<n>() << std::endl;
*/
    std::cout.write(reinterpret_cast<const char*>(&y), sizeof y);
    std::cout << std::endl;
    //std::bitset<64> bin_w(w);
    std::cout << static_cast<std::bitset<64> >(w) << std::endl;
    std::stringstream ss;
    ss << static_cast<std::bitset<64> >(w);
    std::cout << ss.str() << std::endl;

    const int v = 6;
    std::cout << mpl::c_str<bin_string_c<3>::type>::value << std::endl;
    std::cout << mpl::c_str<bin_string_c<4686>::type>::value << std::endl;
    std::cout << mpl::c_str<bin_string_c<v>::type>::value << std::endl;
    std::cout << mpl::c_str<bin_string_c<foo::value>::type>::value << std::endl;

    const int digit_num = 4;
    //std::cout << mpl::size<bin_string<3>::type>::value << std::endl;
    std::cout << (2 > mpl::size<bin_string_c<v>::type>::value ? "true" : "false") << std::endl;
    std::cout << (digit_num > v ? "true" : "false") << std::endl;
    std::cout << mpl::c_str<format_bin_string<bin_string_c<3>::type, digit_num>::type>::value << std::endl;
    std::cout << mpl::c_str<format_bin_string<bin_string_c<4686>::type, digit_num>::type>::value << std::endl;
    std::cout << mpl::c_str<format_bin_string<bin_string_c<v>::type, digit_num>::type>::value << std::endl;
    std::cout << mpl::c_str<format_bin_string<bin_string_c<foo::value>::type, digit_num>::type>::value << std::endl;

    std::cout << bin_string_c<3>::str() << std::endl;
    std::cout << bin_string_c<v>::str() << std::endl;
    std::cout << bin_string_c<foo::value>::str() << std::endl;

    std::cout << bin_string_c<3>::str<4>() << std::endl;
    std::cout << bin_string_c<v>::str<4>() << std::endl;
    std::cout << bin_string_c<foo::value>::str<4>() << std::endl;


    const auto mask = bitmask<3>::value;
    const ull_t mask2 = bitmask<5, ull_t>::value;
    const auto mask3 = bitmask<64>::value;
    std::cout << mask << std::endl;
    std::cout << bin_string_c<mask>::str() << std::endl;
    std::cout << mask2 << std::endl;
    std::cout << bin_string_c<mask2>::str() << std::endl;
    std::cout << mask3 << std::endl;
    std::cout << bin_string_c<mask3>::str() << std::endl;

    const auto bit1 = bit<3>::value;
    const ull_t bit2 = bit<62, ull_t>::value;
    const auto bit3 = bit<64>::value;
    std::cout << bit1 << std::endl;
    std::cout << bin_string_c<bit1>::str() << std::endl;
    std::cout << bit2 << std::endl;
    std::cout << bin_string_c<bit2>::str() << std::endl;
    std::cout << bit3 << std::endl;
    std::cout << bin_string_c<bit3>::str() << std::endl;


    std::cout << sizeof(unsigned) * 8 << std::endl;
    std::cout << bit<33>::value << std::endl;
    std::cout << bit<64>::value << std::endl;
    std::cout << typeid(bit<32>::type).name() << std::endl;
    std::cout << typeid(bit<64>::type).name() << std::endl;
    std::cout << sizeof(bit<32>::value) << std::endl;
    std::cout << sizeof(bit<64>::value) << std::endl;

    std::cout << mpl::c_str<bin_string_c<bit<3>::value>::type>::value << std::endl;
    std::cout << mpl::c_str<bin_string_c<bit<33>::value>::type>::value << std::endl;
    std::cout << mpl::c_str<bin_string_c<bit<64>::value>::type>::value << std::endl;
}
