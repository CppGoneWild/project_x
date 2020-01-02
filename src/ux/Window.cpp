#include "Window.hh"


ux::Window::~Window()
{}

bool ux::Window::open() const
{
	return (_open);
}

void ux::Window::open(bool b)
{
	_open = b;
}




ux::WindowMngr::~WindowMngr()
{
	for (auto it = _windows.begin(); it != _windows.end(); ++it)
		delete *it;
}

ux::WindowMngr::container_t const & ux::WindowMngr::windows() const
{
	return (_windows);
}

ux::WindowMngr::container_t & ux::WindowMngr::windows()
{
	return (_windows);
}

void ux::WindowMngr::display()
{
	for (auto it = _windows.begin(); it != _windows.end(); ++it)
		(*it)->display();
}

