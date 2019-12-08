/*
    ____                                  __       _      ____        __        __  _
   / __ \____ __________ _____ ___  ___  / /______(_)____/ __ \____  / /_____ _/ /_(_)___  ____
  / /_/ / __ `/ ___/ __ `/ __ `__ \/ _ \/ __/ ___/ / ___/ /_/ / __ \/ __/ __ `/ __/ / __ \/ __ \
 / ____/ /_/ / /  / /_/ / / / / / /  __/ /_/ /  / / /__/ _, _/ /_/ / /_/ /_/ / /_/ / /_/ / / / /
/_/    \__,_/_/   \__,_/_/ /_/ /_/\___/\__/_/  /_/\___/_/ |_|\____/\__/\__,_/\__/_/\____/_/ /_/
*/

template <class T, class U>
Vector<T> ParametricRotation<T, U>::operator()(Vector<T> v, U a) const
{
	Vector<T> res(v);

	res.x = v.x * std::cos(a) - v.y * std::sin(a);
	res.x = v.x * std::sin(a) + v.y * std::cos(a);

	return (res);
}

/*
                         ____        __        __  _
                        / __ \____  / /_____ _/ /_(_)___  ____
                       / /_/ / __ \/ __/ __ `/ __/ / __ \/ __ \
                      / _, _/ /_/ / /_/ /_/ / /_/ / /_/ / / / /
                     /_/ |_|\____/\__/\__,_/\__/_/\____/_/ /_/
*/

template <class T, class U>
Rotation<T, U>::Rotation(U a)
: _angle(std::fmod(a, M_PI * 2.0))
{}

template <class T, class U>
Vector<T> Rotation<T, U>::operator()(Vector<T> v) const
{
	static const ParametricRotation<T, U> eq;
	return (eq(v, _angle));
}

template <class T, class U>
U Rotation<T, U>::angle() const
{
	return (_angle);
}

template <class T, class U>
U & Rotation<T, U>::angle()
{
	return (_angle);
}

template <class T, class U>
Rotation<T, U> Rotation<T, U>::reciproc() const
{
	return (Rotation<T, U>(-_angle));
}
