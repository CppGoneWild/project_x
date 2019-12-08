#include "Parser.hh"

#include "Tokenizer.hh"

#include <cstdlib> // strtol atof
#include <iostream>


static int get_base(char c)
{
	if (c == 'b' || c == 'B')
		return (2);
	else if (c == 'o' || c == 'O')
		return (8);
	else if (c == 'x' || c == 'X')
		return (16);
	return (0);
}

static serializer::I_Leaf * make_leaf(serializer::Tokenizer::Result::Type type, std::string const & s, serializer::Location const loc)
{
	if (type == serializer::Tokenizer::Result::Type::Number) {
		if (s.find('.') != std::string::npos) {
			return (new serializer::Number(std::atof(s.c_str()), loc));
		}
		else if (s.size() > 2 && s[0] == '0') {
			int base = get_base(s[1]);
			if (base)
				return (new serializer::Number((double)(strtol(s.c_str() + 2, NULL, base)), loc));
		}
		return (new serializer::Number(std::atof(s.c_str()), loc));
	}
	else if (type == serializer::Tokenizer::Result::Type::String || type == serializer::Tokenizer::Result::Type::Raw_String)
		return (new serializer::Litteral(s, loc));
	COUT_ERROR << "parsing error at " << loc << ":\t\"" << s << "\" field ill formed.";
	return (nullptr);
}

static bool find_token(serializer::Tokenizer & in, char c)
{
	serializer::Tokenizer::Result res = in.getNext();
	if (res.status != serializer::Tokenizer::Result::Error::OK || res.type != serializer::Tokenizer::Result::Type::Token
	    || res.value[0] != c)
		return (false);
	return (true);
}

static bool parse(serializer::Tokenizer & in, std::vector<serializer::I_Node*> & node, bool need_end = false);

static bool parse(serializer::Tokenizer & in, serializer::Object & obj)
{
	serializer::Tokenizer::Result res = in.getNext();

	if (res.status != serializer::Tokenizer::Result::Error::OK)
		return (false);


	obj.identifier = make_leaf(res.type, res.value, res.location);
	if (!obj.identifier)
		return (false);

	if (find_token(in, ')') && find_token(in, '{'))
		return (parse(in, obj.childs, true));

	return (false);
}

static bool parse(serializer::Tokenizer & in, std::vector<serializer::I_Node*> & node, bool need_end)
{
	serializer::Tokenizer::Result res;
	for (res = in.getNext();
	     res.status == serializer::Tokenizer::Result::Error::OK;
	     res = in.getNext())
	{

		if (res.type == serializer::Tokenizer::Result::Type::Token) {
			if (res.value == "}") {
				if (!need_end)
					COUT_ERROR << "parsing error at " << res.location << ":\t '}' encounter without '{'.";
				return (need_end);
			} 
			else if (res.value == "(") {
				serializer::Object * object = new serializer::Object(res.location);
				if (!parse(in, *object)) {
					COUT_ERROR << "parsing error at " << res.location << ":\t Object ill formed.";
					return (false);
				}
				node.push_back(object);
			}			
			else if (res.value == "{") {
				serializer::Node * tmp = new serializer::Node(res.location);
				if (!parse(in, tmp->childs, true)) {
					COUT_ERROR << "parsing error at " << res.location << ":\t Node ill formed.";
					return (false);
				}
				node.push_back(tmp);
			}
			/// @todo 'point virgule' are ignored for now.
			/// @bug 'point virgule' are ignored for now.
			else if (res.value == ";")
				continue ; // useless before operation or other.
			else {
				COUT_ERROR << "parsing error at " << res.location << ". '" << res.value << "' encountered.";
				return (false);
			}

		} // -end token
		else if (res.type == serializer::Tokenizer::Result::Type::Number ||
		         res.type == serializer::Tokenizer::Result::Type::String ||
		         res.type == serializer::Tokenizer::Result::Type::Raw_String)
			node.push_back(make_leaf(res.type, res.value, res.location));
	}

	if (res.status == serializer::Tokenizer::Result::Error::Eof) {
		if (need_end)
			COUT_ERROR << "parsing error\t: EOF encounter without '}'.";
		return (!need_end);
	}

	COUT_ERROR << "parsing error at " << res.location << ":\t Error unknow." << res.value.size() << " " << (int)res.value[0];
	return (false);
}


serializer::I_Node * serializer::unserialize(std::istream & stream, std::string const & filename)
{
	serializer::LineBuffer lfs(stream, filename);
	serializer::Tokenizer in(lfs);
	std::vector<I_Node*> tmp;

	if (::parse(in, tmp)) {
		if (tmp.size() > 1) {
			Node * node = new Node;
			node->childs = std::move(tmp);
			return (node);
		}
		else if (tmp.size() == 1)
			return (tmp.back());
	}

	return nullptr;	
}
