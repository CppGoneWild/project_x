#ifndef MATH_POLAR_HH__
#define MATH_POLAR_HH__


#define _USE_MATH_DEFINES // for M_PI
#include <cmath> // std::fmod and M_PI


namespace math
{


template <class T, class U = double>
struct Polar
{
	U theta = U(0);
	T radius = T(0);

	Polar() = default;
	~Polar() = default;
	
	template <class V, class W> Polar(Polar<V, W> const &);
	template <class V, class W> Polar(Polar<V, W> &&);

	template <class V, class W> Polar<T, U> & operator=(Polar<V, W> const &);
	template <class V, class W> Polar<T, U> & operator=(Polar<V, W> &&);

	Polar(U, T);

	template <class V, class W> bool operator==(Polar<V, W> const &) const;
	template <class V, class W> bool operator!=(Polar<V, W> const &) const;
	template <class V, class W> bool operator< (Polar<V, W> const &) const;
	template <class V, class W> bool operator> (Polar<V, W> const &) const;
	template <class V, class W> bool operator<=(Polar<V, W> const &) const;
	template <class V, class W> bool operator>=(Polar<V, W> const &) const;

//	void operator+=(T);
//	void operator-=(T);
//	void operator*=(T);
//	void operator/=(T);
//	void operator%=(T);
//
//	template <class U> void operator+=(Polar<U> const &);
//	template <class U> void operator-=(Polar<U> const &);
//	template <class U> void operator*=(Polar<U> const &);
//	template <class U> void operator/=(Polar<U> const &);
//	template <class U> void operator%=(Polar<U> const &);
//
//	template <class U> Polar<T> operator+(U const &) const;
//	template <class U> Polar<T> operator-(U const &) const;
//	template <class U> Polar<T> operator*(U const &) const;
//	template <class U> Polar<T> operator/(U const &) const;
//	template <class U> Polar<T> operator%(U const &) const;

	void reduce();
	Polar<T, U> reduce() const;	
};


#include "Polar.ipp"


} // math


#endif // TOOLS_MATH_POLAR_HH__
