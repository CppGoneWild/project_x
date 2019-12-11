template <class T, class D>
Updatable<T, D>::Updatable(time_point next_update)
: _frequency(), _next_update(next_update)
{}

template <class T, class D>
Updatable<T, D>::Updatable(duration frequency, time_point current_time)
: _next_update(frequency), _next_update(current_time + frequency)
{
	assert(frequency != D()); // use single shot mode
}

template <class T, class D>
D Updatable<T, D>::frequency() const
{
	return (_frequency);
}

template <class T, class D>
T Updatable<T, D>::next_update() const
{
	return (_next_update);
}

template <class T, class D>
D & Updatable<T, D>::frequency()
{
	return (_frequency);
}

template <class T, class D>
T & Updatable<T, D>::next_update()
{
	return (_next_update);
}

template <class T, class D>
bool Updatable<T, D>::is_single_shot() const
{
	return (_frequency == duration());
}

template <class T, class D>
std::pair<T, bool> Updatable<T, D>::can_adv_to(time_point date) const
{
	return (std::pair<T, bool>(_next_update, _next_update <= date));
};

template <class T, class D>
void Updatable<T, D>::update(T date)
{
	assert(_next_update <= date);
	assert(is_single_shot() || _next_update + _frequency > date); // ensure we did not miss a cycle.

	next_update = (is_single_shot()) ? (time_point::max()) : (date + _frequency);
}
