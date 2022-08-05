#ifndef PARSER_HH__HEADER_GUARD__
#define PARSER_HH__HEADER_GUARD__

#include <vector>   // std::vector
#include <iostream> // std::cout
#include <memory>   // std::shared_ptr

#include "error.hh"
#include "token.hh"
#include "node.hh"

class Parser {
public:
	std::shared_ptr<Node> Parse(const std::vector<Token> &p_toks);

	void Dump(); // debug

private:
	bool AtEnd();
	bool AtStatementEnd();

	std::shared_ptr<Node> ParseFactor();
	std::shared_ptr<Node> ParsePower();
	std::shared_ptr<Node> ParseTerm();
	std::shared_ptr<Node> ParseExpression();

	void NextToken();

	bool TokenIsOperator(const Token &p_tok);
	bool TokenIsParen(const Token &p_tok);

	std::vector<Token> m_toks;
	std::vector<Token>::const_iterator m_it;

	std::shared_ptr<Node> m_node;
};

#endif
