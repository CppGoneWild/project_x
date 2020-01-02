#include "hubble.hh"



hubble::CelestialBody::CelestialBody(std::string const & name)
: _name(name)
{}

std::string const & hubble::CelestialBody::name() const
{
	return (_name);
}

std::string & hubble::CelestialBody::name()
{
	return (_name);
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

	sol.bodies().emplace_back("soleil");
	sol.bodies().emplace_back("mercury");
	sol.bodies().emplace_back("venus");
	sol.bodies().emplace_back("earth");
	sol.bodies().emplace_back("mars");
	sol.bodies().emplace_back("jupiter");
	sol.bodies().emplace_back("saturne");
	sol.bodies().emplace_back("uranus");
	sol.bodies().emplace_back("neptune");

	return (sol);
}

