/*                      _    __          __
                       | |  / /__  _____/ /_____  _____
                       | | / / _ \/ ___/ __/ __ \/ ___/
                       | |/ /  __/ /__/ /_/ /_/ / /
                       |___/\___/\___/\__/\____/_/
                       
*/



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



////////////////////////////////////////////////////////////////////////////////
//////                             operations                             //////
////////////////////////////////////////////////////////////////////////////////



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



////////////////////////////////////////////////////////////////////////////////
//////                              calculs                               //////
////////////////////////////////////////////////////////////////////////////////



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



/*
                         ____        __
                        / __ \____  / /___ ______
                       / /_/ / __ \/ / __ `/ ___/
                      / ____/ /_/ / / /_/ / /
                     /_/    \____/_/\__,_/_/

*/



template <class T>
static T _reduce_at_2pi(T x)
{
	return (std::fmod(x, 2.0 * M_PI));
}



template <class T, class U>
template <class V, class W>
Polar<T, U>::Polar(Polar<V, W> const & oth)
: theta(oth.theta), radius(oth.radius)
{}

template <class T, class U>
template <class V, class W>
Polar<T, U>::Polar(Polar<V, W> && oth)
: theta(oth.theta), radius(oth.radius)
{}

template <class T, class U>
template <class V, class W>
Polar<T, U> & Polar<T, U>::operator=(Polar<V, W> const & oth)
{
	if (this != &oth) {
		theta = oth.theta;
		radius = oth.radius;
	}
	return (*this);
}

template <class T, class U>
template <class V, class W>
Polar<T, U> & Polar<T, U>::operator=(Polar<V, W> && oth)
{
	if (this != &oth) {
		theta = oth.theta;
		radius = oth.radius;
	}
	return (*this);
}

template <class T, class U>
Polar<T, U>::Polar(U t, T r)
: theta(t), radius(r)
{}

template <class T, class U>
template <class V, class W>
bool Polar<T, U>::operator==(Polar<V, W> const & oth) const
{
	return (radius == oth.radius &&
	        _reduce_at_2pi(theta) == _reduce_at_2pi(oth.theta));
}

template <class T, class U>
template <class V, class W>
bool Polar<T, U>::operator!=(Polar<V, W> const & oth) const
{
	return (radius != oth.radius ||
	        _reduce_at_2pi(theta) != _reduce_at_2pi(oth.theta));
}

template <class T, class U>
template <class V, class W>
bool Polar<T, U>::operator< (Polar<V, W> const & oth) const
{
	return (radius < oth.radius &&
	        _reduce_at_2pi(theta) < _reduce_at_2pi(oth.theta));
}

template <class T, class U>
template <class V, class W>
bool Polar<T, U>::operator> (Polar<V, W> const & oth) const
{
	return (radius > oth.radius &&
	        _reduce_at_2pi(theta) > _reduce_at_2pi(oth.theta));
}

template <class T, class U>
template <class V, class W>
bool Polar<T, U>::operator<=(Polar<V, W> const & oth) const
{
	return (radius <= oth.radius &&
	        _reduce_at_2pi(theta) <= _reduce_at_2pi(oth.theta));
}

template <class T, class U>
template <class V, class W>
bool Polar<T, U>::operator>=(Polar<V, W> const & oth) const
{
	return (radius >= oth.radius &&
	        _reduce_at_2pi(theta) >= _reduce_at_2pi(oth.theta));
}

template <class T, class U>
void Polar<T, U>::reduce()
{
	theta = _reduce_at_2pi(theta);
}

template <class T, class U>
Polar<T, U> Polar<T, U>::reduce() const
{
	Polar<T, U> tmp(*this);
	tmp.reduce();
	return (tmp);
}



/*
     __                        ____                           __  _
    / /__________ _____  _____/ __/___  _________ ___  ____ _/ /_(_)___  ____
   / __/ ___/ __ `/ __ \/ ___/ /_/ __ \/ ___/ __ `__ \/ __ `/ __/ / __ \/ __ \
  / /_/ /  / /_/ / / / (__  ) __/ /_/ / /  / / / / / / /_/ / /_/ / /_/ / / / /
  \__/_/   \__,_/_/ /_/____/_/  \____/_/  /_/ /_/ /_/\__,_/\__/_/\____/_/ /_/
  
*/



template <class T, class U, class V>
Vector<T> to_carthesian(Polar<U, V> const & p)
{
	Vector<T> res;

	if (p.radius != Polar<U, V>().radius) {
		res.x = p.radius * std::cos(p.theta);
		res.y = p.radius * std::sin(p.theta);
	}

	return (res);
}

template <class T, class U, class V>
Polar<T, U> to_polar(Vector<V> const & v)
{
	assert(false);
	Polar<T, U> res;
	res.radius = std::hypot(v.x, v.y);
	res.theta = std::atan2(v.y, v.x);
	return (res);
}
