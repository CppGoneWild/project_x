#include "Colony.hh"


#include <chrono> // std::chrono::duration_cast
#include <numeric> // std::accumulate

std::string const & Colony::name() const
{
	return (_name);
}

std::string & Colony::name()
{
	return (_name);
}

int Colony::population() const
{
	return (_population);
}

int & Colony::population()
{
	return (_population);
}

float Colony::population_growth() const
{
	return (_population_growth);
}

float & Colony::population_growth()
{
	return (_population_growth);
}

int Colony::gross_colonial_product() const
{
	return (_gross_colonial_product);
}

int & Colony::gross_colonial_product()
{
	return (_gross_colonial_product);
}

float Colony::gross_colonial_product_growth() const
{
	return (_gross_colonial_product_growth);
}

float & Colony::gross_colonial_product_growth()
{
	return (_gross_colonial_product_growth);
}

void Colony::update(UniversalClock::duration last_tick, UniversalClock::time_point date)
{
	static constexpr auto population_tick = UniversalClock::years(25);

	if (_next_pop_update == UniversalClock::time_point())
		_next_pop_update = date;
	if (_next_update == UniversalClock::time_point())
		_next_update = date;

	if (_next_pop_update <= date) {
		for (auto it = _population_distrib.rbegin(); it + 1 != _population_distrib.rend(); it++)
			*it = *(it + 1);
		_population_distrib[0] = 0;
		_next_pop_update += std::chrono::duration_cast<UniversalClock::duration>(population_tick);
	}

	if (_next_update <= date) {
		int time_since_last_update_in_days = std::chrono::duration_cast<UniversalClock::days>(date - _next_update).count();

		_population_distrib[0] += _population_distrib[1] * _population_growth * time_since_last_update_in_days;

		_gross_colonial_product *= _gross_colonial_product_growth * time_since_last_update_in_days;
		
		_next_update += std::chrono::duration_cast<UniversalClock::duration>(UniversalClock::days(1));
	}


	_population = std::accumulate(_population_distrib.begin(), _population_distrib.end(), 0);

}

