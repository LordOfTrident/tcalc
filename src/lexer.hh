#ifndef LEXER_HH__HEADER_GUARD__
#define LEXER_HH__HEADER_GUARD__

#include <iostream>  // std::cout, std::endl
#include <string>    // std::string
#include <vector>    // std::vector
#include <cassert>   // assert
#include <cctype>    // std::isdigit, std::isspace, std::isalpha
#include <stdexcept> // std::runtime_error

#include "token.hh"
#include "error.hh"

class Lexer {
public:
	Lexer();

	std::vector<Token> Lex(const std::string &p_file, const std::string &p_code);

	void Dump() const; // debug;

private:
	bool AtEnd();

	void LexNum();
	void LexSlash();
	void SkipComment();
	void SkipMultiLineComment();

	void NextCh();
	void PrevCh();

	void NextLine();

	void PushToken();
	void PushToken(std::string p_str, TokenType p_type);

	const std::string *m_code;
	std::string::const_iterator m_it;

	Token    m_tok;
	Location m_loc;

	std::vector<Token> m_toks;
};

#endif
