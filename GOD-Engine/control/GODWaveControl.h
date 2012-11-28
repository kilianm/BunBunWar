#ifndef GODWAVECONTROL_H
#define GODWAVECONTROL_H

#include <bunbunwar/stdafx.h>
#include <bunbunwar/stdincludes.h>
#include <bunbunwar/GODEngine.h>
#include "../xml/GODXML.h"
#include <list>

class DLLEXPORT GODWaveControl : public GODXMLObjectParser {
public:
	static std::string XML_OBJECT_NAME;
	static GODWaveControl* getInstance();

	~GODWaveControl();

	void startWaves();
	void resetWaves();
	void waveDied();
	void stopWaves();

	bool isDoneWaveSpawns();
	void setDoneWaveSpawns(bool doneWaveSpawns);

	bool startSpawningNextWave();

	bool isSpawningWaves();

	GODWaveObject* nextWave();
	bool hasNextWave();

	int getReward();

	static void spawnWaves();

	std::string getXMLObjectName();
	GODXMLObjectParser* parseXMLObject(GODXMLObject* object);
protected:
	GODWaveControl();
private:
	static GODWaveControl* instance;

	bool doneWaveSpawns;
	bool startSpawnNextWave;
	bool spawningWaves;

	GODWaveObject* currentWave;
	HANDLE thread;

	std::list<GODWaveObject*> waves;
};

#endif