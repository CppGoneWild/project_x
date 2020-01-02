#ifndef HUBBLE_HH
#define HUBBLE_HH




#include <vector>
#include <string>




namespace hubble
{




class CelestialBody
{
public:
	CelestialBody()                      = default;
	CelestialBody(CelestialBody const &) = default;
	CelestialBody(CelestialBody &&)      = default;
	~CelestialBody()                     = default;

	CelestialBody & operator=(CelestialBody const &) = default;
	CelestialBody & operator=(CelestialBody &&)      = default;

	explicit CelestialBody(std::string const &);

	std::string const & name() const;
	std::string & name();

private:
	std::string _name;
};




class System
{
public:
	using container_t = std::vector<CelestialBody>;

	System()               = default;
	System(System const &) = default;
	System(System &&)      = default;
	~System()              = default;

	System & operator=(System const &) = default;
	System & operator=(System &&)      = default;

	explicit System(std::string const &);

	std::string const & name() const;
	std::string & name();

	container_t const & bodies() const;
	container_t & bodies();

private:
	std::string _name;
	container_t _bodies;
};



System make_sol_system();



} // hubble




#endif // HUBBLE_HH
