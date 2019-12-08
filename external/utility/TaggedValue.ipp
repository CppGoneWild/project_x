template <class TAG, class T>
template <class U>
TaggedValue<TAG, T>::TaggedValue(TaggedValue<TAG, U> const & oth)
: _value(oth._value)
{}

template <class TAG, class T>
template <class U>
TaggedValue<TAG, T>::TaggedValue(TaggedValue<TAG, U> && oth)
: _value(oth._value)
{}

template <class TAG, class T>
template <class U>
TaggedValue<TAG, T> & TaggedValue<TAG, T>::operator=(TaggedValue<TAG, U> const & oth)
{
	_value = oth._value;
	return (*this);
}

template <class TAG, class T>
template <class U>
TaggedValue<TAG, T> & TaggedValue<TAG, T>::operator=(TaggedValue<TAG, U> && oth)
{
	_value = oth._value;
	return (*this);
}

template <class TAG, class T>
TaggedValue<TAG, T>::TaggedValue(T v)
: _value(v)
{}

template <class TAG, class T>
T TaggedValue<TAG, T>::value() const
{
	return (_value);
}

template <class TAG, class T>
void TaggedValue<TAG, T>::value(T v)
{
	_value = v;
}

template <class TAG, class T>
template <class U>
bool TaggedValue<TAG, T>::operator==(TaggedValue<TAG, U> const & oth) const
{
	return (_value == oth._value);
}

template <class TAG, class T>
template <class U>
bool TaggedValue<TAG, T>::operator!=(TaggedValue<TAG, U> const & oth) const
{
	return (_value != oth._value);
}

template <class TAG, class T>
template <class U>
bool TaggedValue<TAG, T>::operator< (TaggedValue<TAG, U> const & oth) const
{
	return (_value < oth._value);
}

template <class TAG, class T>
template <class U>
bool TaggedValue<TAG, T>::operator> (TaggedValue<TAG, U> const & oth) const
{
	return (_value > oth._value);
}

template <class TAG, class T>
template <class U>
bool TaggedValue<TAG, T>::operator<=(TaggedValue<TAG, U> const & oth) const
{
	return (_value <= oth._value);
}

template <class TAG, class T>
template <class U>
bool TaggedValue<TAG, T>::operator>=(TaggedValue<TAG, U> const & oth) const
{
	return (_value >= oth._value);
}

template <class TAG, class T>
void TaggedValue<TAG, T>::operator+=(T v)
{
	_value += v;
}

template <class TAG, class T>
void TaggedValue<TAG, T>::operator-=(T v)
{
	_value -= v;
}

template <class TAG, class T>
void TaggedValue<TAG, T>::operator*=(T v)
{
	_value *= v;
}

template <class TAG, class T>
void TaggedValue<TAG, T>::operator/=(T v)
{
	_value /= v;
}

template <class TAG, class T>
void TaggedValue<TAG, T>::operator%=(T v)
{
	_value %= v;
}

template <class TAG, class T>
template <class U>
void TaggedValue<TAG, T>::operator+=(TaggedValue<TAG, U> const & oth)
{
	_value += oth._value;
}

template <class TAG, class T>
template <class U>
void TaggedValue<TAG, T>::operator-=(TaggedValue<TAG, U> const & oth)
{
	_value -= oth._value;
}

template <class TAG, class T>
template <class U>
void TaggedValue<TAG, T>::operator*=(TaggedValue<TAG, U> const & oth)
{
	_value *= oth._value;
}

template <class TAG, class T>
template <class U>
void TaggedValue<TAG, T>::operator/=(TaggedValue<TAG, U> const & oth)
{
	_value /= oth._value;
}

template <class TAG, class T>
template <class U>
void TaggedValue<TAG, T>::operator%=(TaggedValue<TAG, U> const & oth)
{
	_value %= oth._value;
}

template <class TAG, class T>
template <class U>
TaggedValue<TAG, T> TaggedValue<TAG, T>::operator+(U const & oth) const
{
	TaggedValue<TAG, T> tmp(*this);
	tmp += oth;
	return (tmp);
}

template <class TAG, class T>
template <class U>
TaggedValue<TAG, T> TaggedValue<TAG, T>::operator-(U const & oth) const
{
	TaggedValue<TAG, T> tmp(*this);
	tmp -= oth;
	return (tmp);
}

template <class TAG, class T>
template <class U>
TaggedValue<TAG, T> TaggedValue<TAG, T>::operator*(U const & oth) const
{
	TaggedValue<TAG, T> tmp(*this);
	tmp *= oth;
	return (tmp);
}

template <class TAG, class T>
template <class U>
TaggedValue<TAG, T> TaggedValue<TAG, T>::operator/(U const & oth) const
{
	TaggedValue<TAG, T> tmp(*this);
	tmp /= oth;
	return (tmp);
}

template <class TAG, class T>
template <class U>
TaggedValue<TAG, T> TaggedValue<TAG, T>::operator%(U const & oth) const
{
	TaggedValue<TAG, T> tmp(*this);
	tmp %= oth;
	return (tmp);
}
