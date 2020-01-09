#include "time.hh"

#include <algorithm> // stable_sort, is_sorted

#include "logg.hh"




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

template <class D>
static std::int64_t _get_only(UniversalClock::time_point & t)
{
	std::int64_t res  = std::chrono::duration_cast<D>(t.time_since_epoch()).count();
	t -= std::chrono::duration_cast<UniversalClock::duration>(D(res));
	return (res);
}

std::string UniversalClock::to_string(time_point t)
{
	std::int64_t year, month, day, hours, minutes, seconds;
	auto decompose_time = [](time_point t, auto & Y, auto & M, auto & D,
	                                       auto & h, auto & m, auto & s)
	{
		t += std::chrono::duration_cast<duration>(days(1)) + std::chrono::duration_cast<duration>(months(1)); // date do start at day 1 month 1.

		Y = _get_only<UniversalClock::years>(t) + 2200;
		M = _get_only<UniversalClock::months>(t);
		D = _get_only<UniversalClock::days>(t);

		h = _get_only<UniversalClock::hours>(t);
		m = _get_only<UniversalClock::minutes>(t);
		s = _get_only<UniversalClock::seconds>(t);
	};

	std::string res;
	auto display_with_2_digit = [&res](auto value)
	{
		assert(value >= 0);
		if (value < 10)
			res += "0";
		res += std::to_string(value);
		return (res);
	};

	decompose_time(t, year, month, day, hours, minutes, seconds);

	if (!(hours == 0 && minutes == 0 && seconds == 0)) {
		display_with_2_digit(seconds);
		res += ":";
		display_with_2_digit(minutes);
		res += ":";
		display_with_2_digit(hours);
		res += " - ";
	}

	display_with_2_digit(day);
	res += ".";
	display_with_2_digit(month);
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
			d -= std::chrono::duration_cast<UniversalClock::duration>(duration_as_integer);
 		}
	};

	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::years>(d)), "Y");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::months>(d)), "M");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::days>(d)), "D");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::hours>(d)), "h");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::minutes>(d)), "m");

	if (d.count() > 0)
		res += std::to_string(d.count()) + "s";

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




////////////////////////////////////////////////////////////////////////////////
//                               CyclicalTimer                                //
////////////////////////////////////////////////////////////////////////////////




CyclicalTimer::CyclicalTimer(UniversalClock::duration frequency, UniversalClock::time_point next_update)
: I_Timer(), _frequency(frequency), _next_update(next_update)
{
	assert (UniversalClock::now() + frequency <= next_update);
	assert (frequency != UniversalClock::duration());

	_last_update = _next_update - frequency;
}

CyclicalTimer::CyclicalTimer(UniversalClock::duration frequency)
: CyclicalTimer(frequency, UniversalClock::now() + frequency)
{}

UniversalClock::time_point CyclicalTimer::next_update() const
{
	return (_next_update);
}

UniversalClock::time_point CyclicalTimer::next_next_update() const
{
	return (_next_update+ + _frequency);
}

UniversalClock::duration CyclicalTimer::frequency() const
{
	return (_frequency);
}

void CyclicalTimer::update(UniversalClock::time_point date)
{
	assert(_next_update <= date); // ensure we do need to update.
	assert(_next_update + _frequency > date); // ensure we did not missed a cycle.

	_last_update = _next_update;
	_next_update += _frequency;
}




////////////////////////////////////////////////////////////////////////////////
//                               ArbitraryTimer                               //
////////////////////////////////////////////////////////////////////////////////




ArbitraryTimer::ArbitraryTimer(UniversalClock::time_point next_update)
: I_Timer(), _next_update(next_update)
{}

UniversalClock::time_point ArbitraryTimer::next_update() const
{
	return (_next_update);
}

UniversalClock::time_point ArbitraryTimer::next_next_update() const
{
	return (I_Timer::max());
}

