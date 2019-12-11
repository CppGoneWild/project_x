#include "Updatable.hh"



Updatable::Updatable(time_point next_update)
: _frequency(), _next_update(next_update)
{}

Updatable::Updatable(duration frequency, time_point current_time)
: _next_update(frequency), _next_update(current_time + frequency)
{
	assert(frequency != duration()); // use single shot mode
}

D Updatable::frequency() const
{
	return (_frequency);
}

T Updatable::next_update() const
{
	return (_next_update);
}

D & Updatable::frequency()
{
	return (_frequency);
}

T & Updatable::next_update()
{
	return (_next_update);
}

bool Updatable::is_single_shot() const
{
	return (_frequency == duration());
}

std::pair<T, bool> Updatable::can_adv_to(time_point date) const
{
	return (std::pair<T, bool>(_next_update, _next_update <= date));
};

void Updatable::update(T date)
{
	assert(_next_update <= date);
	assert(is_single_shot() || _next_update + _frequency > date); // ensure we did not miss a cycle.

	next_update = (is_single_shot()) ? (time_point::max()) : (date + _frequency);
}
