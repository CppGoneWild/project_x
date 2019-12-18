#include "logg.hh"

#include "ui/Camera.hh"

#include "imgui.h"



template <class T, class U>
static double _compute_scale(T world, U screen)
{
	return ((double)(world) / (double)(screen));
}

template <class T, class U>
static float _compute_size(T scale, U screen)
{
	return ((float)(scale) * (float)(screen));
}


ui::Camera::Camera(sf::RenderWindow const & w)
: _view(w.getView()),
  _win_size(w.getSize()),
  _pixel_in_meter(_compute_scale(_view.getSize().x, _win_size.x))
{}

sf::View const & ui::Camera::get_view() const
{
	return (_view);
}

void ui::Camera::set_view(sf::View const & v)
{
	_view = v;
	_pixel_in_meter = _compute_scale(_view.getSize().x, _win_size.x);
}

sf::Vector2u const & ui::Camera::get_win_size() const
{
	return (_win_size);
}

void ui::Camera::set_win_size(sf::Vector2u const & v)
{
	_win_size = v;
	_pixel_in_meter = _compute_scale(_view.getSize().x, _win_size.x);
}

void ui::Camera::set_win_size(unsigned int x, unsigned int y)
{
	set_win_size(sf::Vector2u(x, y));
}

double ui::Camera::get_pixel_in_meter() const
{
	return (_pixel_in_meter > 1 ? _pixel_in_meter : 1.0);
}

void ui::Camera::set_pixel_in_meter(double d)
{
	_pixel_in_meter = d;
	sf::Vector2f world_size(_compute_size(_pixel_in_meter, _win_size.x),
	                        _compute_size(_pixel_in_meter, _win_size.y));
	_view.setSize(world_size);
}

sf::Vector2f const & ui::Camera::get_center() const
{
	return (_view.getCenter());
}

void ui::Camera::set_center(sf::Vector2f const & v)
{
	_view.setCenter(v);
}

void ui::Camera::set_center(float x, float y)
{
	set_center(sf::Vector2f(x, y));
}

sf::Vector2f const & ui::Camera::get_size() const
{
	return (_view.getSize());
}

void ui::Camera::set_size(sf::Vector2f const & s)
{
	_pixel_in_meter = _compute_scale(s.x, _win_size.x);
	_view.setSize(s);
}

void ui::Camera::set_size(float x, float y)
{
	set_size(sf::Vector2f(x, y));
}

void ui::Camera::zoom_by(double coef)
{
	sf::Vector2f tmp((float)(_view.getSize().x * coef),
                     (float)(_view.getSize().y * coef));
	set_size(tmp);
}






void display(ui::Camera & camera)
{
	if (ImGui::Begin("Camera")) {
		if (ImGui::Button("Zoom In++"))
			camera.zoom_by(0.5);
		ImGui::SameLine();
		if (ImGui::Button("Zoom In"))
			camera.zoom_by(0.9);
		if (ImGui::Button("Zoom Out++"))
			camera.zoom_by(2);
		ImGui::SameLine();
		if (ImGui::Button("Zoom Out"))
			camera.zoom_by(1.1);
		ImGui::Value("scale (km/pxl)", (float)(camera.get_pixel_in_meter()) / 1000);		
		if (ImGui::Button("print scale"))
			COUT_USER << "Scale is " << camera.get_pixel_in_meter() << " meters by pixels.";
	}
	ImGui::End();
}
