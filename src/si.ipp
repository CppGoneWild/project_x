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
	return (____si_cast<typename TO_SI::type_t, TAG, typename TO_SI::ratio_t, // ensure same TAG for src and dest
		                  SI_Value<REP, TAG, RATIO>,
		                  std::ratio_divide<RATIO, typename TO_SI::ratio_t>>(s));
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
	auto s_as_sm = si_cast<meters3>(surface).count();
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
	auto v_as_cm = si_cast<meters3>(vol).count();

	return (kg_by_meters3(m_as_k * v_as_cm));
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
rad_per_second make_angular_speed(radians angle, T t)
{
	auto as_seconds = std::chrono::duration_cast<seconds>(t).count();
	return (rad_per_second(angle.count() / as_seconds));
}

template <class T>
deg_per_second make_angular_speed(degrees angle, T t)
{
	auto as_seconds = std::chrono::duration_cast<seconds>(t).count();
	return (deg_per_second(angle.count() / as_seconds));
}



////////////////////////////////////////////////////////////////////////////////
/////                              position                                /////
////////////////////////////////////////////////////////////////////////////////



// helpers for carthesian composante direct access



template <class D>
typename D::type_t get_x(SI_Value<Vector<D>, carth_coord_tag, typename D::ratio_t> const & v)
{
	return (v.count().x.count());
}

template <class D>
typename D::type_t get_y(SI_Value<Vector<D>, carth_coord_tag, typename D::ratio_t> const & v)
{
	return (v.count().y.count());
}

template <class D>
typename D::type_t & get_x(SI_Value<Vector<D>, carth_coord_tag, typename D::ratio_t> & v)
{
	return (v.count().x.count());
}

template <class D>
typename D::type_t & get_y(SI_Value<Vector<D>, carth_coord_tag, typename D::ratio_t> & v)
{
	return (v.count().y.count());
}



// helpers for polar composante direct access



template <class D, class A, class R>
typename D::type_t get_radius(SI_Value<Polar<D, A>, polar_coord_tag, R> const & p)
{
	return (p.count().radius.count());
}

template <class D, class A, class R>
typename A::type_t get_theta(SI_Value<Polar<D, A>, polar_coord_tag, R> const & p)
{
	return (p.count().theta.count());
}

template <class D, class A, class R>
typename D::type_t & get_radius(SI_Value<Polar<D, A>, polar_coord_tag, R> & p)
{
	return (p.count().radius.count());
}

template <class D, class A, class R>
typename A::type_t & get_theta(SI_Value<Polar<D, A>, polar_coord_tag, R> & p)
{
	return (p.count().theta.count());
}
