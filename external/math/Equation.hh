#ifndef MATH_EQUATION_HH__
#define MATH_EQUATION_HH__


#include "Vector.hh"

#include <array>
#include <functional> // std::not_equal_to


namespace math
{


template <class T, class U = T>
class Equation
{
public:
	using input_t  = T;
	using output_t = U;

	virtual ~Equation() = default;

	virtual U operator()(T) const = 0;

protected:
	Equation()                    = default;
	Equation(Equation<T, U> const &) = default;
	Equation(Equation<T, U> &&)      = default;

	Equation<T, U> & operator=(Equation<T, U> const &) = default;
	Equation<T, U> & operator=(Equation<T, U> &&)      = default;
};


template <class EQUATION, class NEQUAL = std::not_equal_to<typename EQUATION::input_t>>
class CachedEquation
{
public:
	using comparator_t = NEQUAL;
	using equation_t   = EQUATION;
	using input_t      = typename EQUATION::input_t;
	using output_t     = typename EQUATION::output_t;

	CachedEquation()                                 = default;
	CachedEquation(CachedEquation<EQUATION, NEQUAL> const &) = default;
	CachedEquation(CachedEquation<EQUATION, NEQUAL> &&)      = default;
	virtual ~CachedEquation()                        = default;

	CachedEquation<EQUATION, NEQUAL> & operator=(CachedEquation<EQUATION, NEQUAL> const &) = default;
	CachedEquation<EQUATION, NEQUAL> & operator=(CachedEquation<EQUATION, NEQUAL> &&)      = default;

	CachedEquation(equation_t const &, comparator_t const & nequal = NEQUAL());

	/// @toto Question ? Should it be const with mutable member.
	virtual output_t const & operator()(input_t);

	equation_t const & equation() const;
	output_t const & value() const;
	input_t const & last_param() const;

	equation_t & equation();
	output_t & value();
	input_t & last_param();

	bool equation_is_set() const;
	equation_t * set_equation(equation_t const &);
	equation_t * unset_equation();

	void reset_called_flag();

protected:
	NEQUAL _nequal = NEQUAL();
	equation_t * _equation = nullptr;
	bool _called = false;
	output_t _value;
	input_t _last_param;
};


template <class T, std::size_t N>
class Power : public Equation<T>
{
public:
	static constexpr std::size_t exponent = N;

	Power()                   = default;
	Power(Power<T, N> const &)= default;
	Power(Power<T, N> &&)     = default;
	virtual ~Power() override = default;

	Power<T, N> & operator=(Power<T, N> const &) = default;
	Power<T, N> & operator=(Power<T, N> &&)      = default;

	virtual T operator()(T) const override;
};



template <class T, std::size_t N>
class Polynom : public Equation<T>
{
public:
	using container_t = std::array<T, N + 1>;

	Polynom()                      = default;
	Polynom(Polynom<T, N> const &) = default;
	Polynom(Polynom<T, N> &&) = default;
	virtual ~Polynom() override = default;

	Polynom<T, N> & operator=(Polynom<T, N> const &) = default;
	Polynom<T, N> & operator=(Polynom<T, N> &&) = default;

	Polynom(container_t const &);
	Polynom(container_t &&);

	virtual T operator()(T) const override;

	container_t const & coefs() const;
	container_t & coefs();

private:
	container_t _coefs;
};


#include "Equation.ipp"


} // math


#endif // MATH_EQUATION_HH__
