#pragma once
#include <ValueError.hpp>

class LexingAction {
public:

	enum LexingActionType {

		Shift,
		Push,
		ShiftAndPush,
		Accept,
		Error,
	};

	LexingActionType type;

	LexingAction(LexingActionType p_type);
	LexingAction(LexingActionType p_type, int intVal);

	int getNewState() const;
	int getPushedTokenType() const;

private:

	union {

		int newState;
		int pushedTokenType;
	};
};

LexingAction::LexingAction(LexingActionType p_type) {

	if (p_type == LexingActionType::Shift) {

		throw ValueError("Can't initialize a shift action without a state to shift to!");
	}
	else if (p_type == LexingActionType::Push) {

		throw ValueError("Can't initialize a push action without a token type to push!");
	}
	else if (p_type == LexingActionType::ShiftAndPush) {

		throw ValueError("Can't initialize a shift and push action without a token type to push!");
	}
	else {

		type = p_type;
		pushedTokenType = 0;
	}
}

LexingAction::LexingAction(LexingActionType p_type, int intVal) {

	type = p_type;

	if (type == LexingActionType::Shift) {

		newState = intVal;
	}
	else {

		pushedTokenType = intVal;
	}
}

int LexingAction::getNewState() const {

	if (type != LexingActionType::Shift) {

		throw ValueError("Can't get new state from non shift action!");
	}
	
	return newState;
}

int LexingAction::getPushedTokenType() const {

	if (type != LexingActionType::Push && type != LexingActionType::ShiftAndPush) {

		throw ValueError("Can't get pushed token type from non push or non shift and push action!");
	}

	return pushedTokenType;
}