#pragma once
#include <CharacterClass.hpp>
#include <ValueError.hpp>

class LexingMatch {
public:

	enum LexingMatchType {

		Character,
		CharClass,
		EndOfInput,
		Fallback,
	};

	LexingMatchType type;

	LexingMatch(char p_character);
	LexingMatch(CharacterClass p_charClass);
	LexingMatch(LexingMatchType p_type);

	~LexingMatch();

	bool operator==(char other) const;
	bool operator!=(char other) const;

	char getChar() const;

	CharacterClass getCharClass() const;

private:
	
	union {

		char character;
		CharacterClass charClass;
	};
};

LexingMatch::LexingMatch(char p_character) {

	type = LexingMatch::Character;
	character = p_character;
}

LexingMatch::LexingMatch(CharacterClass p_charClass) {

	type = LexingMatch::CharClass;
	charClass = p_charClass;
}

LexingMatch::LexingMatch(LexingMatchType p_type) {

	if (p_type == LexingMatch::Character) {

		throw ValueError("Can't initialize character match without character!");
	}
	else if (p_type == LexingMatch::CharClass) {

		throw ValueError("Can't initialize character class match without character class!");
	}
	else {

		type = p_type;
	}
}

LexingMatch::~LexingMatch() {

	if (type == LexingMatch::CharClass) {

		charClass.~CharacterClass();
	}
}

bool LexingMatch::operator==(char other) const {

	if (type == LexingMatch::Character) {

		return character == other;
	}
	else if (type == LexingMatch::CharClass) {

		return charClass.check(other);
	}
	else if (type == LexingMatch::EndOfInput) {

		return other == '\0';
	}
	else {

		return true;
	}
}

bool LexingMatch::operator!=(char other) const {

	return !(*this == other);
}

char LexingMatch::getChar() const {

	if (type != LexingMatch::Character) {

		throw ValueError("Can't get character of a non character match!");
	}
	else {

		return character;
	}
}

CharacterClass LexingMatch::getCharClass() const {

	if (type != LexingMatch::CharClass) {

		throw ValueError("Can't get character class of a non character class match!");
	}
}