/*
     ______           __             ________                  __  _
    / ____/___ ______/ /_  ___  ____/ / ____/___ ___  ______ _/ /_(_)___  ____
   / /   / __ `/ ___/ __ \/ _ \/ __  / __/ / __ `/ / / / __ `/ __/ / __ \/ __ \
  / /___/ /_/ / /__/ / / /  __/ /_/ / /___/ /_/ / /_/ / /_/ / /_/ / /_/ / / / /
  \____/\__,_/\___/_/ /_/\___/\__,_/_____/\__, /\__,_/\__,_/\__/_/\____/_/ /_/
                                            /_/
*/


template <class EQUATION, class NEQUAL>
CachedEquation<EQUATION, NEQUAL>::CachedEquation(equation_t const & e, comparator_t const & nequal)
: _nequal(nequal),
  _equation(&e),
  _called(false),
  _value(),
  _last_param()
{}

template <class EQUATION, class NEQUAL>
typename CachedEquation<EQUATION, NEQUAL>::output_t const & CachedEquation<EQUATION, NEQUAL>::operator()(input_t i)
{
	assert(equation_is_set());
	if (!_called || _nequal(i, _last_param)) {
		_last_param = i;
		_value = (*_equation)(i);
		_called = true;
	}
	return (_value);
}

template <class EQUATION, class NEQUAL>
typename CachedEquation<EQUATION, NEQUAL>::equation_t const & CachedEquation<EQUATION, NEQUAL>::equation() const
{
	assert(equation_is_set());
	return (*_equation);
}

template <class EQUATION, class NEQUAL>
typename CachedEquation<EQUATION, NEQUAL>::output_t const & CachedEquation<EQUATION, NEQUAL>::value() const
{
	return (_value);
}

template <class EQUATION, class NEQUAL>
typename CachedEquation<EQUATION, NEQUAL>::input_t const & CachedEquation<EQUATION, NEQUAL>::last_param() const
{
	return (_last_param);
}

template <class EQUATION, class NEQUAL>
typename CachedEquation<EQUATION, NEQUAL>::equation_t & CachedEquation<EQUATION, NEQUAL>::equation()
{
	assert(equation_is_set());
	return (*_equation);
}

template <class EQUATION, class NEQUAL>
typename CachedEquation<EQUATION, NEQUAL>::output_t & CachedEquation<EQUATION, NEQUAL>::value()
{
	return (_value);
}

template <class EQUATION, class NEQUAL>
typename CachedEquation<EQUATION, NEQUAL>::input_t & CachedEquation<EQUATION, NEQUAL>::last_param()
{
	return (_last_param);
}

template <class EQUATION, class NEQUAL>
bool CachedEquation<EQUATION, NEQUAL>::equation_is_set() const
{
	return (_equation != nullptr);
}

template <class EQUATION, class NEQUAL>
typename CachedEquation<EQUATION, NEQUAL>::equation_t * CachedEquation<EQUATION, NEQUAL>::set_equation(equation_t const & e)
{
	CachedEquation<EQUATION, NEQUAL>::equation_t * old = _equation;
	_equation = &e;
	_called = false;
	return (old);
}

template <class EQUATION, class NEQUAL>
typename CachedEquation<EQUATION, NEQUAL>::equation_t * CachedEquation<EQUATION, NEQUAL>::unset_equation()
{
	CachedEquation<EQUATION, NEQUAL>::equation_t * old = _equation;
	_equation = nullptr;
	_called = false;
	return (old);
}

template <class EQUATION, class NEQUAL>
void CachedEquation<EQUATION, NEQUAL>::reset_called_flag()
{
	_called = false;
}


/*
                          ____
                         / __ \____ _      _____  _____
                        / /_/ / __ \ | /| / / _ \/ ___/
                       / ____/ /_/ / |/ |/ /  __/ /
                      /_/    \____/|__/|__/\___/_/
*/

template <class T, std::size_t N>
static T _calc_power(T x)
{
	if constexpr (N == 0) {
		return (T(1));
	}
	else if (N == 1) {
		return (x);
	}
	else {
		return (x * _calc_power<N - 1>(x));
	}
}


template <class T, std::size_t N>
T Power<T, N>::operator()(T x) const
{
	return (_calc_power<T, N>(x));
}


/*
                  ____        __
                 / __ \____  / /_  ______  ____  ____ ___
                / /_/ / __ \/ / / / / __ \/ __ \/ __ `__ \
               / ____/ /_/ / / /_/ / / / / /_/ / / / / / /
              /_/    \____/_/\__, /_/ /_/\____/_/ /_/ /_/
                            /____/
*/


template <class T, std::size_t N>
static T _calc_polynom(T x, T const * coefs)
{
	if constexpr (N == 0) {
		return (coefs[0]);
	}
	else {
		return (coefs[0] * _calc_power<T, N - 1>(x) + _calc_polynom<T, N - 1>(x, coefs + 1));
	}
}

template <class T, std::size_t N>
Polynom<T, N>::Polynom(container_t const & c)
: _coefs(c)
{}

template <class T, std::size_t N>
Polynom<T, N>::Polynom(container_t && c)
: _coefs(c)
{}

template <class T, std::size_t N>
T Polynom<T, N>::operator()(T x) const
{
	return (_calc_polynom<T, N + 1>(x, _coefs.data()));
}

template <class T, std::size_t N>
typename Polynom<T, N>::container_t const & Polynom<T, N>::coefs() const
{
	return (_coefs);
}

template <class T, std::size_t N>
typename Polynom<T, N>::container_t & Polynom<T, N>::coefs()
{
	return (_coefs);
}
