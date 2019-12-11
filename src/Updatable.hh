#ifndef UPDATABLE_HH
#define UPDATABLE_HH



#include "UniversalClock.hh"



class Timer
{
public:
	using time_point = UniversalClock::time_point;
	using duration   = UniversalClock::duration;

	Timer()                  = default;
	Timer(Timer const &) = default;
	Timer(Timer &&)      = default;
	~Timer()                 = default;

	Timer & operator=(Timer const &) = default;
	Timer & operator=(Timer &&)      = default;

	explicit Timer(time_point next_update); // single shot mode
	Timer(duration frequency, time_point current_time);

	duration frequency() const;
	time_point next_update() const;

	duration & frequency();
	time_point & next_update();

	bool is_single_shot() const;

	/**
	 * @brief return max date when it can advance.
	 * 
	 * @return res.second is false if it do not need an update this round.
	 *         res.first is the maximum date you can go if it need to advance this round (std::min(next_update, date)).
	 */
	std::pair<time_point, bool> can_adv_to(time_point date) const;
	void update(time_point date);

private:
	duration _frequency;
	time_point _next_update;
};


// std::pair<time_point, bool> operator+(std::pair<time_point, bool> const & a, std::pair<time_point, bool> const & b)
// {
	// return (std::pair<time_point, bool>(std::min(a.first, b.first), a.second | b.second));
// }


class I_Updatable
{
public:
	using time_point = UniversalClock::time_point;

	virtual ~I_Updatable(/* args */) = default;

	virtual std::pair<time_point, bool> can_adv_to(time_point date) const = 0;

	virtual void update(time_point date) = 0;

protected:
	I_Updatable(I_Updatable const &) = default;
	I_Updatable(I_Updatable &&)      = default;

	I_Updatable & operator=(I_Updatable const &) = default;
	I_Updatable & operator=(I_Updatable &&)      = default;
};



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
class Scheduler
{
public:
	using container_t = std::list<I_Updatable &>;
	using value_type = container_t::value_type;

	using iterator               = container_t::iterator;
	using const_iterator         = container_t::const_iterator;
	using reverse_iterator       = container_t::reverse_iterator;
	using const_reverse_iterator = container_t::const_reverse_iterator;

	struct less
	{
		bool operator()(Timer const &, Timer const &);
		bool operator()(I_Updatable const &, I_Updatable const &);

		bool operator()(Timer const &, I_Updatable const &);
		bool operator()(I_Updatable const &, Timer const &);
	};

	Scheduler()                  = default;
	Scheduler(Scheduler const &) = default;
	Scheduler(Scheduler &&)      = default;
	~Scheduler()                 = default;

	bool empty() const;
	std::size_t size() const;

	bool is_sorted() const;
	void sort();
	void clean_dead_timer();

	void add(I_Updatable &);
	void add_and_sort(I_Updatable &);

	template <class IT> void add(IT, IT);
	template <class IT> void add_and_sort(IT, IT);

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

	time_point can_adv_to(time_point date, iterator & out_first, iterator & out_last) const;

private:
	std::list<I_Updatable &> _updatable;
};



#endif // UPDATABLE_HH
