#ifndef GODUNITTYPEOBJECT_H
#define GODUNITTYPEOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../xml/GODXML.h"

class DLLEXPORT GODUnitTypeObject : public GODXMLObjectParser {
public:
	static std::string XML_OBJECT_NAME;

	GODUnitTypeObject();
	~GODUnitTypeObject();

	// Default Getter & Setters
	int getId();
	void setId(int id);
	int getHealth();
	void setHealth(int health);
	int getMovement();
	void setMovement(int movement);
	int getAttackPower();
	void setAttackPower(int attackPower);
	int getArmor();
	void setArmor(int armor);
	int getAttackSpeed();
	void setAttackSpeed(int attackSpeed);
	int getRange();
	void setRange(int range);
	int getMissRate();
	void setMissRate(int missRate);
	int getCritRate();
	void setCritRate(int critRate);
	int getPrice();
	void setPrice(int price);
	int getUpgrade();
	void setUpgrade(int upgrade);

	std::string getMeshName();
	void setMeshName(std::string meshName);

	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
protected:
	int id;
	int health;
	int movement;
	int attackPower;
	int armor;
	int attackSpeed;
	int range;
	int missRate;
	int critRate;
	int price;
	int upgrade;
	std::string meshName;
};

#endif