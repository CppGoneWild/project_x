#ifndef SERIALIZER_TOKENIZER_H__
#define SERIALIZER_TOKENIZER_H__


#include "LineBuffer.hh"


namespace serializer
{


class Tokenizer
{
public:
	struct Result
	{
		enum class Error {
			OK = 0,
			Eof,
			BadFormat,
			BadFormat_comment_block,
		};

		enum class Type {
			None = 0,
			Number,
			String,
			Raw_String,
			Token
		};

		Result() : Result(serializer::Location(), Error::OK, Type::None, "") {}
		Result(serializer::Location loc) : Result(loc, Error::OK, Type::None, "") {}
		Result(serializer::Location loc, Error e, Type t = Type::None, std::string s = "") : location(loc), status(e), type(t), value(s) {}
		Result(serializer::Location loc, Type t, std::string s = "") : Result(loc, Error::OK, t, s) {}
		~Result() = default;

		Result(Result const & other) : Result(other.location, other.status, other.type, other.value) {} 
		Result(Result && other) : location(std::move(other.location)), status(other.status), type(other.type), value(std::move(other.value)) {}

		Result & operator=(Result const & other)
		{
			if (this != &other) {
				location = other.location;
				status = other.status;
				type = other.type;
				value = other.value;
			}
			return (*this);
		}

		Result & operator=(Result && other)
		{
			location = std::move(other.location);
			status = other.status;
			type = other.type;
			value = std::move(other.value);
			return (*this);
		}


		serializer::Location location;
		Error status;
		Type type;
		std::string value;
	};


	Tokenizer() = delete;
	Tokenizer(Tokenizer const &) = delete;
	Tokenizer(Tokenizer &&) = delete;
	Tokenizer & operator=(Tokenizer const &) = delete;
	Tokenizer & operator=(Tokenizer &&) = delete;

	Tokenizer(serializer::LineBuffer & in);

	~Tokenizer();

	Result getNext();

private:
	bool is_triple_quote();
	bool get_raw(std::string &);
	bool skip_comment_block();
	bool get_identifier(std::string &);
	bool get_number(std::string &);

	char c;
	serializer::LineBuffer & in;
};

	
} //serializer


#endif // SERIALIZER_TOKENIZER_H__
