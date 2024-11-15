#pragma once
#include <AcidLib/Exception/Exception.hpp>

class EmptyStackException : public Exception {
public:

	EmptyStackException(const char* p_message);

	virtual const char* what() const override;

private:

	const char* m_message;
};