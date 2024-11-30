#pragma once
#include <AcidLib/String/String.hpp>

using namespace ac;

class LexerDebugInfo {
public:

	enum DebugInfoType {

		Error,
		Info,
	};

	DebugInfoType type;

	String message;

	LexerDebugInfo();
	LexerDebugInfo(DebugInfoType p_type, String p_message);
};

LexerDebugInfo::LexerDebugInfo() {

	type = DebugInfoType::Info;
	message = "";
}

LexerDebugInfo::LexerDebugInfo(DebugInfoType p_type, String p_message) {

	type = p_type;
	message = p_message;
}