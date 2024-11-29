#pragma once
#include <Utilities/ValueError.hpp>

class LexerAction {
public:

	enum LexerActionType {

		Shift,
		Push,
		ShiftAndPush,
		Accept,
		Error,
	};

	LexerActionType type;

	LexerAction(LexerActionType p_type);
	LexerAction(LexerActionType p_type, int intVal);

	int getNewState() const;
	int getPushedTokenType() const;

private:

	union {

		int newState;
		int pushedTokenType;
	};
};

LexerAction::LexerAction(LexerActionType p_type) {

	if (p_type == LexerActionType::Shift) {

		throw ValueError("Can't initialize a shift action without a state to shift to!");
	}
	else if (p_type == LexerActionType::Push) {

		throw ValueError("Can't initialize a push action without a token type to push!");
	}
	else if (p_type == LexerActionType::ShiftAndPush) {

		throw ValueError("Can't initialize a shift and push action without a token type to push!");
	}
	else {

		type = p_type;
		pushedTokenType = 0;
	}
}

LexerAction::LexerAction(LexerActionType p_type, int intVal) {

	type = p_type;

	if (type == LexerActionType::Shift) {

		newState = intVal;
	}
	else {

		pushedTokenType = intVal;
	}
}

int LexerAction::getNewState() const {

	if (type != LexerActionType::Shift) {

		throw ValueError("Can't get new state from non shift action!");
	}
	
	return newState;
}

int LexerAction::getPushedTokenType() const {

	if (type != LexerActionType::Push && type != LexerActionType::ShiftAndPush) {

		throw ValueError("Can't get pushed token type from non push or non shift and push action!");
	}

	return pushedTokenType;
}