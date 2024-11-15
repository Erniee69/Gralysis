#include <AcidLib/Exception/GraphException.hpp>

GraphException::GraphException(const char* p_msg) {

	msg = p_msg;
}

const char* GraphException::what() const {

	return msg;
}