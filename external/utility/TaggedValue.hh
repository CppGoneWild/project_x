#ifndef UTILITY_TAGGEDVALUE_HH__
#define UTILITY_TAGGEDVALUE_HH__



namespace utility
{


template <class TAG, class T>
class TaggedValue
{
public:
	using type_t = T;
	using tag_t = TAG;

	TaggedValue() = default;
	~TaggedValue() = default;

	template <class U> TaggedValue(TaggedValue<TAG, U> const &);
	template <class U> TaggedValue(TaggedValue<TAG, U> &&);

	template <class U> TaggedValue<TAG, T> & operator=(TaggedValue<TAG, U> const &);
	template <class U> TaggedValue<TAG, T> & operator=(TaggedValue<TAG, U> &&);

	explicit TaggedValue(T);

	T value() const;
	void value(T);

	template <class U> bool operator==(TaggedValue<TAG, U> const &) const;
	template <class U> bool operator!=(TaggedValue<TAG, U> const &) const;
	template <class U> bool operator< (TaggedValue<TAG, U> const &) const;
	template <class U> bool operator> (TaggedValue<TAG, U> const &) const;
	template <class U> bool operator<=(TaggedValue<TAG, U> const &) const;
	template <class U> bool operator>=(TaggedValue<TAG, U> const &) const;

	void operator+=(T);
	void operator-=(T);
	void operator*=(T);
	void operator/=(T);
	void operator%=(T);

	template <class U> void operator+=(TaggedValue<TAG, U> const &);
	template <class U> void operator-=(TaggedValue<TAG, U> const &);
	template <class U> void operator*=(TaggedValue<TAG, U> const &);
	template <class U> void operator/=(TaggedValue<TAG, U> const &);
	template <class U> void operator%=(TaggedValue<TAG, U> const &);

	template <class U> TaggedValue<TAG, T> operator+(U const &) const;
	template <class U> TaggedValue<TAG, T> operator-(U const &) const;
	template <class U> TaggedValue<TAG, T> operator*(U const &) const;
	template <class U> TaggedValue<TAG, T> operator/(U const &) const;
	template <class U> TaggedValue<TAG, T> operator%(U const &) const;

private:
	T _value = T(0);
};


#include "TaggedValue.ipp"


} // utility



#endif // UTILITY_TAGGEDVALUE_HH__
