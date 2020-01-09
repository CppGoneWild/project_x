#include "ux/time.hh"

#include "../time.hh"

#include "logg.hh"

#include "imgui.h"




/*
                     ______      __                __
                    / ____/___ _/ /___ _____  ____/ /___ ______
                   / /   / __ `/ / __ `/ __ \/ __  / __ `/ ___/
                  / /___/ /_/ / / /_/ / / / / /_/ / /_/ / /
                  \____/\__,_/_/\__,_/_/ /_/\__,_/\__,_/_/
                  
*/




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
		if (ImGui::Button("day")) { _scheduler->advance_until(UniversalClock::days(_time_incr)); UniversalClock::advance(UniversalClock::days(_time_incr));}
		ImGui::SameLine();
		if (ImGui::Button("month")) { _scheduler->advance_until(UniversalClock::months(_time_incr)); UniversalClock::advance(UniversalClock::months(_time_incr));}
		ImGui::SameLine();
		if (ImGui::Button("year")) { _scheduler->advance_until(UniversalClock::years(_time_incr)); UniversalClock::advance(UniversalClock::years(_time_incr));}

		PopupContextMenu cm("Calandar context");
		ux::display_in_tree(*_scheduler, cm);
	}
	ImGui::End();
}




/*
                               ___            __
                          ____/ (_)________  / /___ ___  __
                         / __  / / ___/ __ \/ / __ `/ / / /
                        / /_/ / (__  ) /_/ / / /_/ / /_/ /
                        \__,_/_/____/ .___/_/\__,_/\__, /
                                   /_/            /____/
*/




static void display_timer(I_Timer const & timer, ux::PopupContextMenu & context_id)
{
	ImGui::ProgressBar(timer.progress(UniversalClock::now()));

	ux::display_in_context(timer, context_id);


	if (ImGui::IsItemHovered())
		ux::display_in_tooltip(timer);
}

static void display_scheduler(Scheduler const & scheduler, ux::PopupContextMenu & context_id)
{
	// Vertically align text node a bit lower so it'll be vertically centered with upcoming widget. Otherwise you can use SmallButton (smaller fit).
	ImGui::AlignTextToFramePadding();
	
	// Common mistake to avoid: if we want to SameLine after TreeNode we need to do it before we add child content.
	bool node_open = ImGui::TreeNode(&scheduler, "scheduler");
	
	ux::display_in_context(scheduler, context_id);
	if (ImGui::IsItemHovered())
		ux::display_in_tooltip(scheduler);

	if (node_open) {
		auto display = [](Scheduler::container_t const & c, ux::PopupContextMenu & context_id)
		{
			for (auto it = c.cbegin(); it != c.cend(); ++it)
				ux::display_in_tree(**it, context_id);
		};

		display(scheduler.cyclicals(), context_id);
		display(scheduler.abritraries(), context_id);
		display(scheduler.mutables(), context_id);

		ImGui::TreePop();
	}
}


void ux::display_in_tree(I_Timer const & timer, PopupContextMenu & context_id)
{
	auto const * is_scheduler = dynamic_cast<Scheduler const *>(&timer);
	if (is_scheduler)
		display_scheduler(*is_scheduler, context_id);
	else {

		{
			ux::ScopeID scope_id(&timer);
			display_timer(timer, context_id);			
		}

		{		
			ux::ScopeID scope_id(&timer + 1);
			ImGui::Bullet();
			ux::display_in_text(timer, ux::timer_mode::Date, context_id);			
			ImGui::SameLine(); ImGui::Text("("); ImGui::SameLine();
			{		
				ux::ScopeID scope_id(&timer + 2);
				display_in_text(timer, timer_mode::Remaining, context_id);
			}
			ImGui::SameLine(); ImGui::Text(")");
		}

	}
}


void ux::display_in_tooltip(I_Timer const & timer)
{
	ux::ScopeToolTips sctt;

	ImGui::Bullet();

	display_in_text(timer, timer_mode::Date);

	ImGui::SameLine(); ImGui::Text("("); ImGui::SameLine();
	display_in_text(timer, timer_mode::Remaining);
	ImGui::SameLine(); ImGui::Text(")");
}


void ux::display_in_text(I_Timer const & timer, timer_mode mode)
{
	static const ImVec4 im_yellow(255, 255, 0, 255);
	
	if (mode == timer_mode::Remaining) {
		auto remaining_duration = timer.next_update() - UniversalClock::now();
		ImGui::TextColored(im_yellow, "%s", UniversalClock::to_string(remaining_duration).c_str());
	}
	else {
		ImGui::TextColored(im_yellow, "%s", UniversalClock::to_string(timer.next_update()).c_str());
	}
}

void ux::display_in_text(I_Timer const & timer, timer_mode mode, PopupContextMenu & context_id)
{
	display_in_text(timer, mode);
	display_in_context(timer, context_id);
}


void ux::display_in_context(I_Timer const &, PopupContextMenu & context_id)
{
	PopupContextMenu::Scope scpcm(context_id);
	if (scpcm && ImGui::Selectable("Set a remainder"))
		;
}
