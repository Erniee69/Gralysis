#pragma once
#include <AcidLib/Containers/ArrayList.hpp>
#include <AcidLib/Containers/Stack.hpp>
#include <Lexer/CharacterValidator.hpp>
#include <Lexer/LexerAction.hpp>
#include <Lexer/LexerTable.hpp>
#include <Lexer/Token.hpp>
#include <Utilities/LogicError.hpp>

class Lexer {
public:

	struct LexerFrame {

		int state;

		char current;

		int index;
		int row;
		int col;

		String lexeme;

		int resultSize;
	};

	Lexer();

	ArrayList<Token> tokenize(String p_data);

	void runAction(LexerAction action);

	void shift(int newState);
	void push(int pushedTokenType);

	LexerFrame captureFrame() const;

	void restoreFrame(LexerFrame p_frame);

	void setTransitionTable(LexerTable p_table);

	LexerTable& getTransitionTable();

	const LexerTable& getTransitionTable() const;

private:

	bool finished;
	bool accepted;

	int m_state;

	char m_current;

	int m_index;
	int m_row;
	int m_col;

	String m_lexeme;

	String m_data;

	ArrayList<Token> m_result;

	Stack<LexerFrame> m_frameStack;

	LexerTable m_transitionTable;

	void resetLexer();
};

Lexer::Lexer() {

	resetLexer();
}

ArrayList<Token> Lexer::tokenize(String p_data) {

	if (!m_transitionTable.hasStartState()) {

		throw LogicError("Can't run a lexer without a start state (state number 0).");
	}

	resetLexer();

	m_data = p_data;

	m_current = (m_data.size() != 0) ? m_data[0] : '\0';

	while (!finished) {

		ArrayList<LexerAction> actions = m_transitionTable.getActions(m_state, m_current);

		if (actions.size() == 0) {

			if (m_frameStack.size() == 0) {

				finished = true;
				accepted = false;
			}
			else {

				restoreFrame(m_frameStack.pop());
			}
		}
		else if (actions.size() == 1) {

			runAction(actions[0]);
		}
		else {

			LexerFrame currentFrame = captureFrame();

			for (int i = actions.size() - 1; i > 0; i--) {

				runAction(actions[i]);

				m_frameStack.push(captureFrame());

				restoreFrame(currentFrame);
			}

			runAction(actions[0]);
		}
	}

	for (int i = m_result.size() - 1; i >= 0; i--) {

		if (m_result[i].tokenID == 0) {

			m_result.remove(i);
		}
	}

	return m_result;
}

void Lexer::runAction(LexerAction action) {

	if (action.type == LexerAction::Shift) {

		shift(action.getNewState());
	}
	else if (action.type == LexerAction::Push) {

		push(action.getPushedTokenType());
	}
	else if (action.type == LexerAction::ShiftAndPush) {

		shift(0);
		push(action.getPushedTokenType());
	}
	else if (action.type == LexerAction::Accept) {

		finished = true;
		accepted = true;
	}
	else {

		throw LogicError("Lexer encountered explicit error action!");
	}
}

void Lexer::shift(int newState) {
	
	if (m_current != '\0') {

		m_lexeme += m_current;
		m_index++;

		m_col++;

		if (m_index < m_data.size()) {

			m_current = m_data[m_index];
		}
		else {

			m_current = '\0';
		}

		if (m_current == '\n') {

			m_row++;
			m_col = 1;
		}

		m_state = newState;
	}
	else {

		throw LogicError("Can't advance behind end of input!");
	}
}

void Lexer::push(int pushedTokenType) {

	Token token;

	token.row = m_row;
	token.col = m_col;

	token.lexeme = m_lexeme;
	token.tokenID = pushedTokenType;

	m_result.append(token);

	m_state = 0;
	m_lexeme.clear();
}

Lexer::LexerFrame Lexer::captureFrame() const {

	LexerFrame result;

	result.state = m_state;

	result.current = m_current;

	result.index = m_index;
	result.row = m_row;
	result.col = m_col;

	result.lexeme = m_lexeme;

	result.resultSize = m_result.size();

	return result;
}

void Lexer::restoreFrame(LexerFrame p_frame) {

	m_state = p_frame.state;

	m_current = p_frame.current;

	m_index = p_frame.index;
	m_row = p_frame.row;
	m_col = p_frame.col;

	m_lexeme = p_frame.lexeme;

	m_result.resize(p_frame.resultSize);
}

void Lexer::setTransitionTable(LexerTable p_table) {

	m_transitionTable = p_table;
}

LexerTable& Lexer::getTransitionTable() {

	return m_transitionTable;
}

const LexerTable& Lexer::getTransitionTable() const {

	return m_transitionTable;
}

void Lexer::resetLexer() {

	finished = false;
	accepted = false;

	m_state = 0;

	m_current = '\0';

	m_index = 0;
	m_row = 1;
	m_col = 1;

	m_data = "";

	m_lexeme = "";

	m_result.clear();
	m_frameStack.clear();
}