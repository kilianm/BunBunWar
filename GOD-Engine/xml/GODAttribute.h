#ifndef GODATTRIBUTE_H
#define GODATTRIBUTE_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>

class DLLEXPORT GODAttribute {
public:
	GODAttribute(std::string name, std::string value);
	~GODAttribute();

	std::string getName();
	void setName(std::string name);
	std::string getValue();
	void setValue(std::string value);
private:
	std::string name;
	std::string value;
};

#endif