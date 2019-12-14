#include <numeric>   // accumulate
#include <cmath>     // pow
#include <algorithm> // sort


template <typename T>
T sum(Distribution<T> const & d)
{
	return (std::accumulate(d.begin(), d.end(), T(0)));
}

template <typename T>
T median(Distribution<T> const & d)
{
	Distribution<T> tmp(d);

	std::sort(tmp.begin(), tmp.end());

	return (tmp.empty() ? T(0) : tmp[tmp.size() / 2]);
}

template <typename T>
T mean(Distribution<T> const & d)
{
	return (d.size() ? sum(d) / T(d.size()) : T(0));
}

template <typename T>
T mean(Distribution<T> const & values, Distribution<T> const & factors)
{
	assert(values.size() == factors.size());

	T accumulator = 0;
	T divider = sum(factors);

	if (divider) {
		auto it_v = values.cbegin();
		auto it_f = factors.cbegin();
		for (; it_v != values.cend(); it_v++, it_f++)
			accumulator += (*it_v) * (*it_f);
		accumulator /= divider;
	}

	return (accumulator);
}

template <typename T>
T geometric_mean(Distribution<T> const & d)
{
	return (d.size() ? std::pow(double(sum(d)), 1.0 / double(d.size())) : T(0));
}



template <typename T, class U>
static Distribution<T> double_for_each(Distribution<T> const & a,
                                       Distribution<T> const & b,
                                       U functor)
{
	assert(a.size() == b.size());

	Distribution<T> tmp(a);
	auto it_tmp = tmp.begin();
	auto it_b = b.cbegin();

	for (; it_b != b.cend(); it_tmp++, it_b++)
		functor(it_tmp, it_b);

	return (tmp);
}



template <typename T>
Distribution<T>  add_distribution(Distribution<T> const & a, Distribution<T> const & b)
{
	auto adder = [](Distribution<T>::iterator left, Distribution<T>::const_iterator right)
	{
		*left += *right;
	};
	return (double_for_each(a, b, adder));
}

template <typename T>
Distribution<T>  sub_distribution(Distribution<T> const & a, Distribution<T> const & b)
{
	auto subber = [](Distribution<T>::iterator left, Distribution<T>::const_iterator right)
	{
		*left -= *right;
	};
	return (double_for_each(a, b, subber));
}

template <typename T>
Distribution<T>  mul_distribution(Distribution<T> const & a, Distribution<T> const & b)
{
	auto multer = [](Distribution<T>::iterator left, Distribution<T>::const_iterator right)
	{
		*left *= *right;
	};
	return (double_for_each(a, b, multer));
}

template <typename T>
Distribution<T>  div_distribution(Distribution<T> const & a, Distribution<T> const & b)
{
	auto divider = [](Distribution<T>::iterator left, Distribution<T>::const_iterator right)
	{
		*left /= *right;
	};
	return (double_for_each(a, b, divider));
}
