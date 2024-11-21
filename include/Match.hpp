#pragma once
#include <CharacterClass.hpp>
#include <ValueError.hpp>

class Match {
public:

	enum MatchType {

		Character,
		CharClass,
		EndOfInput,
		Fallback,
	};

	MatchType type;

	Match(char p_character);
	Match(CharacterClass p_charClass);
	Match(MatchType p_type);

	~Match();

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

Match::Match(char p_character) {

	type = Match::Character;
	character = p_character;
}

Match::Match(CharacterClass p_charClass) {

	type = Match::CharClass;
	charClass = p_charClass;
}

Match::Match(MatchType p_type) {

	if (p_type == Match::Character) {

		throw ValueError("Can't initialize character match without character!");
	}
	else if (p_type == Match::CharClass) {

		throw ValueError("Can't initialize character class match without character class!");
	}
	else {

		type = p_type;
	}
}

Match::~Match() {

	if (type == Match::CharClass) {

		charClass.~CharacterClass();
	}
}

bool Match::operator==(char other) const {

	if (type == Match::Character) {

		return character == other;
	}
	else if (type == Match::CharClass) {

		return charClass.check(other);
	}
	else if (type == Match::EndOfInput) {

		return other == '\0';
	}
	else {

		return true;
	}
}

bool Match::operator!=(char other) const {

	return !(*this == other);
}

char Match::getChar() const {

	if (type != Match::Character) {

		throw ValueError("Can't get character of a non character match!");
	}
	else {

		return character;
	}
}

CharacterClass Match::getCharClass() const {

	if (type != Match::CharClass) {

		throw ValueError("Can't get character class of a non character class match!");
	}
}