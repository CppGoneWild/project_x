#ifndef SI_HH
#define SI_HH



#ifndef   _USE_MATH_DEFINES
#define   _USE_MATH_DEFINES // for M_PI
#endif // _USE_MATH_DEFINES



#include "math.hh"
#include "time.hh"

#include <cstdint>
#include <ratio>
#include <cmath> // sqrt, hypot, fmod, M_PI, cos, acos, ...


namespace si
{



/*
                        _____ ____  _    __      __
                       / ___//  _/ | |  / /___ _/ /_  _____
                       \__ \ / /   | | / / __ `/ / / / / _ \
                      ___/ // /    | |/ / /_/ / / /_/ /  __/
                     /____/___/____|___/\__,_/_/\__,_/\___/
                             /_____/
*/



template <class REP, class TAG, class RATIO = std::ratio<1>>
class SI_Value
{
public:
	using type_t = REP;
	using tag_t  = TAG;
	using ratio_t  = RATIO;

	SI_Value() = default;
	~SI_Value() = default;

	template <class REP_2, class RATIO_2> SI_Value(SI_Value<REP_2, TAG, RATIO_2> const &);
	template <class REP_2, class RATIO_2> SI_Value(SI_Value<REP_2, TAG, RATIO_2> &&);

	template <class REP_2, class RATIO_2> SI_Value<REP, TAG, RATIO> & operator=(SI_Value<REP_2, TAG, RATIO_2> const &);
	template <class REP_2, class RATIO_2> SI_Value<REP, TAG, RATIO> & operator=(SI_Value<REP_2, TAG, RATIO_2> &&);

	explicit SI_Value(REP);

	REP count() const;
	REP & count();

	template <class REP_2, class RATIO_2> bool operator==(SI_Value<REP_2, TAG, RATIO_2> const &) const;
	template <class REP_2, class RATIO_2> bool operator!=(SI_Value<REP_2, TAG, RATIO_2> const &) const;
	template <class REP_2, class RATIO_2> bool operator< (SI_Value<REP_2, TAG, RATIO_2> const &) const;
	template <class REP_2, class RATIO_2> bool operator> (SI_Value<REP_2, TAG, RATIO_2> const &) const;
	template <class REP_2, class RATIO_2> bool operator<=(SI_Value<REP_2, TAG, RATIO_2> const &) const;
	template <class REP_2, class RATIO_2> bool operator>=(SI_Value<REP_2, TAG, RATIO_2> const &) const;

	void operator+=(REP);
	void operator-=(REP);
	void operator*=(REP);
	void operator/=(REP);
	void operator%=(REP);

	template <class REP_2, class RATIO_2> void operator+=(SI_Value<REP_2, TAG, RATIO_2> const &);
	template <class REP_2, class RATIO_2> void operator-=(SI_Value<REP_2, TAG, RATIO_2> const &);
	template <class REP_2, class RATIO_2> void operator*=(SI_Value<REP_2, TAG, RATIO_2> const &);
	template <class REP_2, class RATIO_2> void operator/=(SI_Value<REP_2, TAG, RATIO_2> const &);
	template <class REP_2, class RATIO_2> void operator%=(SI_Value<REP_2, TAG, RATIO_2> const &);

	template <class U> SI_Value<REP, TAG, RATIO> operator+(U const &) const;
	template <class U> SI_Value<REP, TAG, RATIO> operator-(U const &) const;
	template <class U> SI_Value<REP, TAG, RATIO> operator*(U const &) const;
	template <class U> SI_Value<REP, TAG, RATIO> operator/(U const &) const;
	template <class U> SI_Value<REP, TAG, RATIO> operator%(U const &) const;

