#include "token.hh"

Token::Token():
	type(TokenType::StatementEnd)
{}

Token::Token(TokenType p_type, const std::string &p_data, const Location &p_loc):
	type(p_type),
	data(p_data),
	loc(p_loc)
{}

std::string Token::TypeToStr() const {
	switch (type) {
	case TokenType::EndOfFile:    return "end of file";
	case TokenType::StatementEnd: return "statement end";

	case TokenType::Num: return "number";

	case TokenType::LParen: return "(";
	case TokenType::RParen: return ")";

	case TokenType::Add:  return "+";
	case TokenType::Sub:  return "-";
	case TokenType::Div:  return "/";
	case TokenType::Mult: return "*";
	case TokenType::Mod:  return "%";
	case TokenType::Pow:  return "^";

	default: assert(0 and "If this shows, it is an internal bug, please report it");
	}
}

std::ostream &operator <<(std::ostream &p_stream, const Token &p_token) {
	p_stream << '[' << p_token.TypeToStr() << ": " << p_token.data <<  ']';

	return p_stream;
}
