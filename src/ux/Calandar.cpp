#include "Calandar.hh"

#include "logg.hh"
#include "UniversalClock.hh"


#include "imgui.h"


#include <ctime>  // struct tm;


void ux::Calandar::display()
{
	std::tm tm = UniversalClock::to_tm(UniversalClock::now());
	std::size_t size_copied = std::strftime(_buffer_strftime, _size_buffer_strftime, "%S:%M:%H %a %b %d-%m-%Y", &tm);

	if (size_copied >= _size_buffer_strftime || size_copied == 0) {
		COUT_ERROR << "std::strftime returned " << std::to_string(size_copied);
		return ;
	}
	_imgui_win_title = _buffer_strftime;
	_imgui_win_title += "###Calandar";

	if (ImGui::Begin(_imgui_win_title.c_str())) {
		ImGui::DragInt("Advance by : ", &_time_incr);
		if (ImGui::Button("sec")) UniversalClock::advance(UniversalClock::seconds(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("min")) UniversalClock::advance(UniversalClock::minutes(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("hour")) UniversalClock::advance(UniversalClock::hours(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("day")) UniversalClock::advance(UniversalClock::days(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("week")) UniversalClock::advance(UniversalClock::weeks(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("month")) UniversalClock::advance(UniversalClock::months(_time_incr));
		ImGui::SameLine();
		if (ImGui::Button("year")) UniversalClock::advance(UniversalClock::years(_time_incr));
	}
	ImGui::End();
}
