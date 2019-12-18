#ifndef UI_CAMERA_HH
#define UI_CAMERA_HH


#include <SFML/Graphics.hpp>


namespace ui
{


class Camera
{
public:
	Camera()               = default;
	Camera(Camera const &) = default;
	Camera(Camera &&)      = default;
	~Camera()              = default;

	Camera & operator=(Camera const &) = default;
	Camera & operator=(Camera &&)      = default;

	Camera(sf::RenderWindow const &);

	sf::View const & get_view() const;
	void set_view(sf::View const &);

	sf::Vector2u const & get_win_size() const;
	void set_win_size(sf::Vector2u const &);
	void set_win_size(unsigned int x, unsigned int y);

	double get_pixel_in_meter() const;
	void set_pixel_in_meter(double);

	sf::Vector2f const & get_center() const;
	void set_center(sf::Vector2f const &);
	void set_center(float x, float y);

	sf::Vector2f const & get_size() const;
	void set_size(sf::Vector2f const &);
	void set_size(float x, float y);

	void zoom_by(double);

private:
	sf::View _view;
	sf::Vector2u _win_size;
	double _pixel_in_meter;
};


} // ui

void display(ui::Camera & camera);

#endif // UI_CAMERA_HH
