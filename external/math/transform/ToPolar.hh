#ifndef MATH_TRANSFORM_TOPOLAR_HH__
#define MATH_TRANSFORM_TOPOLAR_HH__


#include "../Vector.hh"
#include "../Polar.hh"
#include "../Equation.hh"


#include <cmath> // trigo



namespace math
{
namespace transform
{


template <class T, class U = double>
class ToPolar : public Equation<Vector<T>, Polar<T, U>>
{
public:
	ToPolar()                      = default;
	ToPolar(ToPolar<T, U> const &) = default;
	ToPolar(ToPolar<T, U> &&)      = default;
	virtual ~ToPolar() override    = default;

	ToPolar<T, U> & operator=(ToPolar<T, U> const &) = default;
	ToPolar<T, U> & operator=(ToPolar<T, U> &&)      = default;

	virtual Polar<T, U> operator()(Vector<T>) const override;
};


template <class T, class U>
Polar<T, U> ToPolar<T, U>::operator()(Vector<T> v) const
{
	Polar<T, U> res;
	res.radius = std::hypot(v.x, v.y);

	if (res.radius == 0)
		res.theta = 0;
	else if (v.y < 0)
		res.theta = -(std::acos(v.x, res.radius));
	else
		res.theta = std::acos(v.x, res.radius);

	return (res);
}


} // transform
} // math


#endif // MATH_TRANSFORM_TOPOLAR_HH__
