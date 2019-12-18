#include "kepler.hh"



/*
                             ____       __    _ __
                            / __ \_____/ /_  (_) /_
                           / / / / ___/ __ \/ / __/
                          / /_/ / /  / /_/ / / /_
                          \____/_/  /_.___/_/\__/
                          
*/



kepler::Orbit::Orbit(si::meters radius, si::seconds sidereal_period, si::time_point epoch)
: _radius(radius), _sidereal_period(sidereal_period), _epoch(epoch)
{}

si::polar_coord kepler::Orbit::orbital_position(si::time_point now) const
{
	if (_radius.count() == 0)
		return (si::polar_coord());
	if (_sidereal_period.count() == 0) {
		Polar<si::meters, si::radians> tmp(si::radians(), _radius);
		return (si::polar_coord(tmp));
	}

	auto elapsed_since_epoch = (now - _epoch).count() % _sidereal_period.count();

	float angle = (float)(elapsed_since_epoch) * M_PI * 2.0;
	angle /= (float)(_sidereal_period.count());

	Polar<si::meters, si::radians> tmp(si::radians(angle), _radius);
	// tmp.reduce();
	return (si::polar_coord(tmp));
}

si::carth_coord kepler::Orbit::stellar_position(si::time_point now) const
{
	return (si::si_cast<si::carth_coord>(orbital_position(now)));
}

si::meters kepler::Orbit::radius() const
{
	return (_radius);
}

si::meters & kepler::Orbit::radius()
{
	return (_radius);
}

si::seconds kepler::Orbit::sidereal_period() const
{
	return (_sidereal_period);
}

si::seconds & kepler::Orbit::sidereal_period()
{
	return (_sidereal_period);
}

si::time_point kepler::Orbit::epoch() const
{
	return (_epoch);
}

si::time_point & kepler::Orbit::epoch()
{
	return (_epoch);
}



/*
               ____       __    _ __        ______            __
              / __ \_____/ /_  (_) /_____ _/ / __ )____  ____/ /_  __
             / / / / ___/ __ \/ / __/ __ `/ / __  / __ \/ __  / / / /
            / /_/ / /  / /_/ / / /_/ /_/ / / /_/ / /_/ / /_/ / /_/ /
            \____/_/  /_.___/_/\__/\__,_/_/_____/\____/\__,_/\__, /
                                                            /____/
*/



kepler::OrbitalBody::OrbitalBody(Orbit const & o, si::meters radius)
: _radius(radius), _orbit(o), _satellite_of(nullptr)
{}

kepler::OrbitalBody::OrbitalBody(Orbit const & o, OrbitalBody & around, si::meters radius)
: _radius(radius), _orbit(o), _satellite_of(&around)
{}

si::carth_coord kepler::OrbitalBody::stellar_position(si::time_point now) const
{
	si::carth_coord res(_orbit.stellar_position(now));

	if (is_satellite())
		res += _satellite_of->stellar_position(now);

	return (res);	
}

si::meters kepler::OrbitalBody::radius() const
{
	return (_radius);
}

si::meters & kepler::OrbitalBody::radius()
{
	return (_radius);
}

kepler::Orbit const & kepler::OrbitalBody::orbit() const
{
	return (_orbit);
}

kepler::Orbit & kepler::OrbitalBody::orbit()
{
	return (_orbit);
}

bool kepler::OrbitalBody::is_satellite() const
{
	return (_satellite_of != nullptr);
}

kepler::OrbitalBody const & kepler::OrbitalBody::satellite_of() const
{
	return (*_satellite_of);
}

kepler::OrbitalBody & kepler::OrbitalBody::satellite_of()
{
	return (*_satellite_of);
}

