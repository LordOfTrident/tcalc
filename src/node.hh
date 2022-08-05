#ifndef NODE_HH__HEADER_GUARD__
#define NODE_HH__HEADER_GUARD__

#include <string>  // std::string
#include <ostream> // std::ostream
#include <cstdint> // std::uint64_t
#include <cassert> // assert
#include <memory>  // std::shared_ptr

#include "location.hh"
#include "token.hh"

enum class NodeType {
	Statements = 0,
	BinOp,
	UnaryOp,
	Num
};

class Node;
using NodeChildren = std::vector<std::shared_ptr<Node>>;

struct Node {
	Node(NodeType p_type);
	Node(const Token &p_tok, const NodeChildren &p_children = {});
	Node(const Token &p_tok, NodeType p_type, const NodeChildren &p_children = {});

	std::string TypeToStr() const;

	friend std::ostream &operator <<(std::ostream &p_stream, const Node &p_node); // debug

	Token    tok;
	NodeType type;
	double   data;

	NodeChildren children;
};

#endif
