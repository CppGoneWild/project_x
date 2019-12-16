#ifndef TIME_HH
#define TIME_HH



#include <list>
#include <cstdint>
#include <ratio>
#include <chrono>
#include <ctime>      // struct tm;
#include <functional> // reference_wrapper
#include <sstream>
#include <iomanip>    // setprecision
#include <string>
#include <cassert>



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


	static time_point now() noexcept;
	static duration last_tic() noexcept;

	static duration advance(time_point) noexcept;
	static duration advance(duration) noexcept;
	template <class REP, class PERIOD>
	static duration advance(std::chrono::duration<REP, PERIOD>) noexcept;

	static std::tm to_tm(time_point) noexcept;

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



class I_Timer
{
public:
	using time_point = UniversalClock::time_point;

	virtual ~I_Timer();

	virtual time_point next_update() const = 0;
	virtual time_point next_next_update() const = 0;
	virtual void update(time_point date) = 0;

	double progress(time_point date) const;

	static time_point max();

	time_point last_update() const;

protected:
	I_Timer();
	I_Timer(I_Timer const &) = default;
	I_Timer(I_Timer &&)      = default;

	I_Timer & operator=(I_Timer const &) = default;
	I_Timer & operator=(I_Timer &&)      = default;

	time_point _last_update;
};



class Timer : public I_Timer
{
public:
	using duration   = UniversalClock::duration;

	Timer()                   = default;
	Timer(Timer const &)      = default;
	Timer(Timer &&)           = default;
	virtual ~Timer() override = default;

	Timer & operator=(Timer const &) = default;
	Timer & operator=(Timer &&)      = default;

	explicit Timer(time_point next_update); // single shot mode
	Timer(duration frequency, time_point current_time);
	template <class D> Timer(D frequency, time_point current_time);

	virtual time_point next_update() const override;
	virtual time_point next_next_update() const override;
	time_point & next_update();

	duration frequency() const;
	duration & frequency();

	virtual void update(time_point date) override;

private:
	duration _frequency;
	time_point _next_update;
};



class Scheduler : public I_Timer
{
public:
	using container_t = std::vector<std::reference_wrapper<I_Timer>>;

	using iterator               = container_t::iterator;
	using const_iterator         = container_t::const_iterator;
	using reverse_iterator       = container_t::reverse_iterator;
	using const_reverse_iterator = container_t::const_reverse_iterator;

	Scheduler()                   = default;
	Scheduler(Scheduler const &)  = default;
	Scheduler(Scheduler &&)       = default;
	virtual ~Scheduler() override = default;

	virtual time_point next_update() const override;
	virtual time_point next_next_update() const override;
	virtual void update(time_point date) override;

	time_point can_adv_to(time_point date) const;

	void advance_until(time_point date);
	void advance_until(UniversalClock::duration delta);
	template <class D> void advance_until(D delta);

	/**
	 * @brief return if is sorted by time in REVERSE order
	 */
	bool is_sorted() const;

	/**
	 * @brief stable sort by time in REVERSE order
	 */
	void sort();
	void clean_dead_timer();

	void add(I_Timer &);
	void add_and_sort(I_Timer &);

	template <class IT> void add(IT, IT);
	template <class IT> void add_and_sort(IT, IT);

	bool empty() const;
	std::size_t size() const;

	void clear();

	void erase(iterator);
	void erase(const_iterator);
	void erase(iterator, iterator);
	void erase(const_iterator, const_iterator);

	iterator begin();
	iterator end();

	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	container_t const & container() const;
	container_t & container();

private:
	container_t _updatable;
};



#include "time.ipp"



#endif // TIME_HH
