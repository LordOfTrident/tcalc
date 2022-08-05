#include <iostream> // std::cerr, std::endl
#include <cstdlib>  // EXIT_FAILURE
#include <memory>   // std::shared_ptr

#include "utils.hh"
#include "error.hh"
#include "lexer.hh"
#include "parser.hh"
#include "eval.hh"

int main(/*int p_argc, const char **p_argv*/) {
	Lexer     lexer;
	Parser    parser;
	Evaluator eval;

	std::cout << "A calculator, type in 'exit' or press ^C to quit." << std::endl;

	bool running = true;
	while (running) {
		std::string input;

		std::cout << "> ";
		std::getline(std::cin, input, '\n');

		if (input == "exit")
			running = false;
		else {
			try {
				eval.Eval(parser.Parse(lexer.Lex("", input)));
			} catch (const CompilerError &p_err) {}
		}
	}

	return 0;
}
