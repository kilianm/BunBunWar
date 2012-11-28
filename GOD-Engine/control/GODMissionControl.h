#ifndef GODMISSIONCONTROL_H
#define GODMISSIONCONTROL_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <bunbunwar/GODEngine.h>

#include "../objects/GODGameTypeObject.h"
#include "../objects/GODMissionObject.h"

class DLLEXPORT GODMissionControl {
public:
	~GODMissionControl();

	static GODMissionControl* getInstance();

	void loadMission(GODGameTypeObject* gameTypeObject, GODMissionObject* missionObject);
	GODGameTypeObject* getGameTypeObject();
	GODMissionObject* getMissionObject();

	void startMission();
	void stopMission();
	static void mission();
	void addUnit(GODUnitObject* unit);

	bool hasCondition(int unitGroup, int alive);
	bool victoryCondition(int unitGroup, int alive);
	bool defeatCondition(int unitGroup, int alive);

	GODUnitControl* getUnitControl();
	GODLandscapeControl* getLandscapeControl();
	GODUnitTypeControl* getUnitTypeControl();
	GODPathFinder* getPathFinder();

	void finishedMove(int unitId);

	void increaseMoney(int money);
	bool decreaseMoney(int money);
	int getCurrentMoney();
	void setTotalMoney(int money);
	int getTotalMoney();
	void setPathBlocked(bool pathBlocked);
	bool isPathBlocked();
	bool isMoneyValueChanged();

	int getCurrentLives();
	bool decreaseLive();
	bool isLivesValueChanged();

	void setVictory();
	void setDefeat();
	bool isVictorious();
	bool isDefeated();
	bool isFinished();
	bool isAttacking(GODUnitObject* unit);
	bool isLoaded();

	bool isPaused();
	void pause();

	bool isMissionActive();
	void resetMission();
protected:
	GODMissionControl();
	void isMissionLoaded();
	void setGameTypeObject(GODGameTypeObject* gameTypeObject);
	void setMissionObject(GODMissionObject* missionObject);
private:
	GODMissionObject* missionObject;
	GODGameTypeObject* gameTypeObject;
	HANDLE thread;
	bool missionActive;
	bool finished;
	bool victory;
	bool defeat;
	bool paused;
	bool moneyValueChanged;
	bool livesValueChanged;
	bool pathBlocked;
	static GODMissionControl* instance;
};

#endif