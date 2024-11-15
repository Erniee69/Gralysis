#include <AcidLib/Exception/KeyAlreadyExistsException.hpp>

const char* KeyAlreadyExistsException::what() const {

	return "KeyAlreadyExistsException: The key already exists.";
}