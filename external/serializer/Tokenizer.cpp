#include "Tokenizer.hh"


static bool is_alpha(char c)             { return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); }
static bool is_digit(char c)             { return ((c >= '0' && c <= '9') || c == '-' || c == '+'); }
static bool is_decimal_separator(char c) { return (c == '.' || c == ','); }
static bool is_alphanum(char c)          { return (is_alpha(c) || is_digit(c)); }
static bool is_blank(char c)             { return (c == ' ' || c == '\t' || c == '\n'); }


serializer::Tokenizer::Tokenizer(serializer::LineBuffer & in)
	: c(), in(in)
{
	in.get(c);
}

serializer::Tokenizer::~Tokenizer()
{}

serializer::Tokenizer::Result serializer::Tokenizer::getNext()
{
	serializer::Tokenizer::Result res;

	while (is_blank(c)) {
		if (!in || c == -1)
			return (Result(in.location(), Result::Error::Eof));
		in.get(c);
	}

	if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';') {
		Result res(in.location(), Result::Type::Token, std::string(1, c));

		if (in)
			in.get(c);
		return (res);
	}

	if (c == '"') {
		if (is_triple_quote()) {
			std::string raw;
			if (get_raw(raw))
				return (Result(in.location(), Result::Type::Raw_String, raw));
		}
		return (Result(in.location(), Result::Error::BadFormat, Result::Type::Raw_String));
	}

	if (c == '/') {
		if (!in)
			return (Result(in.location(), Result::Type::Token, std::string(1, '/')));

		in.get(c);

		if (c == '*') {
			if (!skip_comment_block())
				return (Result(in.location(), Result::Error::BadFormat_comment_block));
		}
		else if (c == '/') {
			in.ignore('\n');
		}
		else {
			return (Result(in.location(), Result::Type::Token, std::string(1, '/')));
		}

		in.get(c);
		return (getNext());
	}

	if (is_alpha(c)) {
		std::string s;
		if (get_identifier(s))
				return (Result(in.location(), Result::Type::String, s));
		return (Result(in.location(), Result::Error::BadFormat, Result::Type::String));
	}

	if (is_digit(c) || is_decimal_separator(c)) {
		std::string s;
		if (get_number(s))
				return (Result(in.location(), Result::Type::Number, s));
		return (Result(in.location(), Result::Error::BadFormat, Result::Type::Number));
	}

	if (c == -1)
		return (Result(in.location(), Result::Error::Eof));

	return (Result(in.location(), Result::Error::BadFormat));
}

bool serializer::Tokenizer::is_triple_quote()
{
	if (in) {
		in.get(c);
		if (c == '"') {
			if (in) {
				in.get(c);
				if (c == '"')
					return (true);
			}
		}
	}
	return (false);
}

bool serializer::Tokenizer::get_raw(std::string & res)
{
	for (;;) {

		for (c = in.get(); c != '"' && in; c = in.get())
			res += c;
		if (!in)
			break;

		in.get(c);
		if (c == '"' && in) {
			in.get(c);
			if (c == '"'){
				if (in)
					in.get(c);
				return (true);
			}
			else
				res += '"';
			res += '"';
		}
		res += c;
	}
	return (false);
}

bool serializer::Tokenizer::skip_comment_block()
{
	do {
		in.ignore('*');
	} while (in && in.get() != '/');

	return (in);
}

bool serializer::Tokenizer::get_identifier(std::string & res)
{
	do {
		res += c;
		if (!in)
			break;
		in.get(c);
	} while (is_alphanum(c));
	return (true);
}

bool serializer::Tokenizer::get_number(std::string & res)
{
	res += c;
	bool dec_sep = is_decimal_separator(c);

	while (in) {
		in.get(c);

		if (is_decimal_separator(c)) {
			if (dec_sep)
				return (false);
			dec_sep = true;
		}
		else if (!is_alphanum(c))
			break;
		res += c;
	}
	return (true);
}

