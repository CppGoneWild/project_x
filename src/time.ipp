/*
        __  __      _                            __________           __
       / / / /___  (_)   _____  ______________ _/ / ____/ /___  _____/ /__
      / / / / __ \/ / | / / _ \/ ___/ ___/ __ `/ / /   / / __ \/ ___/ //_/
     / /_/ / / / / /| |/ /  __/ /  (__  ) /_/ / / /___/ / /_/ / /__/ ,<
     \____/_/ /_/_/ |___/\___/_/  /____/\__,_/_/\____/_/\____/\___/_/|_|

*/

template <class REP, class PERIOD>
UniversalClock::duration UniversalClock::advance(std::chrono::duration<REP, PERIOD> d) noexcept
{
	return (UniversalClock::advance(std::chrono::duration_cast<duration>(d)));
}

template <class REP, class PERIOD>
std::string UniversalClock::to_string(std::chrono::duration<REP, PERIOD> d)
{
	return (UniversalClock::to_string(std::chrono::duration_cast<duration>(d)));
}



/*
                          _______
                         /_  __(_)___ ___  ___  _____
                          / / / / __ `__ \/ _ \/ ___/
                         / / / / / / / / /  __/ /
                        /_/ /_/_/ /_/ /_/\___/_/
*/



template <class D>
Timer::Timer(D frequency, UniversalClock::time_point current_time)
: Timer(std::chrono::duration_cast<UniversalClock::duration>(frequency), current_time)
{}



/*
                    _____      __             __      __
                   / ___/_____/ /_  ___  ____/ /_  __/ /__  _____
                   \__ \/ ___/ __ \/ _ \/ __  / / / / / _ \/ ___/
                  ___/ / /__/ / / /  __/ /_/ / /_/ / /  __/ /
                 /____/\___/_/ /_/\___/\__,_/\__,_/_/\___/_/
*/


template <class D>
void Scheduler::advance_until(D delta)
{
	advance_until(std::chrono::duration_cast<UniversalClock::duration>(delta));
}

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
