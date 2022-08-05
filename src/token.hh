#ifndef TOKEN_HH__HEADER_GUARD__
#define TOKEN_HH__HEADER_GUARD__

#include <string>  // std::string
#include <ostream> // std::ostream
#include <cassert> // assert

#include "location.hh"

enum class TokenType {
	EndOfFile = 0,
	StatementEnd,

	Num,

	LParen,
	RParen,

	Add,
	Sub,
	Div,
	Mult,
	Mod,
	Pow
};

struct Token {
	Token();
	Token(TokenType p_type, const std::string &p_data, const Location &p_loc);

	std::string TypeToStr() const;

	friend std::ostream &operator <<(std::ostream &p_stream, const Token &p_token); // debug

	TokenType   type;
	std::string data;
	Location    loc;
};

#endif
