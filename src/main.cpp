#include "logg.hh"

#include "time.hh"
#include "kepler.hh"

#include "ux/Calandar.hh"
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


void draw_system(sf::RenderWindow & window, kepler::OrbitalBody const & o)
{
	auto position = o.stellar_position(UniversalClock::now());
	sf::CircleShape body(o.radius().count());
	body.setOrigin(- o.radius().count() / 2, - o.radius().count() / 2);
	//body.setPosition(position.count().x, position.count().y);
	body.setFillColor(sf::Color::White);


	//for (auto it = o.system().cbegin(); it != o.system().cend(); it++)
	//	draw_system(window, *it);

	if (o.is_satellite()) {
		sf::CircleShape orbit(o.orbit().radius().count());

		orbit.setOrigin(- o.orbit().radius().count() / 2, - o.orbit().radius().count() / 2);
		orbit.setFillColor(sf::Color::Transparent);
		orbit.setOutlineColor(sf::Color::Blue);
		auto around = o.satellite_of().stellar_position(UniversalClock::now());
		orbit.setPosition(around.count().x, around.count().y);
		window.draw(orbit);
	}

	window.draw(body);
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

	kepler::OrbitalBody sun(kepler::Orbit(), si::kilo_meters(695510 * 1000));

	kepler::OrbitalBody & mercury = sun.add(kepler::OrbitalBody(kepler::Orbit(si::astronomical_units(0.4), si::days(87)),    si::kilo_meters(4880)));
	kepler::OrbitalBody & venus   = sun.add(kepler::OrbitalBody(kepler::Orbit(si::astronomical_units(0.7), si::days(224)),   si::kilo_meters(6051)));
	kepler::OrbitalBody & earth   = sun.add(kepler::OrbitalBody(kepler::Orbit(si::astronomical_units(1.0), si::days(360)),   si::kilo_meters(6371)));
	kepler::OrbitalBody & mars    = sun.add(kepler::OrbitalBody(kepler::Orbit(si::astronomical_units(1.5), si::days(686)),   si::kilo_meters(3389)));
	kepler::OrbitalBody & jupiter = sun.add(kepler::OrbitalBody(kepler::Orbit(si::astronomical_units(5.2), si::days(4332)),  si::kilo_meters(69911)));
	kepler::OrbitalBody & saturn  = sun.add(kepler::OrbitalBody(kepler::Orbit(si::astronomical_units(9.3), si::days(10759)), si::kilo_meters(58232)));
	kepler::OrbitalBody & uranus  = sun.add(kepler::OrbitalBody(kepler::Orbit(si::astronomical_units(19),  si::days(30688)), si::kilo_meters(25362)));
	kepler::OrbitalBody & neptune = sun.add(kepler::OrbitalBody(kepler::Orbit(si::astronomical_units(30),  si::days(60182)), si::kilo_meters(24622)));

	kepler::OrbitalBody & moon = earth.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(400000), si::days(28)), si::kilo_meters(1737)));

	kepler::OrbitalBody & phobos = mars.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(9377),  si::hours(7.66)),  si::kilo_meters(22.2)));
	kepler::OrbitalBody & deimos = mars.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(23460), si::hours(30.55)), si::kilo_meters(12.6)));

	kepler::OrbitalBody & io       = jupiter.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(421700),  si::days(1.7)), si::kilo_meters(3660)));
	kepler::OrbitalBody & europa   = jupiter.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(671034),  si::days(3.5)), si::kilo_meters(3121)));
	kepler::OrbitalBody & ganymede = jupiter.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(1070412), si::days(7.1)), si::kilo_meters(5262)));
	kepler::OrbitalBody & callisto = jupiter.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(1882709), si::days(16)),  si::kilo_meters(4820)));

	kepler::OrbitalBody & mimas     = saturn.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(185539),  si::days(0.9)), si::kilo_meters(396)));
	kepler::OrbitalBody & enceladus = saturn.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(237948),  si::days(1.4)), si::kilo_meters(504)));
	kepler::OrbitalBody & tethys    = saturn.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(294619),  si::days(1.9)), si::kilo_meters(1062)));
	kepler::OrbitalBody & dione     = saturn.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(377396),  si::days(2.7)), si::kilo_meters(1123)));
	kepler::OrbitalBody & rhea      = saturn.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(527108),  si::days(4.5)), si::kilo_meters(1527)));
	kepler::OrbitalBody & titan     = saturn.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(1221870), si::days(16)),  si::kilo_meters(5149)));
	kepler::OrbitalBody & lapetus   = saturn.add(kepler::OrbitalBody(kepler::Orbit(si::kilo_meters(3560820), si::days(79)),  si::kilo_meters(1470)));



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


		draw_system(window, sun);

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
