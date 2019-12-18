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
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
SI_Value<REP, TAG, RATIO>::SI_Value(SI_Value<REP_2, TAG, RATIO_2> && oth)
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
SI_Value<REP, TAG, RATIO> & SI_Value<REP, TAG, RATIO>::operator=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
SI_Value<REP, TAG, RATIO> & SI_Value<REP, TAG, RATIO>::operator=(SI_Value<REP_2, TAG, RATIO_2> && oth)
{}

template <class REP, class TAG, class RATIO>
SI_Value<REP, TAG, RATIO>::SI_Value(REP value)
{}

template <class REP, class TAG, class RATIO>
REP SI_Value<REP, TAG, RATIO>::count() const
{}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::count(REP value)
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator==(SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator!=(SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator< (SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator> (SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator<=(SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
bool SI_Value<REP, TAG, RATIO>::operator>=(SI_Value<REP_2, TAG, RATIO_2> const & oth) const
{}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator+=(REP value)
{}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator-=(REP value)
{}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator*=(REP value)
{}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator/=(REP value)
{}

template <class REP, class TAG, class RATIO>
void SI_Value<REP, TAG, RATIO>::operator%=(REP value)
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator+=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator-=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator*=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator/=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{}

template <class REP, class TAG, class RATIO>
template <class REP_2, class RATIO_2>
void SI_Value<REP, TAG, RATIO>::operator%=(SI_Value<REP_2, TAG, RATIO_2> const & oth)
{}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator+(U const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator-(U const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator*(U const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator/(U const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class U>
SI_Value<REP, TAG, RATIO> SI_Value<REP, TAG, RATIO>::operator%(U const & oth) const
{}

template <class REP, class TAG, class RATIO>
template <class REP_2>
SI_Value<REP_2, TAG, std::ratio<1>> SI_Value<REP, TAG, RATIO>::si() const
{}



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



template <class D1, class D2>
square_meters make_surface(D1 lenght, D2 width)
{
	auto l_as_m = si_cast<meters>(lenght).count();
	auto w_as_m = si_cast<meters>(width).count();

	return (square_meters(l_as_m * w_as_m));
}



////////////////////////////////////////////////////////////////////////////////
/////                                volume                                /////
////////////////////////////////////////////////////////////////////////////////



template <class D1, class D2, class D3>
cubic_meters make_volume(D1 lenght, D2 width, D3 toto)
{
	auto l_as_m = si_cast<meters>(lenght).count();
	auto w_as_m = si_cast<meters>(width).count();
	auto t_as_m = si_cast<meters>(toto).count();

	return (cubic_meters(l_as_m * w_as_m * t_as_m));
}

template <class D, class S>
cubic_meters make_volume(D lenght, S surface)
{
	auto l_as_m = si_cast<meters>(lenght).count();
	auto s_as_sm = si_cast<squaremeters>(surface).count();

	return (cubic_meters(l_as_m * s_as_sm));
}



////////////////////////////////////////////////////////////////////////////////
/////                        mass volumique                                /////
////////////////////////////////////////////////////////////////////////////////



template <class M, class V>
kilogramm_by_cubicmeters make_mass_volumic(M mass, V vol)
{
	auto m_as_k = si_cast<kilogramms>(mass).count();
	auto v_as_cm = si_cast<cubemeters>(vol).count();

	return (kilogramm_by_cubicmeters(m_as_k * v_as_cm));
}



////////////////////////////////////////////////////////////////////////////////
/////                                 angle                                /////
////////////////////////////////////////////////////////////////////////////////



template <> radians si_cast<radians, float, degree_tag, std::ratio<1>>(degrees s) { return (radians(s.count() * M_PI / 180.0)); }
template <> degrees si_cast<degrees, float, radian_tag, std::ratio<1>>(radians s) { return (degrees(s.count() * 180.0 / M_PI)); }



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
radians_per_second make_angular_speed(radian_t angle, T t)
{
	auto as_seconds = std::chrono::duration_cast<seconds>(t).count();
	return (radians_per_second(angle / as_seconds));
}

template <class T>
degrees_per_second make_angular_speed(degrees angle, T t)
{
	auto as_seconds = std::chrono::duration_cast<seconds>(t).count();
	return (radians_per_second(angle / as_seconds));
}



////////////////////////////////////////////////////////////////////////////////
/////                              position                                /////
////////////////////////////////////////////////////////////////////////////////



template <>
carth_coord si_cast<carth_coord, Polar<meters, radians>, polar_coord_tag, std::ratio<1>>(polar_coord s)
{
	carth_coord res;

	if (s.count().radius != meters(0)) {
		res.count().x = s.count().radius * std::cos(s.count().theta);
		res.count().y = s.count().radius * std::sin(s.count().theta);
	}

	return (res);
}

template <>
polar_coord si_cast<polar_coord, Vector<meters>, carth_coord_tag, std::ratio<1>>(carth_coord s)
{
	polar_coord res;
	res.count().radius = std::hypot(s.count().x, s.count().y);

	if (res.count().radius == 0)
		res.count().theta = 0;
	else if (s.count().y < 0)
		res.count().theta = -(std::acos(s.count().x, res.count().radius));
	else
		res.count().theta = std::acos(s.count().x, res.count().radius);

	return (res);
}
