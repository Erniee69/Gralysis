#pragma once
#include <exception>
#include <AcidLib/String/String.hpp>

using namespace ac;

class LogicError : public std::exception {
public:

	LogicError(String p_message);

	const char* what() noexcept;

private:

	String m_message;
};

LogicError::LogicError(String p_message) {

	m_message = p_message;
}

const char* LogicError::what() noexcept {

	return m_message.cstr();
}