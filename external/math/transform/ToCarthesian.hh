#ifndef MATH_TRANSFORM_TOCARTHESIAN_HH__
#define MATH_TRANSFORM_TOCARTHESIAN_HH__


#include "../Vector.hh"
#include "../Polar.hh"
#include "../Equation.hh"


#include <cmath> // trigo



namespace math
{
namespace transform
{


template <class T, class U = double>
class ToCarthesian : public Equation<Polar<T, U>, Vector<T>>
{
public:
	ToCarthesian()                           = default;
	ToCarthesian(ToCarthesian<T, U> const &) = default;
	ToCarthesian(ToCarthesian<T, U> &&)      = default;
	virtual ~ToCarthesian() override         = default;

	ToCarthesian<T, U> & operator=(ToCarthesian<T, U> const &) = default;
	ToCarthesian<T, U> & operator=(ToCarthesian<T, U> &&)      = default;

	virtual Vector<T> operator()(Polar<T, U>) const override;
};


template <class T, class U>
Vector<T> ToCarthesian<T, U>::operator()(Polar<T, U> p) const
{
	Vector<T> res;

	if (p.radius != Polar<T, U>().radius) {
		res.x = p.radius * std::cos(p.theta);
		res.y = p.radius * std::sin(p.theta);
	}

	return (res);
}


} // transform
} // math


#endif // MATH_TRANSFORM_TOCARTHESIAN_HH__
