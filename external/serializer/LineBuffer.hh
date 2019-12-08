#ifndef SERIALIZER_LINEBUFFER_H__
#define SERIALIZER_LINEBUFFER_H__


#include "Tree.hh"

#include <string>
#include <istream>


namespace serializer
{


class LineBuffer
{
public:
	LineBuffer() = delete;
	LineBuffer(LineBuffer const &) = delete;
	LineBuffer(LineBuffer &&);
	LineBuffer(std::istream &, std::string const & = "");
	~LineBuffer();

	std::istream & stream();

	operator bool() const;

	int get();
	LineBuffer & get(char &);
	void ignore(char);

	Location const & location() const;

private:
	std::string _buffer;
	std::size_t _counter;
	Location _location;
	std::istream & _in;
};


} // serializer


#endif // SERIALIZER_LINEBUFFER_H__
