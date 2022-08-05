#include "lexer.hh"

Lexer::Lexer() {}

std::vector<Token> Lexer::Lex(const std::string &p_file, const std::string &p_code) {
	m_toks.clear();

	m_tok  = Token();
	m_loc  = Location();
	m_code = &p_code;

	m_loc.file = p_file;
	m_loc.line = m_code->substr(0, m_code->find_first_of('\n'));

	for (m_it = m_code->begin(); not AtEnd(); NextCh()) {
		switch (*m_it) {
		case '\n': NextLine(); break;
		case ';':
			if (not m_toks.empty()) {
				if (m_toks.back().type != TokenType::StatementEnd)
					PushToken(";", TokenType::StatementEnd);
			}

			break;

		case '(': PushToken("(", TokenType::LParen); break;
		case ')': PushToken(")", TokenType::RParen); break;

		case '+': PushToken("+", TokenType::Add);  break;
		case '-': PushToken("-", TokenType::Sub);  break;
		case '*': PushToken("*", TokenType::Mult); break;
		case '%': PushToken("%", TokenType::Mod);  break;
		case '^': PushToken("^", TokenType::Pow);  break;

		case '/': LexSlash(); break;

		case '#': SkipComment(); break;

		default:
			if (std::isspace(*m_it))
				break;

			if (std::isdigit(*m_it) or *m_it == '.')
				LexNum();
			else
				Error::Throw(m_loc, (std::string)"Unexpected character '" + *m_it + "'");
		}
	}

	++ m_tok.loc.col;
	m_tok.data.clear();
	m_tok.type = TokenType::EndOfFile;
	PushToken();

	return m_toks;
}

void Lexer::Dump() const {
	for (const auto &token : m_toks)
		std::cout << token;

	if (not m_toks.empty())
		std::cout << std::endl;
}

bool Lexer::AtEnd() {
	return *m_it == '\0' or m_it >= m_code->end();
}

void Lexer::LexNum() {
	m_tok.loc   = m_loc;
	m_tok.type  = TokenType::Num;
	bool hasDot = false;

	for (;; NextCh()) {
		switch (*m_it) {
		case '.':
			if (hasDot)
				Error::Throw(m_loc, "Got '.' in a number more than once");

			hasDot      = true;
			m_tok.data += *m_it;

			break;

		case '\n': NextLine();
			// fall through
		default:
			if (not std::isdigit(*m_it)) {
				if (std::isalpha(*m_it) or *m_it == '_')
					Error::Throw(m_loc, (std::string)"Unexpected character '" +
					             *m_it + "' in a number");

				if (m_tok.data == ".")
					Error::Throw(m_tok.loc, "Unexpected character '.'");

				PushToken();

				if (not std::isspace(*m_it))
					PrevCh();

				return;
			} else
				m_tok.data += *m_it;
		}
	}
}

void Lexer::LexSlash() {
	m_tok.loc        = m_loc;
	m_tok.loc.strLen = 2;

	NextCh();

	switch (*m_it) {
	case '*': SkipMultiLineComment(); break;

	default:
		PrevCh();
		PushToken("/", TokenType::Div);
	}
}

void Lexer::SkipComment() {
	NextCh();

	while (not AtEnd()) {
		if (*m_it == '\n') {
			NextLine();

			break;
		}

		NextCh();
	}
}

void Lexer::SkipMultiLineComment() {
	Location commentStartLoc = m_tok.loc;

	NextCh();

	bool lastChWasStar = false;

	while (not AtEnd()) {
		if (lastChWasStar) {
			if (*m_it == '/')
				return;
			else
				lastChWasStar = false;
		}

		switch (*m_it) {
		case '\n': NextLine(); break;
		case '*':  lastChWasStar = true; break;

		default: break;
		}

		NextCh();
	}

	try {
		Error::Throw(m_loc, "Matching '*/' expected, got EOF");
	} catch (const CompilerError &p_err) {
		Error::Note(commentStartLoc, "Opened here");

		throw p_err;
	}
}

void Lexer::NextCh() {
	++ m_it;
	++ m_loc.col;
}

void Lexer::PrevCh() {
	-- m_it;
	-- m_loc.col;
}

void Lexer::NextLine() {
	++ m_loc.row;
	m_loc.col = 0;

	std::size_t i = m_it - m_code->begin() + 1, idx = m_code->find_first_of('\n', i);
	m_loc.line    = m_code->substr(i, idx - i);

	if (not m_toks.empty()) {
		if (m_toks.back().type != TokenType::StatementEnd)
			PushToken(";", TokenType::StatementEnd);
	}
}

void Lexer::PushToken() {
	m_tok.loc.strLen = m_tok.data.length();

	m_toks.push_back(m_tok);

	m_tok.data.clear();
}

void Lexer::PushToken(std::string p_str, TokenType p_type) {
	m_tok.type = p_type;
	m_tok.data = p_str;
	m_tok.loc  = m_loc;
	m_tok.loc.strLen = m_tok.data.length();

	m_toks.push_back(m_tok);

	m_tok.data.clear();
}
