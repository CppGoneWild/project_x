#ifndef TOOLS_SERiALIZER_FILE_HH__
#define TOOLS_SERiALIZER_FILE_HH__


#include <string>


namespace serializer {
	struct I_Node;
} // serializer


namespace serializer
{



class File
{
public:
	File()  = default;
	~File();
	
	File(File &&);
	File & operator=(File &&);

	File(std::string _name);
	File(I_Node & _node, std::string _name);

	I_Node const * node() const;
	void node(I_Node *);

	std::string const & name() const;
	std::string & name();

	void write();
	void read();
	void read(std::string const &);

private:
	File(File const &) = delete;
	File & operator=(File const &) = delete;

	I_Node * _node = nullptr;
	std::string _name;
};



} // serializer



#endif // TOOLS_SERiALIZER_FILE_HH__
