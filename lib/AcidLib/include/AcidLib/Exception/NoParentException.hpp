#pragma once
#include <AcidLib/Exception/Exception.hpp>

class NoParentException : public Exception {
public:

	virtual const char* what() const override;
};