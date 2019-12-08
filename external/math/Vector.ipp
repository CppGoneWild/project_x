
//                      _    __          __
//                     | |  / /__  _____/ /_____  _____
//                     | | / / _ \/ ___/ __/ __ \/ ___/
//                     | |/ /  __/ /__/ /_/ /_/ / /
//                     |___/\___/\___/\__/\____/_/
//                     

template <class T>
Vector<T>::Vector(T value)
	: x(value), y(value)
{}

template <class T>
Vector<T>::Vector(T x, T y)
	: x(x), y(y)
{}

template <class T>
template <class U>
Vector<T>::Vector(Vector<U> const & other)
	: x(T(other.x)), y(T(other.y))
{}

template <class T>
template <class U, class V>
Vector<T>::Vector(Vector<U> const & a, Vector<V> const & b)
	: x(T(b.x) - T(a.x)), y(T(b.y) - T(a.y))
{}

template <class T>
template <class U>
bool Vector<T>::operator==(Vector<U> const & other) const
{
	return (x == T(other.x) && y == T(other.y));
}

template <class T>
template <class U>
bool Vector<T>::operator!=(Vector<U> const & other) const
{
	return (x != T(other.x) || y != T(other.y));
}

template <class T>
template <class U>
bool Vector<T>::operator<(Vector<U> const & other) const
{
	return (x < T(other.x) && y < T(other.y));
}

template <class T>
template <class U>
Vector<T> & Vector<T>::operator=(Vector<U> const & other)
{
	x = T(other.x);
	y = T(other.y);
	return (*this);
}

template <class T>
void Vector<T>::operator+=(T value)
{
	x += value;
	y += value;
}

template <class T>
void Vector<T>::operator-=(T value)
{
	x -= value;
	y -= value;
}

template <class T>
void Vector<T>::operator*=(T value)
{
	x *= value;
	y *= value;
}

template <class T>
void Vector<T>::operator/=(T value)
{
	x /= value;
	y /= value;
}

template <class T>
template <class U>
void Vector<T>::operator+=(Vector<U> const & other)
{
	x += T(other.x);
	y += T(other.y);
}

template <class T>
template <class U>
void Vector<T>::operator-=(Vector<U> const & other)
{
	x -= T(other.x);
	y -= T(other.y);
}

template <class T>
template <class U>
void Vector<T>::operator*=(Vector<U> const & other)
{
	x *= T(other.x);
	y *= T(other.y);
}

template <class T>
template <class U>
void Vector<T>::operator/=(Vector<U> const & other)
{
	x /= T(other.x);
	y /= T(other.y);
}

template <class T>
template <class U>
Vector<T> Vector<T>::operator+(U const & value) const
{
	Vector<T> tmp(*this);
	tmp += value;
	return (tmp);
}

template <class T>
template <class U>
Vector<T> Vector<T>::operator-(U const & value) const
{
	Vector<T> tmp(*this);
	tmp -= value;
	return (tmp);
}

template <class T>
template <class U>
Vector<T> Vector<T>::operator*(U const & value) const
{
	Vector<T> tmp(*this);
	tmp *= value;
	return (tmp);
}

template <class T>
template <class U>
Vector<T> Vector<T>::operator/(U const & value) const
{
	Vector<T> tmp(*this);
	tmp /= value;
	return (tmp);
}


//                                         __  _
//            ____  ____  ___  _________ _/ /_(_)___  ____  _____
//           / __ \/ __ \/ _ \/ ___/ __ `/ __/ / __ \/ __ \/ ___/
//          / /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ / / / (__  )
//          \____/ .___/\___/_/   \__,_/\__/_/\____/_/ /_/____/
//              /_/
//          


template <class T>
T lenghtSquared(Vector<T> const & a)
{
	return (a.x * a.x + a.y * a.y);
}

template <class T>
double lenght(Vector<T> const & a)
{
	return (std::hypot(a.x, a.y));
}

template <class T>
void normalise(Vector<T> & a)
{
	double d = lenght(a);
	if (d != 0) {
		a.x /= d;
		a.y /= d;		
	}
}

template <class T>
Vector<T> getNormed(Vector<T> const & a)
{
	Vector<T> res(a);
	normalise(res);
	return (res);
}


//                                __           __
//                    _________ _/ /______  __/ /____
//                   / ___/ __ `/ / ___/ / / / / ___/
//                  / /__/ /_/ / / /__/ /_/ / (__  )
//                  \___/\__,_/_/\___/\__,_/_/____/
//                  



template <class T, class U>
T distanceSquared(Vector<T>const & a, Vector<U> const & b)
{
	Vector<T> tmp(a, b);
	return (lenghtSquared(tmp));
}

template <class T, class U>
double distance(Vector<T>const & a, Vector<U> const & b)
{
	Vector<T> tmp(a, b);
	return (lenght(tmp));
}

template <class T, class U>
double dot_product(Vector<T>const & a, Vector<U> const & b)
{
	return (a.x * b.x + a.y * b.y);
}

template <class T, class U>
double cross_product(Vector<T>const & a, Vector<U> const & b)
{
	return (a.x * b.y + a.y * b.x);
}
