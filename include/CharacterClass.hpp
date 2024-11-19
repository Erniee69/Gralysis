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

		bool check(String data);

	private:

		String singleChar;
		Pair<String, String> charRange;
	};

	bool negated;

	ArrayList<Rule> rules;

	void addRule(Rule r);

	bool check(String data);
};

CharacterClass::Rule::Rule(String p_singleChar) {

	type = Rule::SingleChar;

	singleChar = p_singleChar;
}

CharacterClass::Rule::Rule(String p_rangeStart, String p_rangeEnd) {

	type = Rule::CharRange;
}

bool CharacterClass::Rule::check(String data) {

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

bool CharacterClass::check(String data) {

	bool result = true;

	for (int i = 0; i < data.size(); i++) {

		bool tempResult = true;

		for (Rule& r : rules) {

			tempResult = tempResult && r.check(data[i]);
		}
	}

	result = result != negated; // != is xor

	return result;
}