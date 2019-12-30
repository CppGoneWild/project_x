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
		Polar<std::int64_t> tmp(0.0, _radius.count());
		return (si::polar_coord(tmp));
	}

	auto elapsed_since_epoch = (now - _epoch).count() % _sidereal_period.count();

	float angle = (float)(elapsed_since_epoch) * M_PI * 2.0;
	angle /= (float)(_sidereal_period.count());

	Polar<std::int64_t> tmp(angle, _radius.count());
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




void kepler::OrbitalBody::_copy_system(OrbitalBody const & src, OrbitalBody & dest)
{
	delete dest._system;
	dest._system = nullptr;	

	if (src._system) {
		dest._system = new System;
		for (auto it = src._system->cbegin(); it == src._system->cend(); it++)
			dest._system->emplace_back(*it)._satellite_of = &dest;
	}
}

void kepler::OrbitalBody::_move_system(OrbitalBody && src, OrbitalBody & dest)
{
	delete dest._system;
	dest._system = nullptr;	

	if (src._system) {
		dest._system = src._system;
		src._system = nullptr;
		for (auto it = dest._system->begin(); it == dest._system->end(); it++)
			it->_satellite_of = &dest;
	}
}




kepler::OrbitalBody::OrbitalBody(OrbitalBody const & oth)
: _radius(oth._radius), _orbit(oth._orbit),
  _satellite_of(oth._satellite_of), _system(nullptr)
{
	_copy_system(oth, *this);
}

kepler::OrbitalBody::OrbitalBody(OrbitalBody && oth)
: _radius(oth._radius), _orbit(oth._orbit),
  _satellite_of(oth._satellite_of), _system(nullptr)
{
	_move_system(std::move(oth), *this);
}

kepler::OrbitalBody::~OrbitalBody()
{
	delete _system;
}

kepler::OrbitalBody & kepler::OrbitalBody::operator=(OrbitalBody const & oth)
{
	if (this != &oth) {
		_radius = oth._radius;
		_orbit = oth._orbit;
		_satellite_of = oth._satellite_of;
		_copy_system(oth, *this);
	}
	return (*this);
}

kepler::OrbitalBody & kepler::OrbitalBody::operator=(OrbitalBody && oth)
{
	if (this != &oth) {
		_radius = oth._radius;
		_orbit = oth._orbit;
		_satellite_of = oth._satellite_of;
		_move_system(std::move(oth), *this);
	}
	return (*this);
}

kepler::OrbitalBody::OrbitalBody(Orbit const & o, si::meters radius)
: _radius(radius), _orbit(o), _satellite_of(nullptr), _system(nullptr)
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

bool kepler::OrbitalBody::has_system() const
{
	return (_system != nullptr);
}

kepler::OrbitalBody::System const & kepler::OrbitalBody::system() const
{
	return (*_system);
}

kepler::OrbitalBody::System & kepler::OrbitalBody::system()
{
	return (*_system);
}

kepler::OrbitalBody & kepler::OrbitalBody::add(OrbitalBody const & body)
{
	if (_system == nullptr)
		_system = new System;

	OrbitalBody & new_body = _system->emplace_back(body);
	new_body._satellite_of = this;
	return (new_body);
}

kepler::OrbitalBody & kepler::OrbitalBody::add(OrbitalBody && body)
{
	if (_system == nullptr)
		_system = new System;

	OrbitalBody & new_body = _system->emplace_back(body);
	new_body._satellite_of = this;
	return (new_body);
}
