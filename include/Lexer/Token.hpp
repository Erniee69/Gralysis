#pragma once
#include <AcidLib/String/String.hpp>

using namespace ac;

class Token {
public:

	int tokenID;

	int row;
	int col;

	String lexeme;

	Token();

	Token(int p_tokenID, String p_lexeme, int p_row, int p_col);
};

Token::Token() {

	tokenID = -1;

	row = 0;
	col = 0;

	lexeme = "";
}

Token::Token(int p_tokenID, String p_lexeme, int p_row, int p_col) {

	tokenID = p_tokenID;

	lexeme = p_lexeme;

	row = p_row;
	col = p_col;
}