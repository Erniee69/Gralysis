#include <GenericLexer.hpp>
#include <iostream>

using namespace ac;

const char* d = "T0 ::= \"::=\";\nT1 ::= \";\";\nT2 ::= \"=>\";\nT3 ::= \"{\";\nT4 ::= \"}\";\nT5 ::= \"|\";\nT6 ::= \"+\";\nT7 ::= \"*\";\nT8 ::= \"?\";\nT9 ::= \"(\";\nT10 ::= \")\";\nNONTERMINAL ::= \"<\" [A-Za-z0-9-_']+ \">\";\nTERMINAL ::= \"\\\"\" (\"\\\\\" $ | [^\"])* \"\\\"\";\nLEXTOKEN ::= [A-Z][A-Z0-9]*;\nNUMQUANT ::= \"{\" [0-9]+ \"}\";\nCHARCLASS ::= \"[\" (\"\\\\\" $ | [^\\[\\]\\\\])+ \"]\" => {\n	T0 ::= \"[\";\n	T1 ::= \"-\";\n	T2 ::= \"]\";\n	CHAR ::= [^\\[\\]\\\\] | \"\\\\\" $;\n	<CharClass> ::= \"[\" (CHAR | CHAR \"-\" CHAR)+ \"]\";\n};\nSKIP ::= \" \" | \"\\n\" | \"\\t\" | \"\\r\";\n<Grammar> ::= (<LexRule> | <GramRule>)+ ;\n<LexRule> ::= LEXTOKEN T0 <LexExpression> <SubLexBlock>? T1;\n<SubLexBlock> ::= T2 T3 <Grammar> T4;\n<LexExpression> ::= <LexTerm>+ (T5 <LexTerm>+)*;\n<LexTerm> ::= <LexFactor> (T6 | T7 | T8 | NUMQUANT)? ;\n<LexFactor> ::= TERMINAL | <CharClass> | T9 <LexExpression> T10;\n<GramRule> ::= NONTERMINAL T0 <GramExpression> T1;\n<GramExpression> ::= <GramTerm>+ (T5 <GramTerm>+)*;\n<GramTerm> ::= <GramFactor> (T6 | T7 | T8 | NUMQUANT)? ;\n<GramFactor> ::= TERMINAL | NONTERMINAL | LEXTOKEN | <CharClass>\n| T9 <GramExpression> T10;";
String data(d);

int main() {

	std::cout << data.cstr();

	return 0;
}