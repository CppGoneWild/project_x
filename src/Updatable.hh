#ifndef UPDATABLE_HH
#define UPDATABLE_HH




template <class TM_POINT, class DURATION>
class Updatable
{
public:
	using time_point = TM_POINT;
	using duration   = DURATION;

	Updatable()                                        = default;
	Updatable(Updatable<time_point, duration> const &) = default;
	Updatable(Updatable<time_point, duration> &&)      = default;
	~Updatable()                                       = default;

	Updatable<time_point, duration> & operator=(Updatable<time_point, duration> const &) = default;
	Updatable<time_point, duration> & operator=(Updatable<time_point, duration> &&)      = default;

	explicit Updatable(time_point next_update); // single shot mode
	Updatable(duration frequency, time_point current_time);

	duration frequency() const;
	time_point next_update() const;

	duration & frequency();
	time_point & next_update();

	bool is_single_shot() const;

	std::pair<time_point, bool> can_adv_to(time_point date) const;
	void update(time_point date);

private:
	duration _frequency;
	time_point _next_update;
};


template <CLOCK>
using Updatable_t = Updatable<CLOCK::time_point, CLOCK::duration>;



#include "Updatable.ipp"



#endif // UPDATABLE_HH
