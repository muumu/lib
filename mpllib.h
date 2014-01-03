#ifndef MPLLIB_H
#define MPLLIB_H

#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/minus.hpp>
namespace mpl = boost::mpl;

template <typename T, typename N>
struct erase_after_n {
    typedef typename mpl::begin<T>::type begin_iter;
    typedef typename mpl::advance<begin_iter, N>::type cut_iter;
    typedef typename mpl::end<T>::type end_iter;
    typedef typename mpl::erase<T, cut_iter, end_iter>::type type;
};

template <typename T, typename N>
struct erase_n {
    typedef typename mpl::begin<T>::type begin_iter;
    typedef typename mpl::advance<begin_iter, N>::type cut_iter;
    typedef typename mpl::erase<T, begin_iter, cut_iter>::type type;
};

template <typename Sequence, typename N> 
struct head_n_elements {
    typedef 
    typename mpl::eval_if<
        mpl::less<mpl::size<Sequence>, N>,
        Sequence,
        erase_after_n<Sequence, N>
    >::type type;

};

template <typename Sequence, int N> 
struct head_n_elements_c {
    typedef typename head_n_elements<Sequence, mpl::int_<N> >::type type;
};

template <typename Sequence, typename N> 
struct tail_n_elements {
    typedef 
    typename mpl::eval_if<
        mpl::less<mpl::size<Sequence>, N>,
        Sequence,
        erase_n<Sequence, mpl::minus<mpl::size<Sequence>, N> >
    >::type type;

};

template <typename Sequence, int N> 
struct tail_n_elements_c {
    typedef typename tail_n_elements<Sequence, mpl::int_<N> >::type type;
};


#endif //MPLLIB_H
