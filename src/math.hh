#ifndef MATH_HH
#define MATH_HH


#define _USE_MATH_DEFINES // for M_PI
#include <cmath>          // sqrt, hypot, fmod, M_PI



/*
                        _    __          __
                       | |  / /__  _____/ /_____  _____
                       | | / / _ \/ ___/ __/ __ \/ ___/
                       | |/ /  __/ /__/ /_/ /_/ / /
                       |___/\___/\___/\__/\____/_/
                       
*/



template <class T>
struct Vector
{
	using Type_t = T;

	T x = 0;
	T y = 0;

	Vector() = default;
	Vector(Vector<T> const &) = default;
	Vector(Vector<T> &&) = default;
	Vector & operator=(Vector<T> const &) = default;
	Vector & operator=(Vector<T> &&) = default;

	explicit Vector(T);
	Vector(T, T);

	template <class U> explicit Vector(Vector<U> const &);
	template <class U, class V> Vector(Vector<U> const &, Vector<V> const &);
	template <class U> Vector<T> & operator=(Vector<U> const &);

	template <class U> bool operator==(Vector<U> const &) const;
	template <class U> bool operator!=(Vector<U> const &) const;

	template <class U> bool operator<(Vector<U> const &) const;

	void operator+=(T);
	void operator-=(T);
	void operator*=(T);
	void operator/=(T);

	template <class U> void operator+=(Vector<U> const &);
	template <class U> void operator-=(Vector<U> const &);
	template <class U> void operator*=(Vector<U> const &);
	template <class U> void operator/=(Vector<U> const &);

	template <class U> Vector<T> operator+(U const &) const;
	template <class U> Vector<T> operator-(U const &) const;
	template <class U> Vector<T> operator*(U const &) const;
	template <class U> Vector<T> operator/(U const &) const;
};



////////////////////////////////////////////////////////////////////////////////
//////                             operations                             //////
////////////////////////////////////////////////////////////////////////////////



template <class T>
T lenghtSquared(Vector<T> const &);

template <class T>
double lenght(Vector<T> const &);

template <class T>
void normalise(Vector<T> &);

template <class T>
Vector<T> getNormed(Vector<T> const &);



////////////////////////////////////////////////////////////////////////////////
//////                              calculs                               //////
////////////////////////////////////////////////////////////////////////////////



template <class T, class U>
T distanceSquared(Vector<T> const &, Vector<U> const &);

template <class T, class U>
double distance(Vector<T> const &, Vector<U> const &);

template <class T, class U>
double dot_product(Vector<T> const &, Vector<U> const &);

template <class T, class U>
double cross_product(Vector<T> const &, Vector<U> const &);



/*
                         ____        __
                        / __ \____  / /___ ______
                       / /_/ / __ \/ / __ `/ ___/
                      / ____/ /_/ / / /_/ / /
                     /_/    \____/_/\__,_/_/

*/



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

	void reduce();
	Polar<T, U> reduce() const;	
};


/*
     __                        ____                           __  _
    / /__________ _____  _____/ __/___  _________ ___  ____ _/ /_(_)___  ____
   / __/ ___/ __ `/ __ \/ ___/ /_/ __ \/ ___/ __ `__ \/ __ `/ __/ / __ \/ __ \
  / /_/ /  / /_/ / / / (__  ) __/ /_/ / /  / / / / / / /_/ / /_/ / /_/ / / / /
  \__/_/   \__,_/_/ /_/____/_/  \____/_/  /_/ /_/ /_/\__,_/\__/_/\____/_/ /_/
  
*/


template <class T, class U, class V>
Vector<T> to_carthesian(Polar<U, V> const & p);

template <class T, class U, class V>
Polar<T, U> to_polar(Vector<V> const & v);



#include "math.ipp"



#endif // MATH_HH
