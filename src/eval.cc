#include "eval.hh"

void Evaluator::Eval(const std::shared_ptr<Node> &p_node) {
	if (p_node == nullptr)
		return;

	for (const auto &node : p_node->children) {
		std::cout << EvalSingle(node) << std::endl;
	}
}

double Evaluator::EvalSingle(const std::shared_ptr<Node> &p_node) {
	switch (p_node->type) {
	case NodeType::BinOp:
		{
			double right = EvalSingle(p_node->children.at(0));
			double left  = EvalSingle(p_node->children.at(1));

			switch (p_node->tok.type) {
			case TokenType::Add:  return right + left;
			case TokenType::Sub:  return right - left;
			case TokenType::Mult: return right * left;
			case TokenType::Div:
				if (left == 0)
					Error::Throw(p_node->tok.loc, "Division by zero");

				return right / left;

			case TokenType::Mod:
				return static_cast<std::uint64_t>(right) % static_cast<std::uint64_t>(left);

			case TokenType::Pow: return std::pow(right, left);

			default: assert(0 and "If this shows, it is an internal bug, please report it");
			}
		}

	case NodeType::UnaryOp:
		{
			double num = EvalSingle(p_node->children.at(0));

			switch (p_node->tok.type) {
			case TokenType::Add: return  num;
			case TokenType::Sub: return -num;

			default: assert(0 and "If this shows, it is an internal bug, please report it");
			}
		}

	case NodeType::Num: return p_node->data; break;

	default: assert(0 and "If this shows, it is an internal bug, please report it");
	}
}
