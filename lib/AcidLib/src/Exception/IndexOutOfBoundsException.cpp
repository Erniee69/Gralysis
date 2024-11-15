#include <AcidLib/Exception/IndexOutOfBoundsException.hpp>

IndexOutOfBoundsException::IndexOutOfBoundsException(int p_index, int p_min, int p_max) {

	m_index = p_index;
	m_min = p_min;
	m_max = p_max;
}

const char* IndexOutOfBoundsException::what() const {

	return "IndexOutOfBoundsException: Index was out of range.";
}