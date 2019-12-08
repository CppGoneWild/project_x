#ifndef MATH_PARAMETRICEQUATION_HH__
#define MATH_PARAMETRICEQUATION_HH__


#include <tuple>


namespace math
{


template <class T, class... Args>
class ParametricEquation
{
public:
	using output_t         = T;
	using tuple_of_input_t = std::tuple<Args...>;

	virtual ~ParametricEquation() = default;

	virtual T operator()(Args...) const = 0;

protected:
	ParametricEquation()                    = default;
	ParametricEquation(ParametricEquation<T, Args...> const &) = default;
	ParametricEquation(ParametricEquation<T, Args...> &&)      = default;

	ParametricEquation<T, Args...> & operator=(ParametricEquation<T, Args...> const &) = default;
	ParametricEquation<T, Args...> & operator=(ParametricEquation<T, Args...> &&)      = default;
};


} // math

#endif // MATH_PARAMETRICEQUATION_HH__
