#include "MainApplication.h"

bool MainApplication::exitApplication = false;
int MainApplication::lastApplication = 0;
int MainApplication::nextApplication = MainApplication::APPLICATION_MENU;
Root* MainApplication::mRoot = NULL;
EventProcessor* MainApplication::mEventProcessor = NULL;

void MainApplication::go() {
	if (!MainApplication::initialize())
		MainApplication::exitApplication = true;
	while (!MainApplication::exitApplication) {
		GODMissionControl* missionControl = GODMissionControl::getInstance();
		if (MainApplication::nextApplication == MainApplication::APPLICATION_MENU) {
			BunBunMenuApplication* menuApp = new BunBunMenuApplication(MainApplication::APPLICATION_MENU, 0, &MainApplication::nextApplication, &MainApplication::exitApplication, MainApplication::mRoot, MainApplication::mEventProcessor);
			menuApp->go();
			delete menuApp;
			MainApplication::lastApplication = MainApplication::APPLICATION_MENU;
		}
		else if (MainApplication::nextApplication == MainApplication::APPLICATION_MISSION) {
			BunBunMissionApplication* missionApp = new BunBunMissionApplication(MainApplication::APPLICATION_MISSION, MainApplication::APPLICATION_MENU, &MainApplication::nextApplication, &MainApplication::exitApplication, MainApplication::mRoot, MainApplication::mEventProcessor);
			missionApp->go();
			delete missionApp;
			MainApplication::lastApplication = MainApplication::APPLICATION_MISSION;
		}
		else
			MainApplication::exitApplication = true;
	}
	delete MainApplication::mRoot;
}

bool MainApplication::initialize() {
	MainApplication::mRoot = new Root("plugins.cfg", "bunbunwar.cfg", "bunbunwar.log");
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
	if (!MainApplication::mRoot->showConfigDialog())
		return false;
	RenderWindow* window = MainApplication::mRoot->initialise(true, "BunBunWar");
	MainApplication::mEventProcessor = new EventProcessor();
	MainApplication::mEventProcessor->initialise(window);
	return true;
}