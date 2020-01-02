#ifndef UX_WINDOW_HH
#define UX_WINDOW_HH




#include <list>




namespace ux
{




class Window
{
public:
	virtual ~Window();

	bool open() const;
	void open(bool b);

	virtual void display() = 0;

protected:
	Window()               = default;
	Window(Window const &) = default;
	Window(Window &&)      = default;

	Window & operator=(Window const &) = default;
	Window & operator=(Window &&)      = default;

	bool _open = false;
};


class WindowMngr
{
public:
	using container_t = std::list<Window *>;

	WindowMngr() = default;
	~WindowMngr();

	container_t const & windows() const;
	container_t & windows();

	void display();

private:
	WindowMngr(WindowMngr const &) = delete;
	WindowMngr(WindowMngr &&)      = delete;
	WindowMngr & operator=(WindowMngr const &) = delete;
	WindowMngr & operator=(WindowMngr &&)      = delete;

	container_t _windows;
};



} // ux




#endif // UX_WINDOW_HH
