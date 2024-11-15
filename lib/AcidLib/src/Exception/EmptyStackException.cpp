#include <AcidLib/Exception/EmptyStackException.hpp>

EmptyStackException::EmptyStackException(const char* p_message) {

	m_message = p_message;
}

const char* EmptyStackException::what() const {

	return m_message;
}