#ifndef BITOPLIB_H
#define BITOPLIB_H

#include <string>
#include <algorithm>
#include <boost/mpl/string.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/min_max.hpp>
//#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/shift_right.hpp>
#include <boost/mpl/bitwise.hpp>
#include <boost/preprocessor.hpp>
#include "mpllib.h"

namespace mpl = boost::mpl;

const int BITS_PER_BYTE = 8;

template <typename T>
inline std::string to_bin_str(T n) {
    std::string str;
    while (n > 0) {
        str.push_back('0' + (n & 1));
        n >>= 1;
    }
    std::reverse(str.begin(), str.end());
    return str;
}

template <typename T>
inline std::string to_bin_str(T n, std::size_t digit_num) {
    std::string str;
    while (n > 0) {
        str.push_back('0' + (n & 1));
        n >>= 1;
    }
    str.resize(digit_num, '0');
    std::reverse(str.begin(), str.end());
    return str;
}

template <long long unsigned N>
struct bit_scan_reverse {
    enum {value = 1 + bit_scan_reverse<(N >> 1)>::value};
};
template <>
struct bit_scan_reverse<0> {
    enum {value = 0};
};

template <typename Sequence1, typename Sequence2>
struct concat : mpl::insert_range<Sequence1, typename mpl::end<Sequence1>::type, Sequence2> {};

template <int N>
struct zero_string : mpl::push_back<typename zero_string<N-1>::type, mpl::char_<'0'> > {};
template <>
struct zero_string<0> : mpl::string<> {};
/*
template <typename Integer>
struct zero_string : mpl::push_back<typename zero_string<typename mpl::minus<Integer, mpl::int_<1> >::type>::type, mpl::char_<'0'> > {};
template <>
struct zero_string<mpl::int_<0> > : mpl::string<> {};

template <typename Sequence, int DigitNumber>
struct format_bin_string {
    typedef
        typename mpl::eval_if_c<(DigitNumber > mpl::size<Sequence>::value),
            //typename concat<typename zero_string<DigitNumber - mpl::size<Sequence>::value>::type, Sequence>::type
            typename concat<
                typename zero_string<
                    typename mpl::max<
                        typename mpl::plus<
                            mpl::int_<DigitNumber>,
                            typename mpl::size<Sequence>::type
                        >::type,
                        mpl::int_<0>
                    >::type
                >::type,
                Sequence
            >::type,
            Sequence
        >::type type;
};
*/
template <typename Sequence, int DigitNum, bool greater = (DigitNum >= mpl::size<Sequence>::value)>
struct format_bin_string {};

template <typename Sequence, int DigitNum>
struct format_bin_string<Sequence, DigitNum, true> :
    concat<
        typename zero_string<DigitNum - mpl::size<Sequence>::value>::type,
        Sequence
    > {};

template <typename Sequence, int DigitNum>
struct format_bin_string<Sequence, DigitNum, false> :
    mpllib::tail_n_c<Sequence, DigitNum> {};


template <typename c>
struct bin_string {
    typedef
        typename boost::mpl::push_back<
            typename bin_string<typename mpl::shift_right<c, mpl::int_<1> >::type>::type,
            boost::mpl::char_<'0' + (c::value & 1)>
        >::type type;

    static std::string str() {
        return std::string(mpl::c_str<type>::value);
    }
    template <int DigitNum>
    static std::string str() {
        return std::string(mpl::c_str<typename format_bin_string<type, DigitNum>::type>::value);
    }
};
template <typename T>
struct bin_string<mpl::integral_c<T, 0> > : boost::mpl::string<> {};

template <long long unsigned N>
struct bin_string_c : bin_string<mpl::integral_c<long long unsigned, N> > {};
/*
template <long long unsigned N>
struct bin_string_c {
    typedef
        typename boost::mpl::push_back<
            typename bin_string_c<(N >> 1)>::type, boost::mpl::char_<'0' + (N & 1)>
        >::type type;

    static std::string str() {
        return std::string(mpl::c_str<type>::value);
    }
    template <int DigitNum>
    static std::string str() {
        return std::string(mpl::c_str<typename format_bin_string<type, DigitNum>::type>::value);
    }
};
template <>
struct bin_string_c<0> : boost::mpl::string<> {};
*/
template <int DigitNum>
struct uint_selector :
    mpl::if_c<(DigitNum > sizeof(unsigned) * BITS_PER_BYTE), unsigned long long, unsigned> {};

template <int DigitNum, typename T = typename uint_selector<DigitNum>::type>
struct bit {
    typedef T type;
    static const T value = (static_cast<T>(1) << (DigitNum - 1));
};
template <>
struct bit<0> {
    enum {value = 0};
};

template <int DigitNum, typename T = typename uint_selector<DigitNum>::type>
struct bitmask {
    typedef T type;
    static const T value = bit<DigitNum + 1>::value - 1;
};
/*
template <>
struct bitmask<0> {
    enum {value = 0};
};
*/



#endif // BITOPLIB_H
