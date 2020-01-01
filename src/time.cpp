#include "time.hh"

#include <algorithm> // stable_sort, is_sorted


/*
        __  __      _                            __________           __
       / / / /___  (_)   _____  ______________ _/ / ____/ /___  _____/ /__
      / / / / __ \/ / | / / _ \/ ___/ ___/ __ `/ / /   / / __ \/ ___/ //_/
     / /_/ / / / / /| |/ /  __/ /  (__  ) /_/ / / /___/ / /_/ / /__/ ,<
     \____/_/ /_/_/ |___/\___/_/  /____/\__,_/_/\____/_/\____/\___/_/|_|

*/



UniversalClock::duration   UniversalClock::_last_tic(0);
UniversalClock::time_point UniversalClock::_now(_last_tic);



UniversalClock::time_point UniversalClock::now() noexcept
{
	return (_now);
}

UniversalClock::duration UniversalClock::last_tic() noexcept
{
	return (_last_tic);
}

UniversalClock::duration UniversalClock::advance(time_point t) noexcept
{
	_last_tic = t - _now;
	_now = t;
	return (_last_tic);
}

UniversalClock::duration UniversalClock::advance(duration d) noexcept
{
	_last_tic = d;
	_now += _last_tic;
	return (_last_tic);
}


std::string UniversalClock::to_string(time_point t)
{
	std::int64_t year  = std::chrono::duration_cast<UniversalClock::years> (t.time_since_epoch()).count();
	std::int64_t month = std::chrono::duration_cast<UniversalClock::months>(t.time_since_epoch() - std::chrono::duration_cast<UniversalClock::duration>(UniversalClock::years(year))).count();
	std::int64_t day   = std::chrono::duration_cast<UniversalClock::days>  (t.time_since_epoch() - std::chrono::duration_cast<UniversalClock::duration>(UniversalClock::years(year)) - std::chrono::duration_cast<UniversalClock::duration>(UniversalClock::months(month))).count();

	year += 2200;

	std::string res;
	if (day < 10)
		res += "0";
	res += std::to_string(day);

	res += ".";

	if (month < 10)
		res += "0";
	res += std::to_string(month);

	res += ".";
	res += std::to_string(year);

	return (res);
}

template <class D>
static D to_integer_duration(D d)
{
	return (D(int(d.count())));
}

std::string UniversalClock::to_string(duration d)
{
	std::string res;

	auto write_duration_order = [&res, &d](auto duration_as_integer, char const * const c_unit)
	{
		if (duration_as_integer.count() >= 1.0) {
			res += std::to_string(int(duration_as_integer.count())) + c_unit;
			d -= std::chrono::duration_cast<UniversalClock::days>(duration_as_integer);
 		}
	};

	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::century>(d)), "c");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::years>(d)), "y");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::months>(d)), "m");

	if (d.count() > 0)
		res += std::to_string(d.count()) + "d";

	return (res);
}


/*
                          ____   _______
                         /  _/  /_  __(_)___ ___  ___  _____
                         / /     / / / / __ `__ \/ _ \/ ___/
                       _/ /     / / / / / / / / /  __/ /
                      /___/____/_/ /_/_/ /_/ /_/\___/_/
                         /_____/
*/



I_Timer::I_Timer()
:  _last_update(UniversalClock::now())
{}

I_Timer::~I_Timer()
{}

UniversalClock::time_point I_Timer::last_update() const
{
	return (_last_update);
}

double I_Timer::progress(UniversalClock::time_point date) const
{
	auto total = next_update() - _last_update;
	auto current = date - _last_update;

	return (double(current.count()) / double(total.count()));
}

UniversalClock::time_point I_Timer::max()
{
	return (UniversalClock::time_point::max());
}



/*
                          _______
                         /_  __(_)___ ___  ___  _____
                          / / / / __ `__ \/ _ \/ ___/
                         / / / / / / / / /  __/ /
                        /_/ /_/_/ /_/ /_/\___/_/
*/



Timer::Timer(UniversalClock::time_point next_update)
: I_Timer(), _frequency(), _next_update(next_update)
{}

Timer::Timer(UniversalClock::duration frequency, UniversalClock::time_point current_time)
: I_Timer(), _frequency(frequency), _next_update(current_time + _frequency)
{
	assert(_frequency != UniversalClock::duration()); // use single shot mode
	_last_update = current_time;
}

UniversalClock::time_point Timer::next_update() const
{
	return (_next_update);
}

UniversalClock::time_point Timer::next_next_update() const
{
	return (_frequency == UniversalClock::duration() ? I_Timer::max() : _next_update + _frequency);
}

UniversalClock::time_point & Timer::next_update()
{
	return (_next_update);
}

UniversalClock::duration Timer::frequency() const
{
	return (_frequency);
}

UniversalClock::duration & Timer::frequency()
{
	return (_frequency);
}

void Timer::update(UniversalClock::time_point date)
{
	assert(_next_update <= date); // ensure we do need to update.
	assert(_frequency == UniversalClock::duration() || _next_update + _frequency > date); // ensure we did not missed a cycle.

	_last_update = _next_update;

	if (_frequency == UniversalClock::duration())
		_next_update = UniversalClock::time_point::max();
	else
		_next_update += _frequency;
}



