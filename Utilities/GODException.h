#ifndef GODEXCEPTION_H
#define GODEXCEPTION_H

#include <bunbunwar/stdafx.h>
#include <stdio.h>

class DLLEXPORT GODException {
public:
	GODException();
	GODException(char* message);
	GODException(char* message, char* cause);
	~GODException();

	// Getters & Setters
	char* getMessage();
	char* getCause();
	char* toString();
private:
	char* message;
	char* cause;
};

#endif