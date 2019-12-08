#ifndef MATH_VECTOR_HH__
#define MATH_VECTOR_HH__


#include <cmath> // std::sqrt, std::hypot



namespace math
{


//                      _    __          __
//                     | |  / /__  _____/ /_____  _____
//                     | | / / _ \/ ___/ __/ __ \/ ___/
//                     | |/ /  __/ /__/ /_/ /_/ / /
//                     |___/\___/\___/\__/\____/_/
//                     


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


//                                        __  _
//           ____  ____  ___  _________ _/ /_(_)___  ____  _____
//          / __ \/ __ \/ _ \/ ___/ __ `/ __/ / __ \/ __ \/ ___/
//         / /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ / / / (__  )
//         \____/ .___/\___/_/   \__,_/\__/_/\____/_/ /_/____/
//             /_/
//         


template <class T>
T lenghtSquared(Vector<T> const &);

template <class T>
double lenght(Vector<T> const &);

template <class T>
void normalise(Vector<T> &);

template <class T>
Vector<T> getNormed(Vector<T> const &);


//                                __           __
//                    _________ _/ /______  __/ /____
//                   / ___/ __ `/ / ___/ / / / / ___/
//                  / /__/ /_/ / / /__/ /_/ / (__  )
//                  \___/\__,_/_/\___/\__,_/_/____/
//                  


template <class T, class U>
T distanceSquared(Vector<T> const &, Vector<U> const &);

template <class T, class U>
double distance(Vector<T> const &, Vector<U> const &);

template <class T, class U>
double dot_product(Vector<T> const &, Vector<U> const &);

template <class T, class U>
double cross_product(Vector<T> const &, Vector<U> const &);


#include "Vector.ipp"


} // math



#endif // MATH_VECTOR_HH__
