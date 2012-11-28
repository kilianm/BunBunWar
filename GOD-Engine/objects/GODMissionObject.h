#ifndef GODMISSIONOBJECT_H
#define GODMISSIONOBJECT_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include "../xml/GODXML.h"
#include "../control/GODUnitControl.h"
#include "../control/GODLandscapeControl.h"
#include "../control/GODUnitTypeControl.h"

class DLLEXPORT GODMissionObject : public GODXMLObjectParser {
public:
	static std::string XML_OBJECT_NAME;

	GODMissionObject();
	~GODMissionObject();

	GODUnitControl* getUnitControl();
	void setUnitControl(GODUnitControl* unitControl);
	GODLandscapeControl* getLandscapeControl();
	void setLandscapeControl(GODLandscapeControl* landscapeControl);
	GODUnitTypeControl* getUnitTypeControl();
	void setUnitTypeControl(GODUnitTypeControl* unitTypeControl);
	std::string getName();
	void setName(std::string name);
	int getCurrentMoney();
	void setCurrentMoney(int currentMoney);
	int getTotalMoney();
	void setTotalMoney(int totalMoney);

	int getLives();
	void setLives(int lives);

	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
protected:
private:
	GODUnitControl* unitControl;
	GODLandscapeControl* landscapeControl;
	GODUnitTypeControl* unitTypeControl;

	std::string name;
	int currentMoney;
	int totalMoney;
	int lives;
};

#endif