#ifndef TIME_HH
#define TIME_HH




#include <list>
#include <functional> // reference_wrapper

#include <string>
#include <sstream>    // serialisation (sstring + setprecision)
#include <iomanip>    // setprecision

#include <cstdint>

#include <ratio>
#include <chrono>
#include <ctime>      // struct tm;

#include <cassert>




/*
          __  __      _                            __________           __
         / / / /___  (_)   _____  ______________ _/ / ____/ /___  _____/ /__
        / / / / __ \/ / | / / _ \/ ___/ ___/ __ `/ / /   / / __ \/ ___/ //_/
       / /_/ / / / / /| |/ /  __/ /  (__  ) /_/ / / /___/ / /_/ / /__/ ,<
       \____/_/ /_/_/ |___/\___/_/  /____/\__,_/_/\____/_/\____/\___/_/|_|
       
*/




class UniversalClock
{
public:
	using rep    = std::int64_t;
	using period = std::ratio<1>;

	using duration   = std::chrono::duration<rep, period>;
	using time_point = std::chrono::time_point<UniversalClock>;

	static const bool is_steady = false;


	using seconds = duration;
	using minutes = std::chrono::duration<double, std::ratio<60>>;
	using hours   = std::chrono::duration<double, std::ratio<3600>>;
	using days    = std::chrono::duration<double, std::ratio<86400>>;
	using months  = std::chrono::duration<double, std::ratio<2592000>>;
	using years   = std::chrono::duration<double, std::ratio<31104000>>;


	static time_point now() noexcept;
	static duration last_tic() noexcept;

	static duration advance(time_point) noexcept;
	static duration advance(duration) noexcept;
	template <class REP, class PERIOD>
	static duration advance(std::chrono::duration<REP, PERIOD>) noexcept;

	static std::string to_string(time_point);
	static std::string to_string(duration d);

	template <class REP, class PERIOD>
	static std::string to_string(std::chrono::duration<REP, PERIOD>);

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




/*
                       ____   _______
                      /  _/  /_  __(_)___ ___  ___  _____
                      / /     / / / / __ `__ \/ _ \/ ___/
                    _/ /     / / / / / / / / /  __/ /
                   /___/____/_/ /_/_/ /_/ /_/\___/_/
                      /_____/

*/




class I_Timer
{
public:
	enum Type { Cyclical, Arbitrary, Mutable };

	virtual ~I_Timer();

	virtual Type type() const = 0;

	virtual UniversalClock::time_point next_update() const = 0;
	virtual UniversalClock::time_point next_next_update() const = 0;
	virtual void update(UniversalClock::time_point date) = 0;

	double progress(UniversalClock::time_point date) const;

	static UniversalClock::time_point max();

	UniversalClock::time_point last_update() const;

protected:
	I_Timer();
	I_Timer(I_Timer const &) = default;
	I_Timer(I_Timer &&)      = default;

	I_Timer & operator=(I_Timer const &) = default;
	I_Timer & operator=(I_Timer &&)      = default;

	UniversalClock::time_point _last_update;
};




/*
                          _______
                         /_  __(_)___ ___  ___  _____
                          / / / / __ `__ \/ _ \/ ___/
                         / / / / / / / / /  __/ /
                        /_/ /_/_/ /_/ /_/\___/_/
                        
*/




class CyclicalTimer : public I_Timer
{
public:
	CyclicalTimer()                      = default;
	CyclicalTimer(CyclicalTimer const &) = default;
	CyclicalTimer(CyclicalTimer &&)      = default;
	virtual ~CyclicalTimer() override    = default;

	CyclicalTimer & operator=(CyclicalTimer const &) = default;
	CyclicalTimer & operator=(CyclicalTimer &&)      = default;

	CyclicalTimer(UniversalClock::duration frequency, UniversalClock::time_point next);
	template <class D> CyclicalTimer(D frequency, UniversalClock::time_point next);

	CyclicalTimer(UniversalClock::duration frequency);
	template <class D> CyclicalTimer(D frequency);

	virtual Type type() const override { return (Cyclical); };

	virtual UniversalClock::time_point next_update() const override;
	virtual UniversalClock::time_point next_next_update() const override;

	UniversalClock::duration frequency() const;

	virtual void update(UniversalClock::time_point date) override;

private:
	UniversalClock::duration _frequency;
	UniversalClock::time_point _next_update;
};




class ArbitraryTimer : public I_Timer
{
public:
	ArbitraryTimer()                       = default;
	ArbitraryTimer(ArbitraryTimer const &) = default;
	ArbitraryTimer(ArbitraryTimer &&)      = default;
	virtual ~ArbitraryTimer() override     = default;

	ArbitraryTimer & operator=(ArbitraryTimer const &) = default;
	ArbitraryTimer & operator=(ArbitraryTimer &&)      = default;

	virtual Type type() const override { return (Arbitrary); };

	ArbitraryTimer(UniversalClock::time_point next_update);
	template <class D> ArbitraryTimer(UniversalClock::time_point next_update);

	virtual UniversalClock::time_point next_update() const override;
	virtual UniversalClock::time_point next_next_update() const override;

	virtual void update(UniversalClock::time_point date) override;

private:
	UniversalClock::time_point _next_update;
};




/*
                  _____      __             __      __
                 / ___/_____/ /_  ___  ____/ /_  __/ /__  _____
                 \__ \/ ___/ __ \/ _ \/ __  / / / / / _ \/ ___/
                ___/ / /__/ / / /  __/ /_/ / /_/ / /  __/ /
               /____/\___/_/ /_/\___/\__,_/\__,_/_/\___/_/
               
*/




class Scheduler : public I_Timer
{
public:
	using container_t = std::list<I_Timer *>;

	Scheduler();
	virtual ~Scheduler() override;

	virtual Type type() const override { return (Mutable); };

	virtual UniversalClock::time_point next_update() const override;
	virtual UniversalClock::time_point next_next_update() const override;
	virtual void update(UniversalClock::time_point date) override;

	UniversalClock::time_point can_adv_to(UniversalClock::time_point date) const;

	void advance_until(UniversalClock::time_point date);
	void advance_until(UniversalClock::duration delta);
	template <class D> void advance_until(D delta);

	/**
	 * @brief stable sort by time in REVERSE order
	 */
	void clean_dead_timer();

	void add(I_Timer &);
	void clear();

	container_t const & cyclicals() const;
	container_t & cyclicals();

	container_t const & abritraries() const;
	container_t & abritraries();

	container_t const & mutables() const;
	container_t & mutables();

private:
	Scheduler(Scheduler const &)             = delete;
	Scheduler(Scheduler &&)                  = delete;
	Scheduler & operator=(Scheduler const &) = delete;
	Scheduler & operator=(Scheduler &&)      = delete;

	container_t _cyclicals;
	container_t _abritraries;
	container_t _mutables;
};




#include "time.ipp"




#endif // TIME_HH
