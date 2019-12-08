#ifndef UNIVERSAL_CLOCK_HH
#define UNIVERSAL_CLOCK_HH



#include <cstdint>
#include <ratio>
#include <chrono>
#include <ctime> // struct tm;



class UniversalClock
{
public:
	using rep    = std::int64_t;
	using period = std::ratio<1>;

	using duration   = std::chrono::duration<rep, period>;
	using time_point = std::chrono::time_point<UniversalClock>;

	static const bool is_steady = false;


	using seconds  = duration;
	using minutes  = std::chrono::duration<double, std::ratio<60>>;
	using hours    = std::chrono::duration<double, std::ratio<3600>>;
	using days     = std::chrono::duration<double, std::ratio<86400>>;
	using weeks    = std::chrono::duration<double, std::ratio<604800>>;
	using months   = std::chrono::duration<double, std::ratio<2629746>>;   ///< Exactly 1/12 of a year
	using years    = std::chrono::duration<double, std::ratio<31556952>>;  ///<  365.2425 days
	using century  = std::chrono::duration<double, std::ratio<3155695200>>;
	using milenary = std::chrono::duration<double, std::ratio<31556952000>>;


	static time_point now() noexcept;
	static duration last_tic() noexcept;

	template <class REP, class PERIOD>
	static duration advance(std::chrono::duration<REP, PERIOD> d) noexcept;
	static duration advance(time_point) noexcept;

	static std::tm to_tm(time_point) noexcept;

private:
	UniversalClock()                       = delete;
	UniversalClock(UniversalClock const &) = delete;
	UniversalClock(UniversalClock &&)      = delete;
	~UniversalClock()                      = delete;

	UniversalClock & operator=(UniversalClock const &) = delete;
	UniversalClock & operator=(UniversalClock &&)      = delete;


	static time_point _now;
	static duration _last_tic;
};



template <class REP, class PERIOD>
UniversalClock::duration UniversalClock::advance(std::chrono::duration<REP, PERIOD> d) noexcept
{
	_last_tic = UniversalClock::seconds(UniversalClock::rep(d.count()) * PERIOD::num);
	_now += _last_tic;
	return (_last_tic);
}



#endif // UNIVERSAL_CLOCK_HH
