#include "LineBuffer.hh"


serializer::LineBuffer::LineBuffer(LineBuffer && other)
	: _buffer(std::move(other._buffer)), _counter(other._counter),
	  _location(std::move(other._location)), _in(other._in)
{}

serializer::LineBuffer::LineBuffer(std::istream & s, std::string const & str)
	: _buffer(), _counter(), _location(), _in(s)
{
	_location.filename = str;
}

serializer::LineBuffer::~LineBuffer()
{}

std::istream & serializer::LineBuffer::stream()
{
	return (_in);
}

serializer::LineBuffer::operator bool() const
{
	return (_counter < _buffer.size() || _in);
}

static std::size_t get_next_line(std::istream & in, std::string & str)
{
	std::size_t line = 0;

	str.clear();
	while (in && str.empty()) {
		std::getline(in, str, '\n');
		line++;
	}
	return (line);
}

int serializer::LineBuffer::get()
{
	if (_counter >= _buffer.size()) {
		_location.line += get_next_line(_in, _buffer);
		_location.column = 0;
		_counter = 0;
	}
	if (_counter < _buffer.size()) {
		_location.column++;
		return (_buffer[_counter++]);
	}
	return (-1);
}

serializer::LineBuffer & serializer::LineBuffer::get(char & c)
{
	c = get();
	return (*this);
}

void serializer::LineBuffer::ignore(char delim)
{
	if (delim == '\n') {
		_location.line += get_next_line(_in, _buffer);
		_location.column = 0;
		_counter = 0;
	}
	else {
		for (char c = get(); (*this); c = get()) {
			_location.column++;
			if (c == delim)
				break ;
		}
	}
}

serializer::Location const & serializer::LineBuffer::location() const
{
	return (_location);
}
