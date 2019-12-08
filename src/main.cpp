#include "logg.hh"

#include "UniversalClock.hh"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>


logg::Timer globaltimer;
logg::Timer rendertimer;
logg::Timer imguitimer;


void clock_ctrl()
{
	static int delta_time = 1;

	if (ImGui::Begin("Clock")) {
		ImGui::DragInt("Advance by : ", &delta_time);
		if (ImGui::Button("sec")) UniversalClock::advance(UniversalClock::seconds(delta_time));
		ImGui::SameLine();
		if (ImGui::Button("min")) UniversalClock::advance(UniversalClock::minutes(delta_time));
		ImGui::SameLine();
		if (ImGui::Button("hour")) UniversalClock::advance(UniversalClock::hours(delta_time));
		ImGui::SameLine();
		if (ImGui::Button("day")) UniversalClock::advance(UniversalClock::days(delta_time));
		ImGui::SameLine();
		if (ImGui::Button("week")) UniversalClock::advance(UniversalClock::weeks(delta_time));
		ImGui::SameLine();
		if (ImGui::Button("month")) UniversalClock::advance(UniversalClock::months(delta_time));
		ImGui::SameLine();
		if (ImGui::Button("year")) UniversalClock::advance(UniversalClock::years(delta_time));
		std::tm tm = UniversalClock::to_tm(UniversalClock::now());
		ImGui::BulletText("time is %s", std::asctime(&tm));
	}
	ImGui::End();
}


void debug_timer_ctrl()
{
	if (ImGui::Begin("Profiling")) {
		if (ImGui::Button("reset timers")) {
			globaltimer.reset_stat();
			rendertimer.reset_stat();
			imguitimer.reset_stat();
		}
	}
	ImGui::End();
}


int main(int, char const * const *, char const * const *)
{
	globaltimer = COUT_TIMER("main game loop");
	rendertimer = COUT_TIMER("rendering     ");
	imguitimer  = COUT_TIMER("imgui         ");

	sf::RenderWindow window;

	window.create(sf::VideoMode(1900, 900), "project_x");
	window.setFramerateLimit(60);

	ImGui::SFML::Init(window);

	COUT_INFO << "Main loop start";

	while (window.isOpen()) {

		logg::ScopeTimer st(globaltimer);

		{
			logg::ScopeTimer st(imguitimer);

			for (sf::Event sfevent; window.pollEvent(sfevent); ) {
				ImGui::SFML::ProcessEvent(sfevent);
				if (sfevent.type == sf::Event::Closed)
					window.close();
			}

			ImGui::SFML::Update(window, sf::milliseconds(160));


			debug_timer_ctrl();
			clock_ctrl();

		}

		ImGui::ShowDemoWindow();

		window.clear(sf::Color::Black);

		{
			logg::ScopeTimer st(imguitimer);
		 	ImGui::SFML::Render(window);				
		}

		window.display();

	}

	COUT_INFO << "Main loop end";

	ImGui::SFML::Shutdown();
	window.close();

	return (0);
}