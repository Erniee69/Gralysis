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

		bool check(char data) const;

	private:

		union {

			char singleChar;
			Pair<char, char> charRange;
		};
	};

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

bool CharacterClass::Rule::check(char data) const {

	if (type == Rule::SingleChar) {

		return singleChar == data;
	}
	else {

		return (charRange.first <= data) && (data <= charRange.second);
	}
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