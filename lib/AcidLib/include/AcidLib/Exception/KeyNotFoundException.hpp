#pragma once
#include <AcidLib/Exception/Exception.hpp>

class KeyNotFoundException : public Exception {
public:

	virtual const char* what() const override;
};