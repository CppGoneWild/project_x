/*
                          _____ ____  _    __      __
                         / ___//  _/ | |  / /___ _/ /_  _____
                         \__ \ / /   | | / / __ `/ / / / / _ \
                        ___/ // /    | |/ / /_/ / / /_/ /  __/
                       /____/___/____|___/\__,_/_/\__,_/\___/
                               /_____/
                       
*/



template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
SI_Value<REP, TAG, RATIO>::SI_Value(SI_Value<REP_2, TAG, RATIO_2> const & oth)
: _value(oth.count())
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
SI_Value<REP, TAG, RATIO>::SI_Value(SI_Value<REP_2, TAG, RATIO_2> && oth)
: _value(oth.count())
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
SI_Value<REP, TAG, RATIO> & SI_Value<REP, TAG, RATIO>::operator=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{
	_value = oth.count();
	return (*this);
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
SI_Value<REP, TAG, RATIO> & SI_Value<REP, TAG, RATIO>::operator=(SI_Value<REP_2, TAG, RATIO_2> && oth)
{
	_value = oth.count();
	return (*this);
}

template <class REP, class TAG, class RATIO>
SI_Value<REP, TAG, RATIO>::SI_Value(REP value)
: _value(value)
{}

template <class REP, class TAG, class RATIO>
REP SI_Value<REP, TAG, RATIO>::count() const
{
	return (_value);
}

template <class REP, class TAG, class RATIO>
REP & SI_Value<REP, TAG, RATIO>::count()
{
	return (_value);
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator==(SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{
	return (_value == oth.count());
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator!=(SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{
	return (_value != oth.count());
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator< (SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{
	return (_value <  oth.count());
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator> (SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{
	return (_value >  oth.count());
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator<=(SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{
	return (_value <= oth.count());
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator>=(SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{
	return (_value >= oth.count());
}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator+=(REP value)
{
	_value += value;
}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator-=(REP value)
{
	_value -= value;
}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator*=(REP value)
{
	_value *= value;
}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator/=(REP value)
{
	_value /= value;
}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator%=(REP value)
{
	_value %= value;
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator+=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{
	_value += oth.count();
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator-=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{
	_value -= oth.count();
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator*=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{
	_value *= oth.count();
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator/=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{
	_value /= oth.count();
}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator%=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{
	_value %= oth.count();
}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator+(U const & oth) const
{
	SI_Value<REP, TAG, RATIO> res(*this);
	res += oth;
	return (res);
}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator-(U const & oth) const
{
	SI_Value<REP, TAG, RATIO> res(*this);
	res -= oth;
	return (res);
}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator*(U const & oth) const
{
	SI_Value<REP, TAG, RATIO> res(*this);
	res *= oth;
	return (res);
}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator/(U const & oth) const
{
	SI_Value<REP, TAG, RATIO> res(*this);
	res /= oth;
	return (res);
}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator%(U const & oth) const
{
	SI_Value<REP, TAG, RATIO> res(*this);
	res %= oth;
	return (res);
}

template <class REP, class TAG, class RATIO>
template <class REP_2>
SI_Value<REP_2, TAG, std::ratio<1>> SI_Value<REP, TAG, RATIO>::si() const
{
	return si_cast<SI_Value<REP_2, TAG, std::ratio<1>>>(*this); 
}



////////////////////////////////////////////////////////////////////////////////
/////                               si_cast                                /////
////////////////////////////////////////////////////////////////////////////////



template <class REP, class TAG, class RATIO, class FROM_SI, class RATIO_FACTOR>
SI_Value<REP, TAG, RATIO> ____si_cast(FROM_SI s)
{
	return (SI_Value<REP, TAG, RATIO>(REP(s.count() * (RATIO_FACTOR::num / RATIO_FACTOR::den))));
}


template <class TO_SI, class REP, class TAG, class RATIO>
TO_SI si_cast(SI_Value<REP, TAG, RATIO> s)
{
	return (____si_cast<TO_SI::type_t, TAG, TO_SI::ratio_t, // ensure same TAG for src and dest
		                  SI_Value<REP, TAG, RATIO>,
		                  std::ratio_divide<RATIO, TO_SI::ratio_t>>(s));
}



/*
                             __  __      _ __
                            / / / /___  (_) /______
                           / / / / __ \/ / __/ ___/
                          / /_/ / / / / / /_(__  )
                          \____/_/ /_/_/\__/____/

*/



/*
 * - surface
 * - volume
 * - mass volumique
 * - angle
 * - speed
 * - acceleration
 * - angular speed
 * - position
 */



////////////////////////////////////////////////////////////////////////////////
/////                              surface                                /////
////////////////////////////////////////////////////////////////////////////////



template <class S, class D1, class D2>
S make_surface(D1 lenght, D2 width)
{
	auto l_as_m = si_cast<meters>(lenght).count();
	auto w_as_m = si_cast<meters>(width).count();
	meters2 m2(l_as_m * w_as_m);

	return (si_cast<S>(m2));
}



////////////////////////////////////////////////////////////////////////////////
/////                                volume                                /////
////////////////////////////////////////////////////////////////////////////////



template <class V, class D1, class D2, class D3>
V make_volume(D1 lenght, D2 width, D3 toto)
{
	auto l_as_m = si_cast<meters>(lenght).count();
	auto w_as_m = si_cast<meters>(width).count();
	auto t_as_m = si_cast<meters>(toto).count();
	meters3 m3(l_as_m * w_as_m * t_as_m);

	return (si_cast<V>(m3));
}

template <class V, class D, class S>
V make_volume(D lenght, S surface)
{
	auto l_as_m = si_cast<meters>(lenght).count();
	auto s_as_sm = si_cast<squaremeters>(surface).count();
	meters3 m3(l_as_m * s_as_sm);

	return (si_cast<V>(m3));
}



////////////////////////////////////////////////////////////////////////////////
/////                        mass volumique                                /////
////////////////////////////////////////////////////////////////////////////////



template <class M, class V>
kg_by_meters3 make_mass_volumic(M mass, V vol)
{
	auto m_as_k = si_cast<kilogramms>(mass).count();
	auto v_as_cm = si_cast<cubemeters>(vol).count();

	return (kg_by_meters3(m_as_k * v_as_cm));
}



////////////////////////////////////////////////////////////////////////////////
/////                                 angle                                /////
////////////////////////////////////////////////////////////////////////////////



template <>
radians si_cast<radians, float, degree_tag, std::ratio<1>>(degrees s)
{
	return (radians(s.count() * M_PI / 180.0));
}

template <>
degrees si_cast<degrees, float, radian_tag, std::ratio<1>>(radians s)
{
	return (degrees(s.count() * 180.0 / M_PI));
}



////////////////////////////////////////////////////////////////////////////////
/////                                 speed                                /////
////////////////////////////////////////////////////////////////////////////////



template <class S, class D, class T>
S make_speed(D d, T t)
{
	auto as_meters  = si_cast<meters>(d).count() * S::ratio_t::num;
	auto as_seconds = std::chrono::duration_cast<seconds>(t).count() * S::ratio_t::den;
	return (S(as_meters / as_seconds));
}




////////////////////////////////////////////////////////////////////////////////
/////                          acceleration                                /////
////////////////////////////////////////////////////////////////////////////////



template <class D, class T>
acceleration make_acceleration(D d, T t)
{
	auto as_meters  = si_cast<meters>(d).count();
	auto as_seconds = std::chrono::duration_cast<seconds>(t).count();
	return (acceleration(as_meters / as_seconds));
}



////////////////////////////////////////////////////////////////////////////////
/////                         angular speed                                /////
////////////////////////////////////////////////////////////////////////////////



template <class T>
rad_per_second make_angular_speed(radian_t angle, T t)
{
	auto as_seconds = std::chrono::duration_cast<seconds>(t).count();
	return (rad_per_second(angle / as_seconds));
}

template <class T>
deg_per_second make_angular_speed(degrees angle, T t)
{
	auto as_seconds = std::chrono::duration_cast<seconds>(t).count();
	return (rad_per_second(angle / as_seconds));
}

template <>
rad_per_second si_cast<rad_per_second, float, deg_speed_tag, std::ratio<1>>(deg_per_second s)
{
	return (rad_per_second(s.count() * M_PI / 180.0));
}

template <>
deg_per_second si_cast<deg_per_second, float, rad_speed_tag, std::ratio<1>>(rad_per_second s)
{
	return (deg_per_second(s.count() * 180.0 / M_PI));
}



////////////////////////////////////////////////////////////////////////////////
/////                              position                                /////
////////////////////////////////////////////////////////////////////////////////



// helpers for carthesian composante direct access



template <class D>
D::type_t get_x(SI_Value<Vector<D>, carth_coord_tag, D::ratio_t> const & v)
{
	return (v.count().x().count());
}

template <class D>
D::type_t get_y(SI_Value<Vector<D>, carth_coord_tag, D::ratio_t> const & v)
{
	return (v.count().y().count());
}

template <class D>
D::type_t & get_x(SI_Value<Vector<D>, carth_coord_tag, D::ratio_t> & v)
{
	return (v.count().x().count());
}

template <class D>
D::type_t & get_y(SI_Value<Vector<D>, carth_coord_tag, D::ratio_t> & v)
{
	return (v.count().y().count());
}



// helpers for polar composante direct access



template <class D, class A, class R>
D::type_t get_radius(SI_Value<Polar<D, radians>, polar_coord_tag, R> const & p)
{
	return (p.count().radius.count());
}

template <class D, class A, class R>
A::type_t get_theta(SI_Value<Polar<D, radians>, polar_coord_tag, R> const & p)
{
	return (p.count().theta.count());
}

template <class D, class A, class R>
D::type_t & get_radius(SI_Value<Polar<D, radians>, polar_coord_tag, R> & p)
{
	return (p.count().radius.count());
}

template <class D, class A, class R>
A::type_t & get_theta(SI_Value<Polar<D, radians>, polar_coord_tag, R> & p)
{
	return (p.count().theta.count());
}



// cast from polar/carthesian to polar/carthesian



template <>
carth_coord si_cast<carth_coord, polar_coord::type_t, polar_coord::tag_t, polar_coord::ratio_t>(polar_coord s)
{
	carth_coord res;

	if (get_radius(s) != meters(0)) {
		get_x(res) = get_radius(s) * std::cos(get_theta(s));
		get_y(res) = get_radius(s) * std::sin(get_theta(s));
	}

	return (res);
}

template <>
polar_coord si_cast<polar_coord, carth_coord::type_t, carth_coord::tag_t, carth_coord::ratio_t>(carth_coord s)
{
	polar_coord res;
	get_radius(res) = std::hypot(get_x(s), get_y(s));

	if (get_radius(res) == 0)
		get_theta(res) = 0;
	else if (get_y(s) < 0)
		get_theta(res) = -(std::acos(get_x(s), get_radius(res)));
	else
		get_theta(res) = std::acos(get_x(s), get_radius(res));

	return (res);
}
