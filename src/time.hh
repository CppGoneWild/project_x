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

	template <class REP, class PERIOD>
	static duration advance(std::chrono::duration<REP, PERIOD>) noexcept;
	static duration advance(time_point) noexcept;

	static std::tm to_tm(time_point) noexcept;

	static std::string to_string(time_point);
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



template <class REP, class PERIOD>
UniversalClock::duration UniversalClock::advance(std::chrono::duration<REP, PERIOD> d) noexcept
{
	_last_tic = std::chrono::duration_cast<UniversalClock::seconds>(d);
	_now += _last_tic;
	return (_last_tic);
}

template <class D>
D to_integer_duration(D d)
{
	return (D(int(d.count())));
}

template <class REP, class PERIOD>
std::string UniversalClock::to_string(std::chrono::duration<REP, PERIOD> d)
{
	std::string res;

	auto write_duration_order = [&res, &d](auto duration_as_integer, char const * const c_unit)
	{
		if (duration_as_integer.count() >= 1.0) {
			res += std::to_string(int(duration_as_integer.count())) + c_unit;
			d -= std::chrono::duration_cast<UniversalClock::seconds>(duration_as_integer);
 		}
	};

	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::century>(d)), "C");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::years>(d)), "Y");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::months>(d)), "M");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::days>(d)),  "d");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::hours>(d)), "h");
	write_duration_order(to_integer_duration(std::chrono::duration_cast<UniversalClock::minutes>(d)), "m");

	if (d.count() > 0)
		res += std::to_string(d.count()) + "s";

	return (res);
}



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



template <class D>
Timer::Timer(D frequency, time_point current_time)
: I_Timer(),
  _frequency(std::chrono::duration_cast<duration>(frequency)),
  _next_update(current_time + _frequency)
{
	assert(_frequency != duration()); // use single shot mode
	_last_update = current_time;
}



/**
 * @brief [brief description]
 * @details [long description]
 * @exemple
 * @code{.cpp}
	void exemple(time_point objective)
	{
		Scheduler scd;
		Scheduler::iterator first, last;
	
		assert(scd.is_sorted());
	
		for (time_point intermediate = scd.can_adv_to(objective, first, last);
			            intermediate <= objective;
			            intermediate = scd.can_adv_to(objective, first, last)) {
			for (; first != last; first++)
				first->update(intermediate);
			scd.sort();
		}
		scd.clean_dead_timer();
	}
 * @endcode
 */
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



template <class IT>
void Scheduler::add(IT first, IT last)
{
	for (; first != last; first++)
		add(*first);
}

template <class IT>
void Scheduler::add_and_sort(IT first, IT last)
{
	add(first, last);
	sort();
}




#endif // TIME_HH
