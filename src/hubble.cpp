#include "hubble.hh"


#include <cassert>
#include <cstring>



hubble::Type::Star::Star(std::string const & spectral_type,
                         std::string const & sub_spectral,
                         std::string const & y)
: Star()
{
	assert(spectral_type.size() < sizeof(spectral));
	assert(sub_spectral.size() < sizeof(sspectral));
	assert(y.size() < sizeof(spectral));

	std::memcpy(spectral.data(), spectral_type.c_str(), spectral_type.size());
	std::memcpy(sspectral.data(), sub_spectral.c_str(), sub_spectral.size());
	std::memcpy(yerkes.data(), y.c_str(), y.size());
}




hubble::Type::Type()
{
	main = M_Type::None;
}

hubble::Type::Type(M_Type type)
{
	main = type;
	second = Planet::None;
}

hubble::Type::Type(Planet type)
{
	main = M_Type::Planetoid;
	second = type;
}

hubble::Type::Type(Star type)
{
	main = M_Type::Staroid;
	second = type;
}


hubble::CelestialBody::CelestialBody(std::string const & name, Type type)
: _name(name), _type(type)
{}

std::string const & hubble::CelestialBody::name() const
{
	return (_name);
}

std::string & hubble::CelestialBody::name()
{
	return (_name);
}

hubble::Type const & hubble::CelestialBody::type() const
{
	return (_type);
}

hubble::Type & hubble::CelestialBody::type()
{
	return (_type);
}




hubble::System::System(std::string const & name)
: _name(name), _bodies()
{}

std::string const & hubble::System::name() const
{
	return (_name);
}

std::string & hubble::System::name()
{
	return (_name);
}

hubble::System::container_t const & hubble::System::bodies() const
{
	return (_bodies);
}

hubble::System::container_t & hubble::System::bodies()
{
	return (_bodies);
}


hubble::System hubble::make_sol_system()
{
	System sol("sol");

	sol.bodies().emplace_back("sun",     Type::Star("G", "2", "V"));
	sol.bodies().emplace_back("mercury", Type::Planet::Ground);
	sol.bodies().emplace_back("venus",   Type::Planet::Ground);
	sol.bodies().emplace_back("earth",   Type::Planet::Ground);
	sol.bodies().emplace_back("mars",    Type::Planet::Ground);
	sol.bodies().emplace_back("jupiter", Type::Planet::Gaz);
	sol.bodies().emplace_back("saturne", Type::Planet::Gaz);
	sol.bodies().emplace_back("uranus",  Type::Planet::Gaz);
	sol.bodies().emplace_back("neptune", Type::Planet::Gaz);

	return (sol);
}

