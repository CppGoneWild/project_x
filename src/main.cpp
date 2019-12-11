#include "logg.hh"

#include "ux/Calandar.hh"

#include "UniversalClock.hh"
#include "Colony.hh"

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
	Colony colony;

	colony.name() = "Alpha";
	colony.population() = 1000;
	colony.gross_colonial_product() = 10000;
	colony.population_growth() = 1.001;
	colony.gross_colonial_product_growth() = 1.001;

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

			colony.update(UniversalClock::last_tic(), UniversalClock::now());

			if (ImGui::Begin("Colony")) {
				ImGui::BulletText("name : %s", colony.name().c_str());

				ImGui::SetNextWindowContentSize(ImVec2(0, 200));
				ImGui::PlotHistogram("pop. distrib", colony._population_distrib.data(), colony._population_distrib.size(),
					0, NULL, FLT_MAX, FLT_MAX, ImVec2(0, 600), sizeof(float));
				ImGui::BulletText("sum %f", sum(colony._population_distrib));
				//ImGui::BulletText("median %f", median(colony._population_distrib));
				ImGui::BulletText("mean %f", mean(colony._population_distrib));
				ImGui::BulletText("geometric_mean %f", geometric_mean(colony._population_distrib));


				ImGui::DragInt("population", &colony.population());

				ImGui::DragInt("population", &colony.population());
				ImGui::DragFloat("population growth", &colony.population_growth());
				ImGui::DragInt("gcd", &colony.gross_colonial_product());
				ImGui::DragFloat("gcd growth", &colony.gross_colonial_product_growth());
			}
			ImGui::End();

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