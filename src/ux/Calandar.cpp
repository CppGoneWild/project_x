#include "Calandar.hh"

#include "logg.hh"
#include "../time.hh"
#include "ux/time.hh"


#include "imgui.h"


ux::Calandar::Calandar(Scheduler & s)
: Window(), _scheduler(&s)
{}

void ux::Calandar::display()
{
	assert(_scheduler);

	_imgui_win_title = UniversalClock::to_string(UniversalClock::now());
	_imgui_win_title += "###Calandar";

	if (ImGui::Begin(_imgui_win_title.c_str(), &_open)) {
		ImGui::DragInt("Advance by : ", &_time_incr);
		ImGui::SameLine();
		if (ImGui::Button("day")) _scheduler->advance_until(UniversalClock::days(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("month")) _scheduler->advance_until(UniversalClock::months(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("year")) _scheduler->advance_until(UniversalClock::years(_time_incr));

		ux::display_as_tree_node(*_scheduler);
	}
	ImGui::End();
}
