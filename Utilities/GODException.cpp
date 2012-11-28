#include "GODException.h"

GODException::GODException() {
	GODException::message = "GODException";
	GODException::cause = "Unknown";
}

GODException::GODException(char* message) {
	GODException::message = message;
	GODException::cause = "Unknown";
}

GODException::GODException(char* message, char* cause) {
	GODException::message = message;
	GODException::cause = cause;
}

GODException::~GODException() {
	delete GODException::message;
}

char* GODException::getMessage() {
	return GODException::message;
}

char* GODException::getCause() {
	return GODException::cause;
}

char* GODException::toString() {
	char* string;
	sprintf(string, "%s caused by: %s", message, cause);
	return string;
}
