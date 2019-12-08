#include "UniversalClock.hh"



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

std::tm UniversalClock::to_tm(time_point t) noexcept
{
	static constexpr int linux_epoch_years = 1900;
	static constexpr int project_x_epoch_years = 4242;

	static std::tm res;

	res.tm_year = t.time_since_epoch().count() / years::period::num;

	res.tm_mon  = (t.time_since_epoch().count() - res.tm_year * years::period::num) / months::period::num;
	res.tm_mday = (t.time_since_epoch().count() - res.tm_year * years::period::num - res.tm_mon * months::period::num) / days::period::num;
	res.tm_hour = (t.time_since_epoch().count() - res.tm_year * years::period::num - res.tm_mon * months::period::num - res.tm_mday * days::period::num) / hours::period::num;
	res.tm_min  = (t.time_since_epoch().count() - res.tm_year * years::period::num - res.tm_mon * months::period::num - res.tm_mday * days::period::num - res.tm_hour * hours::period::num) / minutes::period::num;
	res.tm_sec  = (t.time_since_epoch().count() - res.tm_year * years::period::num - res.tm_mon * months::period::num - res.tm_mday * days::period::num - res.tm_hour * hours::period::num - res.tm_min * minutes::period::num);

	res.tm_year = res.tm_year - linux_epoch_years + project_x_epoch_years;

	res.tm_wday = t.time_since_epoch().count() / days::period::num % 7;
	res.tm_yday = (t.time_since_epoch().count() - res.tm_year % years::period::num) / days::period::num;

	res.tm_isdst = -1;

	return (res);
}


