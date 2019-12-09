#include "logg.hh"

#include "ux/Calandar.hh"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>


logg::Timer globaltimer;
logg::Timer rendertimer;
logg::Timer imguitimer;





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
	ux::Calandar calandar;

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
			calandar.display();
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