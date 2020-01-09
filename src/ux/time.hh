#ifndef UX_TIME_HH
#define UX_TIME_HH


#include "tools.hh"




class I_Timer;



namespace ux
{


void display_in_tree(I_Timer const &, PopupContextMenu &);

void display_in_tooltip(I_Timer const &);


enum class timer_mode { Remaining, Date };
void display_in_text(I_Timer const &, timer_mode);
void display_in_text(I_Timer const &, timer_mode, PopupContextMenu &);

void display_in_context(I_Timer const &, PopupContextMenu &);


} // ux


#endif // UX_TIME_HH
