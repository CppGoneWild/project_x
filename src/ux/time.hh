#ifndef UX_TIME_HH
#define UX_TIME_HH


#include "tools.hh"
#include "Window.hh"

#include <string>




class I_Timer;
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




void display_in_tree(I_Timer const &, PopupContextMenu &);

void display_in_tooltip(I_Timer const &);

enum class timer_mode { Remaining, Date };

void display_in_text(I_Timer const &, timer_mode);
void display_in_text(I_Timer const &, timer_mode, PopupContextMenu &);

void display_in_context(I_Timer const &, PopupContextMenu &);




} // ux




#endif // UX_TIME_HH
