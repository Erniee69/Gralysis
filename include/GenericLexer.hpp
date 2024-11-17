#pragma once
#include <AcidLib/Containers/Map.hpp>
#include <AcidLib/Containers/ArrayList.hpp>
#include <AcidLib/Containers/Stack.hpp>
#include <ValueError.hpp>
#include <LogicError.hpp>
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

	ActionType type;

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
		int tokenCount;

		String current;
		String lexeme;
	};

	ArrayList<GenericToken> tokenize(String p_data);

	void shift(int newState);
	void push(int tokenType);

	void runAction(LexerAction action);

	void reloadFrame(LexerFrame frame);
	LexerFrame snapshot();

	void setRuleTable(LexerTable table);

private:

	int m_state;
	int m_index;
	int m_row;
	int m_col;

	bool finished;
	bool accepted;

	String m_current;
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

	try {
		return m_actionTable[state][lookahead];
	}
	catch (KeyNotFoundException) {

		return ArrayList<LexerAction>();
	}
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

ArrayList<GenericToken> GenericLexer::tokenize(String p_data) {

	m_state = 0;
	m_index = 0;
	m_row = 1;
	m_col = 1;

	finished = false;
	accepted = false;

	m_data = p_data;
	shift(0);

	while (!finished) {

		ArrayList<LexerAction> actions = m_ruleTable.getActions(m_state, m_current);

		if (actions.size() == 0) {

			if (m_frameStack.size() == 0) {

				finished = true;
				accepted = false;
				break;
			}
			else {

				LexerFrame newFrame = m_frameStack.pop();

				reloadFrame(newFrame);
			}
		}
		else if (actions.size() == 1) {

			LexerAction action = actions[0];

			runAction(action);
		}
		else {

			LexerFrame current = snapshot();

			for (int i = actions.size() - 1; i >= 1; i--) {

				LexerAction action = actions[i];

				runAction(action);

				m_frameStack.push(snapshot());
				reloadFrame(current);
			}

			LexerAction action = actions[0];
			runAction(action);
		}
	}
}

void GenericLexer::shift(int newState) {

	if (m_current == "EOI") {

		throw LogicError("Cannot advance over End of Input!");
	}

	m_state = newState;

	m_lexeme += m_current;
	m_index++;

	if (m_index == m_data.size()) {

		m_current = "EOI";
	}
	else {

		m_current = m_data[m_index];

		if (m_current == "\n") {

			m_row++;
			m_col = 1;
		}
		else {

			m_col++;
		}
	}
}

void GenericLexer::push(int tokenType) {

	GenericToken token(m_ruleTable);

	token.lexeme = m_lexeme;
	token.row = m_row;
	token.col = m_col;
	token.tokenID = tokenType;

	m_result.append(token);

	m_lexeme.clear();
}

void GenericLexer::runAction(LexerAction action) {

	if (action.type == LexerAction::Shift) {

		shift(action.newState);
	}
	else if (action.type == LexerAction::Push) {

		push(action.pushedTokenType);
	}
	else if (action.type == LexerAction::ShiftPush) {

		shift(0);
		push(action.pushedTokenType);
	}
	else if (action.type == LexerAction::Accept) {

		finished = true;
		accepted = true;
	}
}

void GenericLexer::reloadFrame(LexerFrame frame) {

	m_result.resize(frame.tokenCount);

	m_state = frame.state;
	m_index = frame.index;
	m_row = frame.row;
	m_col = frame.col;

	m_current = frame.current;
	m_lexeme = frame.lexeme;
}

GenericLexer::LexerFrame GenericLexer::snapshot() {

	LexerFrame result;

	result.col = m_col;
	result.row = m_row;
	result.index = m_index;
	result.lexeme = m_lexeme;
	result.state = m_state;
	result.tokenCount = m_result.size();

	return result;
}

void GenericLexer::setRuleTable(LexerTable table) {

	m_ruleTable = table;
}