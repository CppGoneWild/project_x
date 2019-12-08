#ifndef MATH_ROTATION_HH__
#define MATH_ROTATION_HH__


#include "../Vector.hh"
#include "../Equation.hh"
#include "../ParametricEquation.hh"


#include <cmath> // trigo


namespace math
{
namespace transform
{


template <class T, class U = double>
class ParametricRotation : public ParametricEquation<Vector<T>, Vector<T>, U>
{
public:
	ParametricRotation()                                 = default;
	ParametricRotation(ParametricRotation<T, U> const &) = default;
	ParametricRotation(ParametricRotation<T, U> &&)      = default;
	virtual ~ParametricRotation() override               = default;

	ParametricRotation<T, U> & operator=(ParametricRotation<T, U> const &) = default;
	ParametricRotation<T, U> & operator=(ParametricRotation<T, U> &&)      = default;

	virtual Vector<T> operator()(Vector<T>, U) const override;
};


template <class T, class U = double>
class Rotation : public Equation<Vector<T>>
{
public:
	Rotation()                       = default;
	Rotation(Rotation<T, U> const &) = default;
	Rotation(Rotation<T, U> &&)      = default;
	virtual ~Rotation() override     = default;

	Rotation<T, U> & operator=(Rotation<T, U> const &) = default;
	Rotation<T, U> & operator=(Rotation<T, U> &&)      = default;

	Rotation(U);

	virtual Vector<T> operator()(Vector<T>) const override;

	U angle() const;
	U & angle();

	Rotation<T, U> reciproc() const;

private:
	U _angle;
};


#include "Rotation.ipp"


} // transform
} // math


#endif // MATH_ROTATION_HH__
