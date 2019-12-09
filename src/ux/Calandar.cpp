#include "Calandar.hh"

#include "logg.hh"
#include "UniversalClock.hh"


#include "imgui.h"


#include <ctime>  // struct tm;


void ux::Calandar::display()
{
	std::tm tm = UniversalClock::to_tm(UniversalClock::now());
	std::size_t size_copied = std::strftime(buffer_strftime, size_buffer_strftime, "%S:%M:%H %a %b %d-%m-%Y", &tm);

	if (size_copied >= size_buffer_strftime || size_copied == 0) {
		COUT_ERROR << "std::strftime returned " << std::to_string(size_copied);
		return ;
	}
	imgui_win_title = buffer_strftime;
	imgui_win_title += "###Calandar";

	if (ImGui::Begin(imgui_win_title.c_str())) {
		ImGui::DragInt("Advance by : ", &time_incr);
		if (ImGui::Button("sec")) UniversalClock::advance(UniversalClock::seconds(time_incr));
		ImGui::SameLine();
		if (ImGui::Button("min")) UniversalClock::advance(UniversalClock::minutes(time_incr));
		ImGui::SameLine();
		if (ImGui::Button("hour")) UniversalClock::advance(UniversalClock::hours(time_incr));
		ImGui::SameLine();
		if (ImGui::Button("day")) UniversalClock::advance(UniversalClock::days(time_incr));
		ImGui::SameLine();
		if (ImGui::Button("week")) UniversalClock::advance(UniversalClock::weeks(time_incr));
		ImGui::SameLine();
		if (ImGui::Button("month")) UniversalClock::advance(UniversalClock::months(time_incr));
		ImGui::SameLine();
		if (ImGui::Button("year")) UniversalClock::advance(UniversalClock::years(time_incr));
	}
	ImGui::End();
}
