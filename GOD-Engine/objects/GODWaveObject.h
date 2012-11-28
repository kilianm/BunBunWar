#ifndef GODWAVEOBJECT_H
#define GODWAVEOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../xml/GODXML.h"

class DLLEXPORT GODWaveObject : public GODXMLObjectParser {
public:
	static std::string XML_OBJECT_NAME;

	GODWaveObject();
	~GODWaveObject();

	int getNumber();
	void setNumber(int number);

	int getReward();
	void setReward(int reward);

	int getUnitType();
	void setUnitType(int unitType);

	int getUpgrade();
	void setUpgrade(int upgrade);

	int getAmount();
	void setAmount(int amount);

	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
private:
	int number;
	int reward;
	int unitType;
	int upgrade;
	int amount;
};

#endif