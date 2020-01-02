#ifndef HUBBLE_HH
#define HUBBLE_HH




#include <vector>
#include <array>
#include <string>
#include <variant>




namespace hubble
{




struct Type
{
	enum class M_Type {
		None = 0,
		Staroid,
		Planetoid,
		Asteroid,
		Comet,
		BlackHole,
		Cloud
	};

	struct Star
	{
		std::array<char, 4> spectral;
		std::array<char, 4> sspectral;
		std::array<char, 4> yerkes;

		Star() = default;
		Star(std::string const & spectral_type, std::string const & sub_spectral, std::string const & yerkes);
	};

	enum class Planet
	{
		None = 0, Ground, Gaz, Ice
	};


	M_Type main;
	std::variant<Planet, Star> second;

	Type();
	Type(M_Type);
	Type(Planet);
	Type(Star);
};



class CelestialBody
{
public:
	CelestialBody()                      = default;
	CelestialBody(CelestialBody const &) = default;
	CelestialBody(CelestialBody &&)      = default;
	~CelestialBody()                     = default;

	CelestialBody & operator=(CelestialBody const &) = default;
	CelestialBody & operator=(CelestialBody &&)      = default;

	CelestialBody(std::string const &, Type);

	std::string const & name() const;
	std::string & name();

	Type const & type() const;
	Type & type();

private:
	std::string _name;
	Type _type;
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

	explicit System(std::string const &, CelestialBody const &);

	std::string const & name() const;
	std::string & name();

	CelestialBody const & main_body() const;
	CelestialBody & main_body();

	container_t const & bodies() const;
	container_t & bodies();

private:
	std::string _name;
	CelestialBody _main_body;
	container_t _bodies;
};


System make_sol_system();


class Galaxy
{
public:
	using container_t = std::vector<System>;

	Galaxy()               = default;
	Galaxy(Galaxy const &) = default;
	Galaxy(Galaxy &&)      = default;
	~Galaxy()              = default;

	Galaxy & operator=(Galaxy const &) = default;
	Galaxy & operator=(Galaxy &&)      = default;

	container_t const & systems() const;
	container_t & systems();

private:
	container_t _systems;
};


Galaxy make_via_lactea();


} // hubble




#endif // HUBBLE_HH
