#pragma once
#include <exception>
#include <AcidLib/String/String.hpp>

using namespace ac;

class ValueError : public std::exception {
public:

	ValueError(String p_message);

	const char* what() noexcept;

private:

	String m_message;
};

ValueError::ValueError(String p_message) {

	m_message = p_message;
}

const char* ValueError::what() noexcept {

	return m_message.cstr();
}