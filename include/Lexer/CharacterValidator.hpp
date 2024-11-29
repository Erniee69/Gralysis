#pragma once
#include <Utilities/CharacterClass.hpp>
#include <Utilities/ValueError.hpp>

class CharacterValidator {
public:

	enum ValidatorType {

		Character,
		CharClass,
		EndOfInput,
		Fallback,
	};

	ValidatorType type;

	CharacterValidator(char p_character);
	CharacterValidator(CharacterClass p_charClass);
	CharacterValidator(ValidatorType p_type);

	~CharacterValidator();

	char getChar() const;

	CharacterClass getCharClass() const;

	virtual bool isValid(char target) const;

private:
	
	union {

		char character;
		CharacterClass charClass;
	};
};

CharacterValidator::CharacterValidator(char p_character) {

	type = ValidatorType::Character;
	character = p_character;
}

CharacterValidator::CharacterValidator(CharacterClass p_charClass) {

	type = ValidatorType::CharClass;
	charClass = p_charClass;
}

CharacterValidator::CharacterValidator(ValidatorType p_type) {

	if (p_type == ValidatorType::Character) {

		throw ValueError("Can't initialize character validator without character!");
	}
	else if (p_type == ValidatorType::CharClass) {

		throw ValueError("Can't initialize character class validator without character class!");
	}
	else {

		type = p_type;
	}
}

CharacterValidator::~CharacterValidator() {

	if (type == ValidatorType::CharClass) {

		charClass.~CharacterClass();
	}
}

char CharacterValidator::getChar() const {

	if (type != ValidatorType::Character) {

		throw ValueError("Can't get character of a non character match!");
	}
	else {

		return character;
	}
}

CharacterClass CharacterValidator::getCharClass() const {

	if (type != ValidatorType::CharClass) {

		throw ValueError("Can't get character class of a non character class match!");
	}
}

bool CharacterValidator::isValid(char target) const {

	if (type == ValidatorType::Character) {

		return character == target;
	}
	else if (type == ValidatorType::CharClass) {

		return charClass.check(target);
	}
	else if (type == ValidatorType::EndOfInput) {

		return target == '\0';
	}
	else {

		return true;
	}
}