	template <class REP_2 = REP> SI_Value<REP_2, TAG, std::ratio<1>> si() const;

private:
	REP _value;
};



////////////////////////////////////////////////////////////////////////////////
/////                               si_cast                                /////
////////////////////////////////////////////////////////////////////////////////



template <class TO_SI, class REP, class TAG, class RATIO>
TO_SI si_cast(SI_Value<REP, TAG, RATIO>);



/*
                                          _ __
                             __  ______  (_) /______
                            / / / / __ \/ / __/ ___/
                           / /_/ / / / / / /_(__  )
                           \__,_/_/ /_/_/\__/____/
                           
*/

/*
 * - distance
 * - surface
 * - volume
 * - mass
 * - mass volumique
 * - angle
 * - time
 * - speed
 * - acceleration
 * - angular speed
 * - position
 */


////////////////////////////////////////////////////////////////////////////////
/////                              distance                                /////
////////////////////////////////////////////////////////////////////////////////



struct distance_tag {};
using meters = SI_Value<std::int64_t, distance_tag>;

using kilo_meters = SI_Value<float,        distance_tag, std::kilo>;
using mega_meters = SI_Value<float,        distance_tag, std::mega>;
using giga_meters = SI_Value<float,        distance_tag, std::giga>;

using astronomical_units = SI_Value<float, distance_tag, std::ratio<149567870700>>;

using light_second = SI_Value<float, distance_tag, std::ratio<299792458>>;
using light_minute = SI_Value<float, distance_tag, std::ratio<17987547480>>;
using light_hour   = SI_Value<float, distance_tag, std::ratio<1079252848800>>;
using light_year   = SI_Value<float, distance_tag, std::ratio<9460730472580800>>;

 

////////////////////////////////////////////////////////////////////////////////
/////                              surface                                /////
////////////////////////////////////////////////////////////////////////////////



struct surface_tag {};
using meters2 = SI_Value<std::int64_t, surface_tag>;

using ares     = SI_Value<std::int64_t, surface_tag, std::ratio<10>>;
using hectares = SI_Value<std::int64_t, surface_tag, std::ratio<10000>>;

template <class S, class D1, class D2> meters2 S(D1 lenght, D2 width);



////////////////////////////////////////////////////////////////////////////////
/////                                volume                                /////
////////////////////////////////////////////////////////////////////////////////



struct volume_tag {};
using meters3  = SI_Value<std::int64_t, volume_tag>;

using liter   = SI_Value<std::int64_t, volume_tag, std::ratio<1, 1000>>;
using tonneau = SI_Value<std::int64_t, volume_tag, std::ratio<8849, 3125>>; /// 100 ft3 = 2.83168 m3 = 8849/3125


template <class V, class D1, class D2, class D3> meters3 make_volume(D1, D2, D3);
template <class V, class D, class S> meters3 make_volume(D lenght, S surface);



////////////////////////////////////////////////////////////////////////////////
/////                                  mass                                /////
////////////////////////////////////////////////////////////////////////////////



struct mass_tag {};
using milligramms  = SI_Value<float,        mass_tag, std::ratio<1, 1000000>>;
using gramms       = SI_Value<float,        mass_tag, std::ratio<1, 1000>>;
using kilogramms   = SI_Value<std::int64_t, mass_tag, std::ratio<1>>;
using tonnes       = SI_Value<float,        mass_tag, std::ratio<1000>>;
using kilo_tonnes  = SI_Value<float,        mass_tag, std::ratio<1000000>>;
using mega_tonnes  = SI_Value<float,        mass_tag, std::ratio<1000000000>>;



////////////////////////////////////////////////////////////////////////////////
/////                        mass volumique                                /////
////////////////////////////////////////////////////////////////////////////////



struct mass_volumic_tag {};
using kg_by_meters3 = SI_Value<std::int64_t, mass_volumic_tag, std::ratio<1>>;

template <class M, class V> kg_by_meters3 make_mass_volumic(M, V);



////////////////////////////////////////////////////////////////////////////////
/////                                 angle                                /////
////////////////////////////////////////////////////////////////////////////////



struct radian_tag {};
using radians = SI_Value<float, radian_tag>;
struct degree_tag {};
using degrees = SI_Value<float, degree_tag>;

template <> radians si_cast<radians, float, degree_tag, std::ratio<1>>(degrees s);
template <> degrees si_cast<degrees, float, radian_tag, std::ratio<1>>(radians s);



////////////////////////////////////////////////////////////////////////////////
/////                                  time                                /////
////////////////////////////////////////////////////////////////////////////////



using time_point = UniversalClock::time_point;
using seconds = UniversalClock::seconds;
using hours = UniversalClock::hours;

using days    = UniversalClock::days;
using years   = UniversalClock::years;



////////////////////////////////////////////////////////////////////////////////
/////                                 speed                                /////
////////////////////////////////////////////////////////////////////////////////



struct speed_tag {};
using meters_per_second = SI_Value<std::int64_t, speed_tag>;

using meters_per_hour = SI_Value<float, speed_tag, std::ratio<1, 3600>>;
using meters_per_day  = SI_Value<float, speed_tag, std::ratio<1, 86400>>;

using km_per_second = SI_Value<float, speed_tag, std::kilo>;
using km_per_hour   = SI_Value<float, speed_tag, std::ratio<1000, 3600>>;
using km_per_day    = SI_Value<float, speed_tag, std::ratio<1000, 86400>>;

template <class S, class D, class T>
S make_speed(D d, T t);



////////////////////////////////////////////////////////////////////////////////
/////                          acceleration                                /////
////////////////////////////////////////////////////////////////////////////////



struct acceleration_tag {};
using acceleration = SI_Value<std::int64_t, acceleration_tag>;

template <class D, class T>
acceleration make_acceleration(D d, T t);



////////////////////////////////////////////////////////////////////////////////
/////                         angular speed                                /////
////////////////////////////////////////////////////////////////////////////////



struct rad_speed_tag {};
using rad_per_second = SI_Value<float, rad_speed_tag>;
struct deg_speed_tag {};
using deg_per_second = SI_Value<float, deg_speed_tag>;

template <class T> rad_per_second make_angular_speed(radians angle, T t);
template <class T> deg_per_second make_angular_speed(degrees angle, T t);

template <> rad_per_second si_cast<rad_per_second, float, deg_speed_tag, std::ratio<1>>(deg_per_second);
template <> deg_per_second si_cast<deg_per_second, float, rad_speed_tag, std::ratio<1>>(rad_per_second);



////////////////////////////////////////////////////////////////////////////////
/////                              position                                /////
////////////////////////////////////////////////////////////////////////////////



// carthesian



struct carth_coord_tag {};
using carth_coord = SI_Value<Vector<std::int64_t>, carth_coord_tag, meters::ratio_t>;

using meters_2d      = carth_coord;
using kilo_meters_2d = SI_Value<Vector<double>, carth_coord_tag, kilo_meters::ratio_t>;



// helpers for carthesian composante direct access



template <class D, class R>
D get_x(SI_Value<Vector<D>, carth_coord_tag, R> const &);
template <class D, class R>
D get_y(SI_Value<Vector<D>, carth_coord_tag, R> const &);

template <class D, class R>
D & get_x(SI_Value<Vector<D>, carth_coord_tag, R> &);
template <class D, class R>
D & get_y(SI_Value<Vector<D>, carth_coord_tag, R> &);



// polar



struct polar_coord_tag {};
using polar_coord = SI_Value<Polar<carth_coord::type_t::type_t, float>, polar_coord_tag, meters::ratio_t>;

using meters_polar      = carth_coord;
using kilo_meters_polar = SI_Value<Polar<kilo_meters_2d::type_t::type_t, float>, carth_coord_tag, kilo_meters_2d::ratio_t>;


// helpers for polar composante direct access




template <class D, class A, class R>
D get_radius(SI_Value<Polar<D, A>, polar_coord_tag, R> const &);

template <class D, class A, class R>
A get_theta(SI_Value<Polar<D, A>, polar_coord_tag, R> const &);

template <class D, class A, class R>
D & get_radius(SI_Value<Polar<D, A>, polar_coord_tag, R> &);

template <class D, class A, class R>
A & get_theta(SI_Value<Polar<D, A>, polar_coord_tag, R> &);



// cast from polar/carthesian to polar/carthesian



template <>
carth_coord si_cast<carth_coord, polar_coord::type_t, polar_coord::tag_t, polar_coord::ratio_t>(polar_coord);

template <>
polar_coord si_cast<polar_coord, carth_coord::type_t, carth_coord::tag_t, carth_coord::ratio_t>(carth_coord);



#include "si.ipp"



} // si



#endif // SI_HH
