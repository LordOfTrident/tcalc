#include "node.hh"

Node::Node(NodeType p_type):
	type(p_type),
	data(static_cast<std::uint64_t>(0))
{}

Node::Node(const Token &p_tok, const NodeChildren &p_children):
	tok(p_tok),
	children(p_children)
{
	switch (tok.type) {
	case TokenType::Num:
		type = NodeType::Num;
		data = std::stod(tok.data);

		break;

	case TokenType::LParen:
	case TokenType::RParen:
		type = NodeType::UnaryOp;
		data = 0;

		break;

	case TokenType::Add:
	case TokenType::Sub:
	case TokenType::Div:
	case TokenType::Mult:
	case TokenType::Mod:
	case TokenType::Pow:
		type = NodeType::BinOp;
		data = 0;

		break;

	default: assert(0 and "If this shows, it is an internal bug, please report it");
	}
}

Node::Node(const Token &p_tok, NodeType p_type, const NodeChildren &p_children):
	tok(p_tok),
	type(p_type),
	children(p_children)
{
	switch (type) {
	case NodeType::Num: data = std::stod(tok.data); break;

	default: data = 0;
	}
}

std::string Node::TypeToStr() const {
	switch (type) {
	case NodeType::BinOp:   return "binary operator";
	case NodeType::UnaryOp: return "unary operator";
	case NodeType::Num:     return "number";

	default: assert(0 and "If this shows, it is an internal bug, please report it");
	}
}

std::ostream &operator <<(std::ostream &p_stream, const Node &p_node) {
	p_stream << '[';

	if (p_node.type == NodeType::BinOp or p_node.type == NodeType::UnaryOp)
		p_stream << p_node.tok.data;
	else
		p_stream << p_node.TypeToStr() << ": " << p_node.tok.data;

	for (const auto &node : p_node.children)
		p_stream << ", " << *node;

	p_stream << ']';

	return p_stream;
}
