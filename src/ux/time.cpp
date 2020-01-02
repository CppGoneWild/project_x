#include "ux/time.hh"

#include "ux/tools.hh"

#include "../time.hh"


#include "imgui.h"


static void display_timer(I_Timer const & timer)
{
	ImGui::ProgressBar(timer.progress(UniversalClock::now()));

	ux::display_context_remainder(timer);

	if (ImGui::IsItemHovered())
		ux::display_as_tooltip(timer);
}

static void display_scheduler(Scheduler const & scheduler)
{
	// Vertically align text node a bit lower so it'll be vertically centered with upcoming widget. Otherwise you can use SmallButton (smaller fit).
	ImGui::AlignTextToFramePadding();
	
	// Common mistake to avoid: if we want to SameLine after TreeNode we need to do it before we add child content.
	bool node_open = ImGui::TreeNode(&scheduler, "");
	
	ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
	display_timer(scheduler);

	if (node_open) {
		for (auto it = scheduler.crbegin(); it != scheduler.crend(); ++it)
			ux::display_as_tree_node(it->get());
		ImGui::TreePop();
	}
}




void ux::display_as_tree_node(I_Timer const & timer)
{
	auto const * is_scheduler = dynamic_cast<Scheduler const *>(&timer);
	if (is_scheduler)
		display_scheduler(*is_scheduler);
	else {

		{
			ux::ScopeID scope_id(&timer);
			display_timer(timer);			
		}

		{		
			ux::ScopeID scope_id(&timer + 1);
			ImGui::Bullet();
			ux::display_as_embedded_text(timer, ux::timer_mode::Remaining, true);
		}
		{
			ux::ScopeID scope_id(&timer + 2);
			ImGui::Bullet();
			ux::display_as_embedded_text(timer, ux::timer_mode::Date, true);			
		}

	}
}

void ux::display_as_tooltip(I_Timer const & timer)
{
	ImGui::BeginTooltip();

	ImGui::Bullet();
	display_as_embedded_text(timer, timer_mode::Remaining, false);

	ImGui::Bullet();
	display_as_embedded_text(timer, timer_mode::Date, false);

	ImGui::EndTooltip();
}

void ux::display_as_embedded_text(I_Timer const & timer, timer_mode mode, bool context_auth)
{
	static const ImVec4 im_yellow(255, 255, 0, 255);
	
	if (mode == timer_mode::Remaining) {
		auto remaining_duration = timer.next_update() - UniversalClock::now();
		ImGui::TextColored(im_yellow, "%s", UniversalClock::to_string(remaining_duration).c_str());

		if (context_auth)
			display_context_remainder(timer);

		ImGui::SameLine();
		ImGui::Text("remaining");
	}
	else {
		ImGui::Text("next update");
		ImGui::SameLine();
		ImGui::TextColored(im_yellow, "%s", UniversalClock::to_string(timer.next_update()).c_str());

		if (context_auth)
			display_context_remainder(timer);
	}
}


void ux::display_context_remainder(I_Timer const &)
{
	  if (ImGui::BeginPopupContextItem("date remainder context menu")) {
	      if (ImGui::Selectable("Set a remainder"))
	      	;
	      ImGui::EndPopup();
	  }	
}
