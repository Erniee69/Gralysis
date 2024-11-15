#pragma once
#include <AcidLib/String/String.hpp>
#include <AcidLib/Containers/ArrayList.hpp>
#include <AcidLib/Containers/Map.hpp>

using namespace ac;

class GenericToken {
public:

	int row;
	int col;

	int tokenID;

	String lexeme;
};

class GenericTokenStream {
public:

	int registerTokenType(String p_typename);

	int getTokenTypeID(String p_typename);

	String getTokenTypename(int p_tokenID);
	String getTokenTypename(const GenericToken& p_token);

	void addToken(GenericToken p_token);

	ArrayList<GenericToken>& getTokens();

private:

	ArrayList<GenericToken> m_tokens;

	ArrayList<String> m_tokenNameTable;
};


int GenericTokenStream::registerTokenType(String p_typename) {

	m_tokenNameTable.append(p_typename);

	return m_tokenNameTable.size() - 1;
}

int GenericTokenStream::getTokenTypeID(String p_typename) {

	for (int i = 0; i < m_tokenNameTable.size(); i++) {

		if (m_tokenNameTable[i] == p_typename) {

			return i;
		}
	}

	return -1;
}

String GenericTokenStream::getTokenTypename(int p_tokenID) {

	return m_tokenNameTable[p_tokenID];
}

String GenericTokenStream::getTokenTypename(const GenericToken& p_token) {

	return m_tokenNameTable[p_token.tokenID];
}

void GenericTokenStream::addToken(GenericToken p_token) {

	m_tokens.append(p_token);
}

ArrayList<GenericToken>& GenericTokenStream::getTokens() {

	return m_tokens;
}