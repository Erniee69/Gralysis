#pragma once
#include <AcidLib/String/String.hpp>
#include <AcidLib/Containers/ArrayList.hpp>
#include <AcidLib/Containers/Map.hpp>

using namespace ac;

class LexerTable;

class GenericToken {
public:

	int row;
	int col;

	int tokenID;

	String lexeme;

	GenericToken(LexerTable* p_lexerTable);

	String getName();

private:

	LexerTable* m_lexerTable;
};

GenericToken::GenericToken(LexerTable* p_lexerTable) : m_lexerTable(p_lexerTable) {

	row = 0;
	col = 0;

	tokenID = -1;
}

String GenericToken::getName() {

	return m_lexerTable->getTokenName(tokenID);
}