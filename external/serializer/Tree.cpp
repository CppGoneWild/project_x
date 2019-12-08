#include "Tree.hh"


serializer::Location & serializer::Location::operator=(Location const & other)
{
	if (this != &other) {
		filename = other.filename;
		line = other.line;
		column = other.column;			
	}
	return (*this);		
}

serializer::Location & serializer::Location::operator=(Location && other)
{
	filename = std::move(other.filename);
	line = other.line;
	column = other.column;
	return (*this);
}