/*
                    _____      __             __      __
                   / ___/_____/ /_  ___  ____/ /_  __/ /__  _____
                   \__ \/ ___/ __ \/ _ \/ __  / / / / / _ \/ ___/
                  ___/ / /__/ / / /  __/ /_/ / /_/ / /  __/ /
                 /____/\___/_/ /_/\___/\__,_/\__,_/_/\___/_/
*/



/**
 * @brief used to sort the Scheduler list by time in REVERSE_ORDER
 */
struct I_Timer_less
{
	template <class T>
	bool operator()(T a, T b)
	{
		return (a.get().next_update() > b.get().next_update());
	}
};



UniversalClock::time_point Scheduler::next_update() const
{
	assert(is_sorted());

	return (_updatable.empty() ? I_Timer::max() : _updatable.back().get().next_update());
}

UniversalClock::time_point Scheduler::next_next_update() const
{
	assert(is_sorted());

	UniversalClock::time_point res = I_Timer::max();

	for(auto it = _updatable.rbegin(); it != _updatable.rend(); ++it) {
		if (it->get().next_next_update() < res)
			res = it->get().next_next_update();
		else if (it->get().next_update() < res)
			res = it->get().next_update();
	}

	return (res);
}

void Scheduler::update(UniversalClock::time_point date)
{
	assert(is_sorted());
	assert(next_update() <= date);

	for (auto it = _updatable.rbegin();
		      it != _updatable.rend() && it->get().next_update() <= date;
		      it++)
	{
		it->get().update(date);

		_last_update = date;
	}

	sort();
	clean_dead_timer();
}

UniversalClock::time_point Scheduler::can_adv_to(UniversalClock::time_point date) const
{
	assert(is_sorted());

	if (_updatable.empty() || _updatable.back().get().next_update() > date)
		return (UniversalClock::time_point::max());

	// ensure we will not miss a cycle
	auto next_date = _updatable.back().get().next_update();
	for(auto it = _updatable.crbegin();
		     it != _updatable.crend() &&
		     (it->get().next_update() > date &&
		      it->get().next_update() > date);
		     ++it) {
		if (it->get().next_update() < next_date)
			next_date = it->get().next_update();
		if (it->get().next_next_update() < next_date)
			next_date = it->get().next_next_update();
	}

	return (next_date);
}

void Scheduler::advance_until(UniversalClock::time_point date)
{
	auto intermediate = can_adv_to(date);
	for (; intermediate <= date && intermediate != UniversalClock::time_point::max();
		 intermediate = can_adv_to(date)) {
		UniversalClock::advance(intermediate - UniversalClock::now());
		update(intermediate);
	}
	if (intermediate == UniversalClock::time_point::max() && UniversalClock::now() < date)
		UniversalClock::advance(date - UniversalClock::now());	
}

void Scheduler::advance_until(UniversalClock::duration delta)
{
	advance_until(UniversalClock::now() + delta);
}

bool Scheduler::is_sorted() const
{
	return (std::is_sorted(_updatable.cbegin(), _updatable.cend(), I_Timer_less()));
}

void Scheduler::sort()
{
	std::stable_sort(_updatable.begin(), _updatable.end(), I_Timer_less());
}

void Scheduler::clean_dead_timer()
{
	assert(is_sorted());

	auto last = _updatable.begin();
	for (; last != _updatable.end() && last->get().next_update() == I_Timer::max(); last++)
		;

	_updatable.erase(_updatable.begin(), last);
}

void Scheduler::add(I_Timer & t)
{
	_updatable.push_back(t);

	if (_last_update > t.last_update())
		_last_update = t.last_update();

}

void Scheduler::add_and_sort(I_Timer & t)
{
	add(t);
	sort();	
}

bool Scheduler::empty() const
{
	return (_updatable.empty());
}

std::size_t Scheduler::size() const
{
	return (_updatable.size());
}

void Scheduler::clear()
{
	_updatable.clear();
}

void Scheduler::erase(iterator it)
{
	_updatable.erase(it);
}

void Scheduler::erase(const_iterator it)
{
	_updatable.erase(it);
}

void Scheduler::erase(iterator first, iterator last)
{
	_updatable.erase(first, last);
}

void Scheduler::erase(const_iterator first, const_iterator last)
{
	_updatable.erase(first, last);
}

Scheduler::iterator Scheduler::begin()
{
	return (_updatable.begin());
}

Scheduler::iterator Scheduler::end()
{
	return (_updatable.end());
}

Scheduler::const_iterator Scheduler::cbegin() const
{
	return (_updatable.cbegin());
}

Scheduler::const_iterator Scheduler::cend() const
{
	return (_updatable.cend());
}

Scheduler::reverse_iterator Scheduler::rbegin()
{
	return (_updatable.rbegin());
}

Scheduler::reverse_iterator Scheduler::rend()
{
	return (_updatable.rend());
}

Scheduler::const_reverse_iterator Scheduler::crbegin() const
{
	return (_updatable.crbegin());
}

Scheduler::const_reverse_iterator Scheduler::crend() const
{
	return (_updatable.crend());
}

Scheduler::container_t const & Scheduler::container() const
{
	return (_updatable);
}

Scheduler::container_t & Scheduler::container()
{
	return (_updatable);
}
