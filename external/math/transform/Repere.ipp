/*
    ____                                  __       _      ____
   / __ \____ __________ _____ ___  ___  / /______(_)____/ __ \___  ____  ___  ________
  / /_/ / __ `/ ___/ __ `/ __ `__ \/ _ \/ __/ ___/ / ___/ /_/ / _ \/ __ \/ _ \/ ___/ _ \
 / ____/ /_/ / /  / /_/ / / / / / /  __/ /_/ /  / / /__/ _, _/  __/ /_/ /  __/ /  /  __/
/_/    \__,_/_/   \__,_/_/ /_/ /_/\___/\__/_/  /_/\___/_/ |_|\___/ .___/\___/_/   \___/
                                                                /_/
*/


template <class T, class U>
Vector<T> ParametricRepere<T, U>::operator()(Vector<T> point, Vector<T> d_origin, U d_scale, U d_angle) const
{
	static const ParametricRotation<T, U> eq;

	Vector<T> res(point);

	res += d_origin;
	res *= d_scale;

	return (eq(res, d_angle));
}


/*
                            ____
                           / __ \___  ____  ___  ________
                          / /_/ / _ \/ __ \/ _ \/ ___/ _ \
                         / _, _/  __/ /_/ /  __/ /  /  __/
                        /_/ |_|\___/ .___/\___/_/   \___/
                                  /_/
*/


template <class T, class U>
Repere<T, U>::Repere(Vector<T> const & d_origin, U d_scale, U d_angle)
: _dest_origin(d_origin),
  _dest_scale(d_scale),
  _dest_angle(d_angle)
{}

template <class T, class U>
Vector<T> Repere<T, U>::operator()(Vector<T> p) const
{
	static const ParametricRepere<T, U> eq;
	return (eq(p, _dest_origin, _dest_scale, _dest_angle));
}

template <class T, class U>
Vector<T> const & Repere<T, U>::dest_origin() const
{
	return (_dest_origin);
}

template <class T, class U>
Vector<T> & Repere<T, U>::dest_origin()
{
	return (_dest_origin);
}

template <class T, class U>
U Repere<T, U>::dest_scale() const
{
	return (_dest_scale);
}

template <class T, class U>
U & Repere<T, U>::dest_scale()
{
	return (_dest_scale);
}

template <class T, class U>
U Repere<T, U>::dest_angle() const
{
	return (_dest_angle);
}

template <class T, class U>
U & Repere<T, U>::dest_angle()
{
	return (_dest_angle);
}

template <class T, class U>
Repere<T, U> Repere<T, U>::reciproc() const
{
	return (Repere<T, U>(-_dest_origin, U(1) / _dest_scale, -_dest_angle));
}
