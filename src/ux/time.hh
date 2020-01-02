#ifndef UX_TIME_HH
#define UX_TIME_HH




class I_Timer;



namespace ux
{


void display_as_tree_node(I_Timer const &);

void display_as_tooltip(I_Timer const &);


enum class timer_mode { Remaining, Date };
void display_as_embedded_text(I_Timer const &, timer_mode, bool context_auth);

void display_context_remainder(I_Timer const &);


} // ux


#endif // UX_TIME_HH
