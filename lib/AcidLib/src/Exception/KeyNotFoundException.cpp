#include <AcidLib/Exception/KeyNotFoundException.hpp>

const char* KeyNotFoundException::what() const {

	return "KeyNotFoundException: Key could not be found.";
}