#ifndef CALANDAR_HH
#define CALANDAR_HH


#include <string>


namespace ux
{


class Calandar
{
public:
	Calandar()  = default;
	~Calandar() = default;

	void display();

private:
	Calandar(Calandar const &)             = delete;
	Calandar(Calandar &&)                  = delete;

	Calandar & operator=(Calandar const &) = delete;
	Calandar & operator=(Calandar &&)      = delete;

	static constexpr std::size_t _size_buffer_strftime = 128;
	char _buffer_strftime[_size_buffer_strftime] = {0};
	int _time_incr = 1;
	std::string _imgui_win_title;
};


} // ux


#endif // CALANDAR_HH
