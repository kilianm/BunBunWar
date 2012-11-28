#ifndef OGRETYPEUNIT_H
#define OGRETYPEUNIT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/Utilities.h>
#include <bunbunwar/GODEngine.h>

class DLLEXPORT OgreUnitType : public GODUnitTypeObject {
public:
	OgreUnitType();
	~OgreUnitType();

	void setMeshName(std::string meshName);
	std::string getMeshName();
protected:
	template class DLLEXPORT std::allocator<char>;
	template class DLLEXPORT std::basic_string<char, std::char_traits<char>,std::allocator<char> >;
private:
	std::string meshName;
};

#endif