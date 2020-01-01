#ifndef CALANDAR_HH
#define CALANDAR_HH


#include <string>


class Scheduler;


namespace ux
{


class Calandar
{
public:
	Calandar()  = default;
	~Calandar() = default;

	void display(Scheduler &);

private:
	Calandar(Calandar const &)             = delete;
	Calandar(Calandar &&)                  = delete;

	Calandar & operator=(Calandar const &) = delete;
	Calandar & operator=(Calandar &&)      = delete;

	int _time_incr = 1;
	std::string _imgui_win_title;
};


} // ux


#endif // CALANDAR_HH
