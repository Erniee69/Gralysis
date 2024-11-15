#pragma once
#include <AcidLib/Exception/Exception.hpp>

class KeyAlreadyExistsException : public Exception {
public:

	virtual const char* what() const override;
};