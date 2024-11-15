#pragma once

class Exception {
public:

	virtual const char* what() const = 0;
};