void ArbitraryTimer::update(UniversalClock::time_point date)
{
	assert(_next_update <= date); // ensure we do need to update.

	_last_update = _next_update;
	_next_update = I_Timer::max();
}




/*
                    _____      __             __      __
                   / ___/_____/ /_  ___  ____/ /_  __/ /__  _____
                   \__ \/ ___/ __ \/ _ \/ __  / / / / / _ \/ ___/
                  ___/ / /__/ / / /  __/ /_/ / /_/ / /  __/ /
                 /____/\___/_/ /_/\___/\__,_/\__,_/_/\___/_/
*/




Scheduler::Scheduler()
: I_Timer(), _cyclicals(), _abritraries(), _mutables()
{}

Scheduler::~Scheduler()
{}

static void find_next(Scheduler::container_t const & c,
                      UniversalClock::time_point & res)
{
	for (auto it = c.cbegin(); it != c.cend(); ++it)
		if ((*it)->next_update() < res)
			res = (*it)->next_update();
};

static void find_next_next(Scheduler::container_t const & c,
                           UniversalClock::time_point & res)
{
	for (auto it = c.cbegin(); it != c.cend(); ++it){
		if ((*it)->next_next_update() < res)
			res = (*it)->next_next_update();
		if ((*it)->next_update() < res)
			res = (*it)->next_update();		
	}
};

UniversalClock::time_point Scheduler::next_update() const
{
	UniversalClock::time_point res(UniversalClock::time_point::max());

	find_next(_cyclicals, res);
	find_next(_abritraries, res);
	find_next(_mutables, res);

	return (res);
}

UniversalClock::time_point Scheduler::next_next_update() const
{
	UniversalClock::time_point res(UniversalClock::time_point::max());

	find_next_next(_cyclicals, res);
	find_next_next(_abritraries, res);
	find_next_next(_mutables, res);

	return (res);
}

void Scheduler::update(UniversalClock::time_point date)
{
	auto adv = [date](auto & c, auto & l)
	{
		for (auto it = c.begin(); it != c.end(); ++it)
			if ((*it)->next_update() <= date) {
				(*it)->update(date);
				if (l < (*it)->last_update())
					l = (*it)->last_update();
			}
	};

	adv(_cyclicals, _last_update);
	adv(_abritraries, _last_update);
	adv(_mutables, _last_update);
}

UniversalClock::time_point Scheduler::can_adv_to(UniversalClock::time_point date) const
{
	UniversalClock::time_point res = next_update();
	return (res > date ? date : res);
}

void Scheduler::advance_until(UniversalClock::time_point date)
{
	UniversalClock::time_point tmp = next_update();

	while (tmp <= date) {
		update(tmp);
		tmp = next_update();
	}
}

void Scheduler::advance_until(UniversalClock::duration delta)
{
	advance_until(UniversalClock::now() + delta);
}

void Scheduler::clean_dead_timer()
{
}

void Scheduler::add(I_Timer & t)
{
	if (t.type() == I_Timer::Cyclical)
		_cyclicals.push_back(&t);
	else if (t.type() == I_Timer::Arbitrary)
		_abritraries.push_back(&t);
	else
		_mutables.push_back(&t);

	if (t.last_update() > _last_update)
		_last_update = t.last_update();
}

void Scheduler::clear()
{
	_cyclicals.clear();
	_abritraries.clear();
	_mutables.clear();

	_last_update = UniversalClock::time_point::max();
}

Scheduler::container_t const & Scheduler::cyclicals() const
{
	return (_cyclicals);
}

Scheduler::container_t & Scheduler::cyclicals()
{
	return (_cyclicals);
}

Scheduler::container_t const & Scheduler::abritraries() const
{
	return (_abritraries);
}

Scheduler::container_t & Scheduler::abritraries()
{
	return (_abritraries);
}

Scheduler::container_t const & Scheduler::mutables() const
{
	return (_mutables);
}

Scheduler::container_t & Scheduler::mutables()
{
	return (_mutables);
}
