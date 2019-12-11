#ifndef COLONY_HH
#define COLONY_HH

#include "Distribution.hh"
#include "UniversalClock.hh"

#include <string>


#include <vector>


class Colony
{
public:
	Colony() {_population_distrib = {1000, 750, 500, 100};}
	Colony(Colony const &) = default;
	Colony(Colony &&)      = default;
	~Colony()              = default;

	Colony & operator=(Colony const &) = default;
	Colony & operator=(Colony &&)      = default;

	std::string const & name() const;
	std::string & name();

	int population() const;
	int & population();

	float population_growth() const;
	float & population_growth();

	int gross_colonial_product() const;
	int & gross_colonial_product();

	float gross_colonial_product_growth() const;
	float & gross_colonial_product_growth();

	void update(UniversalClock::duration last_tick, UniversalClock::time_point date);

	Distribution<float> _population_distrib;// = {1000, 750, 500, 100};
private:
	std::string _name;

	UniversalClock::time_point _next_update;
	UniversalClock::time_point _next_pop_update;

	int _population = 0;
	float _population_growth = 0.0;

	int _gross_colonial_product = 0;
	float _gross_colonial_product_growth = 0.0;
};


#endif // COLONY_HH
