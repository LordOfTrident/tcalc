#ifndef EVAL_HH__HEADER_GUARD__
#define EVAL_HH__HEADER_GUARD__

#include <iostream> // std::cout
#include <memory>   // std::shared_ptr
#include <cstdint>  // std::uint64_t
#include <cassert>  // assert
#include <cmath>    // std::pow

#include "error.hh"
#include "node.hh"

class Evaluator {
public:
	void Eval(const std::shared_ptr<Node> &p_node);

private:
	double EvalSingle(const std::shared_ptr<Node> &p_node);
};

#endif
