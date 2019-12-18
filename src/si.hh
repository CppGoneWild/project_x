#ifndef SI_HH
#define SI_HH



#include "math.hh"
#include "time.hh"

#include <cstdint>
#include <ratio>



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
	REP _value = REP(0);
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
using meters      = SI_Value<std::int64_t, distance_tag, std::ratio<1>>;

using kilo_meters = SI_Value<float,        distance_tag, std::kilo>;
using mega_meters = SI_Value<float,        distance_tag, std::mega>;
using giga_meters = SI_Value<float,        distance_tag, std::giga>;

using astronomical_units = SI_Value<float, distance_tag, std::ratio<149567870700>>;
using light_years        = SI_Value<float, distance_tag, std::ratio<9.4607e15>>;



////////////////////////////////////////////////////////////////////////////////
/////                              surface                                /////
////////////////////////////////////////////////////////////////////////////////



struct surface_tag {};
using square_meters  = SI_Value<std::int64_t, surface_tag>;

template <class D1, class D2>
square_meters make_surface(D1 lenght, D2 width);



////////////////////////////////////////////////////////////////////////////////
/////                                volume                                /////
////////////////////////////////////////////////////////////////////////////////



struct volume_tag {};
using cubic_meters  = SI_Value<std::int64_t, volume_tag>;

template <class D1, class D2, class D3>
cubic_meters make_volume(D1 lenght, D2 width, D3 toto);

template <class D, class S>
cubic_meters make_volume(D lenght, S surface);



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
using kilogramm_by_cubicmeters = SI_Value<std::int64_t, mass_volumic_tag, std::ratio<1>>;

template <class M, class V>
kilogramm_by_cubicmeters make_mass_volumic(M mass, V vol);



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
using duration   = UniversalClock::duration;

using seconds    = UniversalClock::seconds;
using days       = UniversalClock::days;
using years      = UniversalClock::years;



////////////////////////////////////////////////////////////////////////////////
/////                                 speed                                /////
////////////////////////////////////////////////////////////////////////////////



struct speed_tag {};
using speed_t               = SI_Value<std::int64_t, speed_tag>;
using meters_per_second     = SI_Value<std::int64_t, speed_tag>;

using meters_per_hours      = SI_Value<float, speed_tag, std::ratio<1, 3600>>;
using meters_per_days       = SI_Value<float, speed_tag, std::ratio<1, 86400>>;

using kilometers_per_second = SI_Value<float, speed_tag, std::kilo>;
using kilometers_per_hours  = SI_Value<float, speed_tag, std::ratio<1000, 3600>>;
using kilometers_per_days   = SI_Value<float, speed_tag, std::ratio<1000, 86400>>;

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



struct angular_speed_tag {};
using radians_per_second = SI_Value<float, angular_speed_tag>;
struct angular_speed_tag2 {};
using degrees_per_second = SI_Value<float, angular_speed_tag2>;

template <class T> radians_per_second make_angular_speed(radians angle, T t);
template <class T> degrees_per_second make_angular_speed(degrees angle, T t);

template <> radians_per_second si_cast<radians_per_second, float, angular_speed_tag2, std::ratio<1>>(degrees_per_second s) { return (radians_per_second(s.count() * M_PI / 180.0)); }
template <> degrees_per_second si_cast<degrees_per_second, float, angular_speed_tag,  std::ratio<1>>(radians_per_second s) { return (degrees_per_second(s.count() * 180.0 / M_PI)); }



////////////////////////////////////////////////////////////////////////////////
/////                              position                                /////
////////////////////////////////////////////////////////////////////////////////



struct carth_coord_tag {};
using carth_coord = SI_Value<Vector<meters>, carth_coord_tag>;

struct polar_coord_tag {};
using polar_coord = SI_Value<Polar<meters, radians>, polar_coord_tag>;

template <>
carth_coord si_cast<carth_coord, Polar<meters, radians>, polar_coord_tag, std::ratio<1>>(polar_coord s);

template <>
polar_coord si_cast<polar_coord, Vector<meters>, carth_coord_tag, std::ratio<1>>(carth_coord s);



#include "si.ipp"



} // si



#endif // SI_HH
