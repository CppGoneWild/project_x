#include "logg.hh"

#include "ux/Calandar.hh"

#include "time.hh"

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


	// imgui
	ImGui::SFML::Init(window);


	// ux
	ux::Calandar calandar;


	//Timer every_day(UniversalClock::days(1), UniversalClock::now());
	Timer every_week(UniversalClock::days(7), UniversalClock::now());
	Timer every_month(UniversalClock::months(1), UniversalClock::now());
	Timer single_shot(UniversalClock::now() + UniversalClock::duration(100000));
	Scheduler scheduler;
	//scheduler.add(every_day);
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


			// update logic
			//colony.update(UniversalClock::last_tic(), UniversalClock::now());


/*			// update imgui
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
*/
			debug_timer_ctrl();
			calandar.display(scheduler);

			if (ImGui::Begin("timer")) {
				//ImGui::ProgressBar(every_day.progress(UniversalClock::now()));
				ImGui::ProgressBar(every_week.progress(UniversalClock::now()));
				ImGui::ProgressBar(every_month.progress(UniversalClock::now()));
				ImGui::ProgressBar(single_shot.progress(UniversalClock::now()));
			}
			ImGui::End();
		}

		ImGui::ShowDemoWindow();



		// render sfml
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