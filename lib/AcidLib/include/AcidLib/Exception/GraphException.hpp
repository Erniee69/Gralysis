#pragma once
#include <AcidLib/Exception/Exception.hpp>

class GraphException : public Exception {
public:

	GraphException(const char* p_msg);

	const char* what() const;

private:

	const char* msg;
};