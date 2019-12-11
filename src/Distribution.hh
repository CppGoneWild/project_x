#ifndef DISTRIBUTION_HH
#define DISTRIBUTION_HH



#include <vector>



template <typename T>
using Distribution = std::vector<T>;



template <typename T>
T sum(Distribution<T> const &);

template <typename T>
T median(Distribution<T> const &);

template <typename T>
T mean(Distribution<T> const &);

template <typename T>
T mean(Distribution<T> const & values, Distribution<T> const & factors);

template <typename T>
T geometric_mean(Distribution<T> const &);



template <typename T>
Distribution<T>  add_distribution(Distribution<T> const &, Distribution<T> const &);

template <typename T>
Distribution<T>  sub_distribution(Distribution<T> const &, Distribution<T> const &);

template <typename T>
Distribution<T>  mul_distribution(Distribution<T> const &, Distribution<T> const &);

template <typename T>
Distribution<T>  div_distribution(Distribution<T> const &, Distribution<T> const &);



#include "Distribution.ipp"



#endif // DISTRIBUTION_HH
