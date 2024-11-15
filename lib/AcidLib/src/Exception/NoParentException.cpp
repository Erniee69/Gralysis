#include <AcidLib/Exception/NoParentException.hpp>

const char* NoParentException::what() const {

	return "Root node has no parent.";
}