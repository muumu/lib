#ifndef MPLLIB_H
#define MPLLIB_H

#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/minus.hpp>

namespace mpllib {

namespace mpl = boost::mpl;

template <typename Sequence, typename N>
struct erase_after_n {
    typedef typename mpl::begin<Sequence>::type begin_iter;
    typedef typename mpl::advance<begin_iter, N>::type cut_iter;
    typedef typename mpl::end<Sequence>::type end_iter;
    typedef typename mpl::erase<Sequence, cut_iter, end_iter>::type type;
};

template <typename Sequence, typename N>
struct erase_head_n {
    typedef typename mpl::begin<Sequence>::type begin_iter;
    typedef typename mpl::advance<begin_iter, N>::type cut_iter;
    typedef typename mpl::erase<Sequence, begin_iter, cut_iter>::type type;
};

template <typename Sequence, typename N> 
struct head_n {
    typedef typename mpl::eval_if<
        mpl::less<mpl::size<Sequence>, N>,
        Sequence,
        erase_after_n<Sequence, N>
    >::type type;

};

template <typename Sequence, int N> 
struct head_n_c {
    typedef typename head_n<Sequence, mpl::int_<N> >::type type;
};

template <typename Sequence, typename N> 
struct tail_n {
    typedef typename mpl::eval_if<
        mpl::less<mpl::size<Sequence>, N>,
        Sequence,
        erase_head_n<Sequence, mpl::minus<mpl::size<Sequence>, N> >
    >::type type;

};

template <typename Sequence, int N> 
struct tail_n_c {
    typedef typename tail_n<Sequence, mpl::int_<N> >::type type;
};

}; // end of namespace mpllib

#endif //MPLLIB_H
