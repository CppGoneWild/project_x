#include "hubble.hh"


#include <cassert>
#include <cstring>



hubble::Type::Star::Star(std::string const & spectral_type,
                         std::string const & sub_spectral,
                         std::string const & y)
: Star()
{
	assert(spectral_type.size() < spectral.size());
	assert(sub_spectral.size() < sspectral.size());
	assert(y.size() < spectral.size());

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




hubble::System::System(std::string const & name, CelestialBody const & main)
: _name(name), _main_body(main), _bodies()
{}

std::string const & hubble::System::name() const
{
	return (_name);
}

std::string & hubble::System::name()
{
	return (_name);
}

hubble::CelestialBody const & hubble::System::main_body() const
{
	return (_main_body);
}

hubble::CelestialBody & hubble::System::main_body()
{
	return (_main_body);
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
	System sol("sol", CelestialBody("sun", Type::Star("G", "2", "V")));

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




hubble::Galaxy::container_t const & hubble::Galaxy::systems() const
{
	return (_systems);
}

hubble::Galaxy::container_t & hubble::Galaxy::systems()
{
	return (_systems);
}



hubble::Galaxy hubble::make_via_lactea()
{
	Galaxy gal;

	gal.systems().emplace_back(make_sol_system());

	System sirius("sirius", CelestialBody("sirius A", Type::Star("A", "0m1", "Va")));
	sirius.bodies().emplace_back("sirius B", Type::Star("DA", "2", "*"));
	sirius.bodies().emplace_back("sirius I",   Type::Planet::Ground);
	sirius.bodies().emplace_back("sirius II",  Type::Planet::Ground);
	sirius.bodies().emplace_back("sirius III", Type::Planet::Gaz);

	System proxima("proxima centauri", CelestialBody("alpha centauri", Type::Star("M", "5.5", "Ve")));
	proxima.bodies().emplace_back("alpha centauri Cb",   Type::Planet::Ground);
	proxima.bodies().emplace_back("alpha centauri Cd",   Type::Planet::Gaz);

	gal.systems().emplace_back(sirius);
	gal.systems().emplace_back(proxima);

	return (gal);
}
