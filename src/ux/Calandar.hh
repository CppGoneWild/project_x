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

	static constexpr std::size_t size_buffer_strftime = 128;
	char buffer_strftime[size_buffer_strftime] = {0};
	int time_incr = 1;
	std::string imgui_win_title;
};


} // ux


#endif // CALANDAR_HH
