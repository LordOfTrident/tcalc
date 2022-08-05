#include "parser.hh"

std::shared_ptr<Node> Parser::Parse(const std::vector<Token> &p_toks) {
	if (p_toks.empty())
		return nullptr;

	m_toks = p_toks;
	m_it   = m_toks.begin();

	m_node = std::make_shared<Node>(NodeType::Statements);

	while (not AtEnd()) {
		std::shared_ptr<Node> node = ParseExpression();

		m_node->children.push_back(node);

		NextToken();
	}

	return m_node;
}

void Parser::Dump() {
	if (m_node != nullptr)
		std::cout << *m_node << std::endl;
}

bool Parser::AtEnd() {
	return m_it->type == TokenType::EndOfFile or m_it >= m_toks.end();
}

bool Parser::AtStatementEnd() {
	if (not AtEnd())
		return m_it->type == TokenType::StatementEnd;
	else
		return true;
}

std::shared_ptr<Node> Parser::ParseFactor() {
	if (AtEnd())
		Error::Throw(m_it->loc, "A number expected, got end of file");
	else if (AtStatementEnd())
		Error::Throw(m_it->loc, "A number expected, got statemend end");

	const Token &tok = *m_it;

	if (m_it->type == TokenType::LParen) {
		NextToken();

		std::shared_ptr<Node> expr = ParseExpression();
		if (AtStatementEnd() or m_it->type != TokenType::RParen) {
			try {
				if (AtEnd())
					Error::Throw(m_it->loc, "Matching ')' expected, got end of file");
				else
					Error::Throw(m_it->loc, "Matching ')' expected, got " + m_it->TypeToStr());
			} catch (const CompilerError &p_err) {
				Error::Note(tok.loc, "Opened here");

				throw p_err;
			}
		}

		NextToken();

		return expr;
	} else if (m_it->type == TokenType::Sub or m_it->type == TokenType::Add) {
		NextToken();

		return std::make_shared<Node>(tok, NodeType::UnaryOp, NodeChildren{ParseFactor()});
	} else if (m_it->type == TokenType::Num) {
		NextToken();

		return std::make_shared<Node>(tok);
	} else {
		Error::Throw(m_it->loc, "A number expected, got " + m_it->TypeToStr());

		return std::shared_ptr<Node>(nullptr);
	}
}

std::shared_ptr<Node> Parser::ParsePower() {
	std::shared_ptr<Node> left = ParseFactor();

	if (AtStatementEnd())
		return left;

	if (not TokenIsOperator(*m_it) and not TokenIsParen(*m_it))
		Error::Throw(m_it->loc, "Expected an operator, got " + m_it->TypeToStr());

	while (m_it->type == TokenType::Pow) {
		const Token &op = *m_it;
		NextToken();

		std::shared_ptr<Node> right = ParsePower();

		left = std::make_shared<Node>(op, NodeChildren{left, right});

		if (AtStatementEnd())
			break;
	}

	return left;
}

std::shared_ptr<Node> Parser::ParseTerm() {
	std::shared_ptr<Node> left = ParsePower();

	if (AtStatementEnd())
		return left;

	while (m_it->type == TokenType::Mult or m_it->type == TokenType::Div or
	       m_it->type == TokenType::Mod) {
		const Token &op = *m_it;
		NextToken();

		std::shared_ptr<Node> right = ParsePower();

		left = std::make_shared<Node>(op, NodeChildren{left, right});

		if (AtStatementEnd())
			break;
	}

	return left;
}

std::shared_ptr<Node> Parser::ParseExpression() {
	std::shared_ptr<Node> left = ParseTerm();

	if (AtStatementEnd())
		return left;

	while (m_it->type == TokenType::Add or m_it->type == TokenType::Sub) {
		const Token &op = *m_it;
		NextToken();

		std::shared_ptr<Node> right = ParseTerm();

		left = std::make_shared<Node>(op, NodeChildren{left, right});

		if (AtStatementEnd())
			break;
	}

	return left;
}

void Parser::NextToken() {
	++ m_it;
}

bool Parser::TokenIsOperator(const Token &p_tok) {
	switch (p_tok.type) {
	case TokenType::Add:
	case TokenType::Sub:
	case TokenType::Div:
	case TokenType::Mult:
	case TokenType::Mod:
	case TokenType::Pow: return true;

	default: return false;
	}
}

bool Parser::TokenIsParen(const Token &p_tok) {
	switch (p_tok.type) {
	case TokenType::LParen:
	case TokenType::RParen: return true;

	default: return false;
	}
}
