#include "File.hh"

#include "Tree.hh"
#include "Parser.hh"

#include <fstream>


serializer::File::~File()
{
	delete _node;
}

serializer::File::File(File && oth)
: _node(oth._node), _name(std::move(oth._name))
{
	oth._node = nullptr;
}

serializer::File & serializer::File::operator=(File && oth)
{
	if (this != &oth) {
		_node = oth._node;
		oth._node = nullptr;
		_name = std::move(oth._name);
	}
	return (*this);
}

serializer::File::File(std::string name)
: _node(nullptr), _name(std::move(name))
{}

serializer::File::File(I_Node & node, std::string name)
: _node(&node), _name(name)
{}

serializer::I_Node const * serializer::File::node() const
{
	return (_node);
}

void serializer::File::node(I_Node * n)
{
	delete _node;
	_node = n;
}

std::string const & serializer::File::name() const
{
	return (_name);
}

std::string & serializer::File::name()
{
	return (_name);
}

void serializer::File::write()
{}

void serializer::File::read()
{
	delete _node;
	std::ifstream in(_name, std::ios_base::in);
	_node = serializer::unserialize(in, _name);
}

void serializer::File::read(std::string const & file)
{
	_name = file;
	read();
}

