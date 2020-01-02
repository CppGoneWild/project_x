#include "logg.hh"

#include "time.hh"

#include "hubble.hh"

#include "ux/Calandar.hh"
#include "ux/Window.hh"

#include "ui/Camera.hh"


#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include <unistd.h>



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

void _display(hubble::System const & system)
{
	auto display_celestial = [](auto const & c)
	{
		if (ImGui::TreeNode(c.name().c_str())){
			if (c.type().main == hubble::Type::M_Type::Staroid) {
				std::string tmp;
				tmp += std::get<hubble::Type::Star>(c.type().second).spectral.data();
				tmp += std::get<hubble::Type::Star>(c.type().second).sspectral.data();
				tmp += std::get<hubble::Type::Star>(c.type().second).yerkes.data();
				ImGui::BulletText("%s", tmp.c_str());
			}
			else
				ImGui::BulletText(std::get<hubble::Type::Planet>(c.type().second) == hubble::Type::Planet::Ground ? "ground" : "gaz");
			ImGui::TreePop();
		}
	};

	display_celestial(system.main_body());
	for (auto it = system.bodies().cbegin(); it != system.bodies().cend(); it++)
		display_celestial(*it);
}

void display(hubble::System const & system)
{
	if (ImGui::Begin(system.name().c_str())) {
		_display(system);
	}
	ImGui::End();
}


void display(hubble::Galaxy const & g)
{
	if (ImGui::Begin("Galaxy")) {
		for (auto it = g.systems().cbegin(); it != g.systems().cend(); it++)
		if (ImGui::TreeNode(it->name().c_str())){
			_display(*it);
			ImGui::TreePop();
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


	Scheduler scheduler;
	Timer every_week(UniversalClock::days(7), UniversalClock::now());
	Timer every_month(UniversalClock::months(1), UniversalClock::now());
	scheduler.add(every_week);
	scheduler.add(every_month);
	scheduler.sort();


	hubble::System sol = hubble::make_sol_system();
	hubble::Galaxy via_lactea = hubble::make_via_lactea();

	// ux
	ux::WindowMngr win_mngr;

	win_mngr.windows().emplace_back(new ux::Calandar(scheduler));


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

			win_mngr.display();

			display(camera);
			display(sol);
			display(via_lactea);
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
		usleep(60);
	}

	COUT_INFO << "Main loop end";


	// clean imgui and sfml
	ImGui::SFML::Shutdown();
	window.close();

	return (0);
}
