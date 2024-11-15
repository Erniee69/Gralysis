#pragma once
#include <AcidLib/Exception/Exception.hpp>

class IndexOutOfBoundsException : public Exception {
public:

	int m_index;
	int m_min;
	int m_max;

	IndexOutOfBoundsException(int p_index, int p_min, int p_max);

	virtual const char* what() const override;
};