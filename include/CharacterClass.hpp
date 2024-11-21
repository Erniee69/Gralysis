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

		Rule(String p_singleChar);
		Rule(String p_rangeStart, String p_rangeEnd);

		bool check(String data) const;

	private:

		String singleChar;
		Pair<String, String> charRange;
	};

	bool negated;

	ArrayList<Rule> rules;

	void addRule(Rule r);

	bool check(String data) const;
};

CharacterClass::Rule::Rule(String p_singleChar) {

	type = Rule::SingleChar;

	if (p_singleChar.size() != 1) {

		if (p_singleChar != "EOI") {

			throw ValueError("CharClass SingleChar Rule can only be 1 char or \"EOI\"");
		}
	}

	singleChar = p_singleChar;
}

CharacterClass::Rule::Rule(String p_rangeStart, String p_rangeEnd) {

	if (p_rangeStart.size() != 1) {

		throw ValueError("CharClass CharRange start can only be 1 char");
	}
	if (p_rangeEnd.size() != 1) {

		throw ValueError("CharClass CharRange end can only be 1 char");
	}

	type = Rule::CharRange;

	charRange.first = p_rangeStart;
	charRange.second = p_rangeEnd;
}

bool CharacterClass::Rule::check(String data) const {

	bool result = true;

	for (int i = 0; i < data.size(); i++) {
		
		if (type == Rule::SingleChar) {

			result = result && (String(data[i]) == singleChar);
		}
		else {

			result = result && (data[i] >= charRange.first[0] && data[i] <= charRange.second[0]);
		}
	}

	return result;
}

void CharacterClass::addRule(Rule r) {

	rules.append(r);
}

bool CharacterClass::check(String data) const {

	bool result = true;

	for (int i = 0; i < data.size(); i++) {

		bool tempResult = true;

		for (const Rule& r : rules) {

			tempResult = tempResult && r.check(data[i]);
		}

		result = result && (tempResult != negated);
	}

	return result;
}