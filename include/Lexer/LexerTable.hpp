#pragma once
#include <Lexer/CharacterValidator.hpp>
#include <AcidLib/Containers/Map.hpp>
#include <AcidLib/Containers/ArrayList.hpp>
#include <Lexer/LexerAction.hpp>

class LexerTable {
public:

	void addAction(int lexerState, CharacterValidator validator, LexerAction action);

	ArrayList<LexerAction> getActions(int lexerState, char character);

	bool hasStartState() const;

private:

	Map<int, Map<CharacterValidator, ArrayList<LexerAction>>> m_table;
	Map<int, ArrayList<LexerAction>> m_fallbackTable;
};

void LexerTable::addAction(int lexerState, CharacterValidator validator, LexerAction action) {

	if (validator.type == CharacterValidator::Fallback) {

		if (!m_fallbackTable.has(lexerState)) {

			m_fallbackTable.append(lexerState, ArrayList<LexerAction>());
		}

		m_fallbackTable[lexerState].append(action);
	}
	else {

		if (!m_table.has(lexerState)) {

			m_table.append(lexerState, Map<CharacterValidator, ArrayList<LexerAction>>());
		}

		if (!m_table[lexerState].has(validator)) {

			m_table[lexerState].append(validator, ArrayList<LexerAction>());
		}

		m_table[lexerState][validator].append(action);
	}
}

ArrayList<LexerAction> LexerTable::getActions(int lexerState, char character) {

	if (m_table.has(lexerState)) {

		for (const KeyValuePair<CharacterValidator, ArrayList<LexerAction>>& kv : m_table[lexerState]) {

			if (kv.key.isValid(character)) {

				return kv.value;
			}
		}
	}

	if (m_fallbackTable.has(lexerState)) {

		return m_fallbackTable[lexerState];
	}

	return ArrayList<LexerAction>();
}

bool LexerTable::hasStartState() const {

	return m_table.has(0) || m_fallbackTable.has(0);
}