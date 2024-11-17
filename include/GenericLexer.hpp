#pragma once
#include <AcidLib/Containers/Map.hpp>
#include <AcidLib/Containers/ArrayList.hpp>
#include <AcidLib/Containers/Stack.hpp>
#include <ValueError.hpp>
#include <GenericToken.hpp>

using namespace ac;

class LexerAction {
public:

	enum ActionType {

		Shift,
		Push,
		ShiftPush,
		Accept,
	};

	int newState;
	int pushedTokenType;
};

class LexerTable {
public:

	ArrayList<LexerAction> getActions(int state, String lookahead) const;

	void addActions(int state, String lookahead, LexerAction action);

	void registerTokenName(int tokenID, String tokenName);

	String getTokenName(int tokenID) const;

private:

	Map<int, Map<String, ArrayList<LexerAction>>> m_actionTable;

	Map<int, String> m_tokenNameTable;
};

class GenericLexer {
public:

	struct LexerFrame {
	public:

		int state;
		int index;
		int row;
		int col;
		String lexeme;
	};

	ArrayList<GenericToken> tokenize(String p_data);

private:

	int m_state;
	int m_index;
	int m_row;
	int m_col;

	String m_lexeme;

	String m_data;
	ArrayList<GenericToken> m_result;

	Stack<LexerFrame> m_frameStack;

	LexerTable m_ruleTable;
};

ArrayList<LexerAction> LexerTable::getActions(int state, String lookahead) const {

	if (lookahead.size() != 1) {

		if (lookahead != "EOI" && lookahead != "else") {

			throw ValueError("Lookahead can only be a single char, \"EOI\", or \"else\"");
		}
	}

	return m_actionTable[state][lookahead];
}

void LexerTable::addActions(int state, String lookahead, LexerAction action) {

	if (lookahead.size() > 1) {

		if (lookahead != "EOI" && lookahead != "else") {

			throw ValueError("Lookahead can only be a single char, \"EOI\", or \"else\"");
		}
	}

	if (!m_actionTable.keys().contains(state)) {

		m_actionTable.append(state, Map<String, ArrayList<LexerAction>>());
	}

	if (!m_actionTable[state].keys().contains(lookahead)) {

		m_actionTable[state].append(lookahead, ArrayList<LexerAction>());
	}

	m_actionTable[state][lookahead].append(action);
}

void LexerTable::registerTokenName(int tokenID, String tokenName) {

	m_tokenNameTable.append(tokenID, tokenName);
}

String LexerTable::getTokenName(int tokenID) const {

	return m_tokenNameTable[tokenID];
}