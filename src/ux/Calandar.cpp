#include "Calandar.hh"

#include "logg.hh"
#include "time.hh"


#include "imgui.h"



static void display_scheduler(Scheduler & scheduler)
{
	ImGui::AlignTextToFramePadding();         // Vertically align text node a bit lower so it'll be vertically centered with upcoming widget. Otherwise you can use SmallButton (smaller fit).
	bool node_open = ImGui::TreeNode(&scheduler, "");  // Common mistake to avoid: if we want to SameLine after TreeNode we need to do it before we add child content.
	ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
	ImGui::ProgressBar(scheduler.progress(UniversalClock::now()), ImVec2(-1, 0), UniversalClock::to_string(scheduler.next_update() - UniversalClock::now()).c_str());

	if (node_open) {
		for (auto it = scheduler.crbegin(); it != scheduler.crend(); ++it) {

			auto const * is_scheduler = dynamic_cast<Scheduler const *>(&it->get());
			if (is_scheduler) {
				display_scheduler(scheduler);
			}
			else {
				ImGui::TreePush(&it->get());
				ImGui::ProgressBar(it->get().progress(UniversalClock::now()), ImVec2(-1, 0), UniversalClock::to_string(it->get().next_update() - UniversalClock::now()).c_str());
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
}

void ux::Calandar::display(Scheduler & scheduler)
{
	_imgui_win_title = UniversalClock::to_string(UniversalClock::now());
	_imgui_win_title += "###Calandar";

	if (ImGui::Begin(_imgui_win_title.c_str())) {
		ImGui::DragInt("Advance by : ", &_time_incr);
		ImGui::SameLine();
		if (ImGui::Button("day")) scheduler.advance_until(UniversalClock::days(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("month")) scheduler.advance_until(UniversalClock::months(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("year")) scheduler.advance_until(UniversalClock::years(_time_incr));

		display_scheduler(scheduler);
	}
	ImGui::End();
}
