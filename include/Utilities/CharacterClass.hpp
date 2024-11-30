#pragma once
#include <AcidLib/String/String.hpp>
#include <AcidLib/Containers/Pair.hpp>
#include <AcidLib/Containers/ArrayList.hpp>

using namespace ac;

class CharacterClass {
public:

	struct Rule {
	public:

		enum RuleType {

			SingleChar,
			CharRange,
		};

		RuleType type;

		Rule();
		Rule(char p_singleChar);
		Rule(char p_rangeStart, char p_rangeEnd);

		bool operator==(const Rule& other) const;
		bool operator!=(const Rule& other) const;

		bool check(char data) const;

	private:

		union {

			char singleChar;
			Pair<char, char> charRange;
		};
	};

	bool operator==(const CharacterClass& other) const;
	bool operator!=(const CharacterClass& other) const;

	void setNegated(bool p_negated);

	void addRule(Rule r);

	bool check(char data) const;

private:

	bool negated;

	ArrayList<Rule> m_rules;
};

CharacterClass::Rule::Rule() {

	type = Rule::SingleChar;
	singleChar = '\0';
}

CharacterClass::Rule::Rule(char p_singleChar) {

	type = Rule::SingleChar;

	singleChar = p_singleChar;
}

CharacterClass::Rule::Rule(char p_rangeStart, char p_rangeEnd) {

	type = Rule::CharRange;

	charRange.first = p_rangeStart;
	charRange.second = p_rangeEnd;
}

bool CharacterClass::Rule::operator==(const Rule& other) const {

	if (type != other.type) {

		return false;
	}

	if (type == Rule::SingleChar) {

		return singleChar == other.singleChar;
	}
	else {

		return (charRange.first == other.charRange.first) && (charRange.second == other.charRange.second);
	}
}
bool CharacterClass::Rule::operator!=(const Rule& other) const {

	return !(*this == other);
}

bool CharacterClass::Rule::check(char data) const {

	if (type == Rule::SingleChar) {

		return singleChar == data;
	}
	else {

		return (charRange.first <= data) && (data <= charRange.second);
	}
}

bool CharacterClass::operator==(const CharacterClass& other) const {

	if (m_rules.size() != other.m_rules.size()) {

		return false;
	}

	for (int i = 0; i < m_rules.size(); i++) {

		if (m_rules[i] != other.m_rules[i]) {

			return false;
		}
	}

	return true;
}

bool CharacterClass::operator!=(const CharacterClass& other) const {

	return !(*this == other);
}

void CharacterClass::setNegated(bool p_negated) {

	negated = p_negated;
}

void CharacterClass::addRule(Rule r) {

	m_rules.append(r);
}

bool CharacterClass::check(char data) const {

	bool result = true;

	for (Rule r : m_rules) {

		bool ruleResult = r.check(data);

		result = result && (negated ? !ruleResult : ruleResult);
	}

	return result;
}