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

private:

	LexerTable& m_lexerTable;
};