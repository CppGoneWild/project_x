#include "logg.hh"

#include "time.hh"
#include "kepler.hh"

#include "ux/Calandar.hh"
#include "ui/Camera.hh"


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
	// init log timer
	globaltimer = COUT_TIMER("main game loop");
	rendertimer = COUT_TIMER("rendering     ");
	imguitimer  = COUT_TIMER("imgui         ");


	// sfml
	sf::RenderWindow window;
	window.create(sf::VideoMode(1900, 900), "project_x");
	window.setFramerateLimit(60);

	ui::Camera camera(window);
	camera.set_center(0, 0);
	camera.set_pixel_in_meter(328311616);


	// imgui
	ImGui::SFML::Init(window);


	// ux
	ux::Calandar calandar;


	Scheduler scheduler;
	Timer every_week(UniversalClock::days(7), UniversalClock::now());
	Timer every_month(UniversalClock::months(1), UniversalClock::now());
	scheduler.add(every_week);
	scheduler.add(every_month);
	scheduler.sort();


	COUT_INFO << "Main loop start";


	// main loop
	while (window.isOpen()) {

		logg::ScopeTimer st(globaltimer);

		{
			logg::ScopeTimer st(imguitimer);

			// event loop
			for (sf::Event sfevent; window.pollEvent(sfevent); ) {
				ImGui::SFML::ProcessEvent(sfevent);
				if (sfevent.type == sf::Event::Closed)
					window.close();
			}
			ImGui::SFML::Update(window, sf::milliseconds(160));


			debug_timer_ctrl();
			calandar.display(scheduler);
			display(camera);
		}

		ImGui::ShowDemoWindow();



		// render sfml
		window.setView(camera.get_view());
		window.clear(sf::Color::Black);


		// render imgui
		{
			logg::ScopeTimer st(imguitimer);
		 	ImGui::SFML::Render(window);				
		}


		// push to screen
		window.display();

	}

	COUT_INFO << "Main loop end";


	// clean imgui and sfml
	ImGui::SFML::Shutdown();
	window.close();

	return (0);
}
