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
