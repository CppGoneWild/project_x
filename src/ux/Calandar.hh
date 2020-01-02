#ifndef CALANDAR_HH
#define CALANDAR_HH




#include "Window.hh"

#include <string>




class Scheduler;




namespace ux
{


class Calandar : public Window
{
public:
	explicit Calandar(Scheduler &);
	virtual ~Calandar() = default;

	virtual void display() override;

private:
	Calandar()                             = default;
	Calandar(Calandar const &)             = delete;
	Calandar(Calandar &&)                  = delete;

	Calandar & operator=(Calandar const &) = delete;
	Calandar & operator=(Calandar &&)      = delete;

	Scheduler * _scheduler;
	int _time_incr = 1;
	std::string _imgui_win_title;
};


} // ux


#endif // CALANDAR_HH
