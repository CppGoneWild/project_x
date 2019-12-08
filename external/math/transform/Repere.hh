#ifndef MATH_REPERE_HH__
#define MATH_REPERE_HH__


#include "../Vector.hh"
#include "../Equation.hh"
#include "../ParametricEquation.hh"
#include "Rotation.hh"


namespace math
{
namespace transform
{


template <class T, class U = double>
class ParametricRepere : public ParametricEquation<Vector<T>, Vector<T>, Vector<T>, U, U>
{
public:
	ParametricRepere()                               = default;
	ParametricRepere(ParametricRepere<T, U> const &) = default;
	ParametricRepere(ParametricRepere<T, U> &&)      = default;
	virtual ~ParametricRepere() override             = default;

	ParametricRepere<T, U> & operator=(ParametricRepere<T, U> const &) = default;
	ParametricRepere<T, U> & operator=(ParametricRepere<T, U> &&)      = default;

	virtual Vector<T> operator()(Vector<T> point, Vector<T> d_origin, U d_scale, U d_angle) const override;
};


template <class T, class U = double>
class Repere : public Equation<Vector<T>>
{
public:
	Repere()                     = default;
	Repere(Repere<T, U> const &) = default;
	Repere(Repere<T, U> &&)      = default;
	virtual ~Repere() override   = default;

	Repere<T, U> & operator=(Repere<T, U> const &) = default;
	Repere<T, U> & operator=(Repere<T, U> &&)      = default;

	Repere(Vector<T> const & d_origin, U d_scale, U d_angle);

	virtual Vector<T> operator()(Vector<T>) const override;

	Vector<T> const & dest_origin() const;
	Vector<T> & dest_origin();

	U dest_scale() const;
	U & dest_scale();

	U dest_angle() const;
	U & dest_angle();

	Repere<T, U> reciproc() const;

private:
	Vector<T> _dest_origin;
	U _dest_scale;
	U _dest_angle;
};


#include "Repere.ipp"


} // transform
} // math


#endif // MATH_REPERE_HH__
