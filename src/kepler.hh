#ifndef KEPLER_HH
#define KEPLER_HH



#ifndef   _USE_MATH_DEFINES
#define   _USE_MATH_DEFINES // for M_PI
#endif // _USE_MATH_DEFINES



#include "si.hh"

#include <vector>
#include <cmath> // sqrt, hypot, fmod, M_PI, cos, acos, ...



namespace kepler
{




/*
                              ____       __    _ __
                             / __ \_____/ /_  (_) /_
                            / / / / ___/ __ \/ / __/
                           / /_/ / /  / /_/ / / /_
                           \____/_/  /_.___/_/\__/
                           
*/



class Orbit
{
public:
	Orbit()              = default;
	Orbit(Orbit const &) = default;
	Orbit(Orbit &&)      = default;
	~Orbit()             = default;

	Orbit & operator=(Orbit const &) = default;
	Orbit & operator=(Orbit &&)      = default;

	Orbit(si::meters radius, si::seconds sidereal_period, si::time_point epoch = si::time_point());
	template <class D, class T> Orbit(D, T, si::time_point = si::time_point());

	si::polar_coord orbital_position(si::time_point) const;
	si::carth_coord stellar_position(si::time_point) const;

	si::meters radius() const;
	si::meters & radius();

	si::seconds sidereal_period() const;
	si::seconds & sidereal_period();

	si::time_point epoch() const;
	si::time_point & epoch();

private:
	si::meters _radius;
	si::seconds _sidereal_period;
	si::time_point _epoch;
};



template <class D, class T>
Orbit::Orbit(D radius, T revolution, si::time_point epoch)
: Orbit(si::si_cast<si::meters>(radius),
	      std::chrono::duration_cast<si::seconds>(revolution),
	      epoch)
{}



/*
               ____       __    _ __        ______            __
              / __ \_____/ /_  (_) /_____ _/ / __ )____  ____/ /_  __
             / / / / ___/ __ \/ / __/ __ `/ / __  / __ \/ __  / / / /
            / /_/ / /  / /_/ / / /_/ /_/ / / /_/ / /_/ / /_/ / /_/ /
            \____/_/  /_.___/_/\__/\__,_/_/_____/\____/\__,_/\__, /
                                                            /____/
            
*/



class OrbitalBody
{
public:
	using System = std::list<OrbitalBody>;

	OrbitalBody() = default;

	OrbitalBody(OrbitalBody const &);
	OrbitalBody(OrbitalBody &&);
	~OrbitalBody();

	OrbitalBody & operator=(OrbitalBody const &);
	OrbitalBody & operator=(OrbitalBody &&);

	OrbitalBody(Orbit const &, si::meters radius);
	template <class D> OrbitalBody(Orbit const &, D radius);

	/**
	 * @brief relative to star.
	 * @details compute position relative to the center of the system.
	 *          for 'local' postion, see member orbit.
	 */
	si::carth_coord stellar_position(si::time_point) const;

	si::meters radius() const;
	si::meters & radius();

	Orbit const & orbit() const;
	Orbit & orbit();

	bool is_satellite() const;
	OrbitalBody const & satellite_of() const;
	OrbitalBody & satellite_of();

	bool has_system() const;
	System const & system() const;
	System & system();
	OrbitalBody & add(OrbitalBody const &);
	OrbitalBody & add(OrbitalBody &&);

private:
	si::meters _radius;
	Orbit _orbit;

	OrbitalBody * _satellite_of = nullptr;
	System * _system = nullptr;

	static void _copy_system(OrbitalBody const & src, OrbitalBody & dest);
	static void _move_system(OrbitalBody && src, OrbitalBody & dest);
};



template <class D> OrbitalBody::OrbitalBody(Orbit const & o, D radius)
: OrbitalBody(o, si::si_cast<si::meters>(radius))
{}



	
} // kepler



#endif // KEPLER_HH
