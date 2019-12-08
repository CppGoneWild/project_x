#ifndef SERIALIZER_TREE_H__
#define SERIALIZER_TREE_H__


#include "logg.hh"
#include "logg/Entry.hh"

#include <string>
#include <vector>


namespace serializer
{


struct Location
{
	Location() = default;
	Location(Location const &) = default;
	Location(Location && other) : filename(std::move(other.filename)), line(other.line), column(other.column) {}
	~Location() = default;

	Location & operator=(Location const & other);
	Location & operator=(Location && other);

	std::string filename = "";
	std::size_t line = 0;
	std::size_t column = 0;
};

/// @todo refactor all this shit.
struct I_Node
{
	virtual ~I_Node() {}

	virtual bool is_leaf() const = 0;
	virtual bool is_node() const = 0;
	virtual bool is_object() const = 0;

	Location location;
protected:
	I_Node(Location const loc) : location(loc) {}
};

struct I_Leaf : public I_Node
{
	virtual ~I_Leaf() {}

	virtual bool is_litteral() const = 0;
	virtual bool is_number() const = 0;

protected:
	I_Leaf(Location const loc) : I_Node(loc) {}
};

struct Litteral : public I_Leaf
{
	Litteral() : Litteral(std::string(), Location()) {}
	Litteral(std::string const & s) : Litteral(s, Location()) {}
	Litteral(Location const loc) : Litteral(std::string(),loc) {}
	Litteral(std::string const & s, Location const loc) : I_Leaf(loc), value(s) {}
	virtual ~Litteral() {}


	virtual bool is_leaf() const { return (true); }
	virtual bool is_node() const { return (false); }
	virtual bool is_object() const { return (false); }

	virtual bool is_litteral() const { return (true); };
	virtual bool is_number() const { return (false); };

	std::string value;
};

struct Number : public I_Leaf
{
	Number() : Number(0, Location()) {}
	Number(double d) : Number(d, Location()) {}
	Number(Location const loc) : Number(0, loc) {}
	Number(double d, Location const loc) : I_Leaf(loc), value(d) {}
	virtual ~Number() {}


	virtual bool is_leaf() const { return (true); }
	virtual bool is_node() const { return (false); }
	virtual bool is_object() const { return (false); }

	virtual bool is_litteral() const { return (false); };
	virtual bool is_number() const { return (true); };

	double value;
};

struct Node : public I_Node
{
	Node() : Node(Location()) {}
	Node(Location const loc) : I_Node(loc) {}
	virtual ~Node()
	{
		for (auto it = childs.begin(); it != childs.end(); it++)
			delete *it;
	}

	virtual bool is_leaf() const { return (false); }
	virtual bool is_node() const { return (true); }
	virtual bool is_object() const { return (false); }

	std::vector<I_Node *> childs;
};

struct Object : public Node
{
	Object() : Object(Location()) {}
	Object(Location const loc) : Node(loc), identifier(nullptr) {}
	virtual ~Object() { delete identifier; }

	virtual bool is_leaf() const { return (false); }
	virtual bool is_node() const { return (true); }
	virtual bool is_object() const { return (true); }

	I_Leaf * identifier;
};


inline bool get_string(I_Node const * n, std::string & s)
{
	if (!n || !n->is_leaf() ||
	    !static_cast<I_Leaf const *>(n)->is_litteral())
		return (false);
	s = static_cast<Litteral const *>(n)->value;
	return (true);
}

template <class T>
inline bool get_number(I_Node const * n, T & s)
{
	if (!n || !n->is_leaf() ||
	    !static_cast<I_Leaf const *>(n)->is_number())
		return (false);
	s = (T)(static_cast<Number const *>(n)->value);
	return (true);
}

inline bool get_identifier(I_Node const * n, I_Leaf const ** l)
{
	if (!n || !n->is_object())
		return (false);
	*l = static_cast<Object const *>(n)->identifier;
	return (true);
}

inline bool get_identifier_as_string(I_Node const * n, std::string & s)
{
	I_Leaf const * l;
	return (get_identifier(n, &l) && get_string(l, s));
}

template <class T>
inline bool get_identifier_as_number(I_Node const * n, T & s)
{
	I_Leaf const * l;
	return (get_identifier(n, &l) && get_number<T>(l, s));
}

inline bool get_childs(I_Node const * n, std::vector<I_Node *> const ** l)
{
	if (!n || !n->is_node())
		return (false);
	*l = &(static_cast<Node const *>(n)->childs);
	return (true);
}



inline Number * make_node(double value)
{
	return (new Number(value));
}

inline Litteral * make_node(std::string const & value)
{
	return (new Litteral(value));
}


inline Object * make_node(std::string const & identifier, Node & node)
{
	Object * tmp = new Object;

	tmp->identifier = make_node(identifier);
	tmp->childs = std::move(node.childs);
	return (tmp);
}

inline Object * make_node(std::string const & identifier, std::vector<I_Node *> && nodes)
{
	Object * tmp = new Object;

	tmp->identifier = make_node(identifier);
	tmp->childs = std::move(nodes);
	return (tmp);
}

template <class UUID>
inline Object * make_node(UUID identifier, Node & node)
{
	Object * tmp = new Object;

	tmp->identifier = make_node(static_cast<double>(identifier.id()));
	tmp->childs = std::move(node.childs);
	return (tmp);
}

template <class UUID>
inline Object * make_node(UUID identifier, std::vector<I_Node *> && nodes)
{
	Object * tmp = new Object;

	tmp->identifier = make_node(static_cast<double>(identifier.id()));
	tmp->childs = std::move(nodes);
	return (tmp);
}


} // serializer


inline logg::Entry operator<<(logg::Entry e, serializer::Location const & loc)
{
	std::string tmp;

	tmp += loc.filename;
	tmp += '(';
	tmp += std::to_string(loc.line);
	tmp += ',';
	tmp += std::to_string(loc.column);
	tmp += ')';

	e.append(tmp);

	return (e);
}


#endif // SERIALIZER_TREE_H__
