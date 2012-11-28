#ifndef BUNBUNMENUGUICONTROL_H
#define BUNBUNMENUGUICONTROL_H

#include <bunbunwar/OgreGODEngine.h>
#include <bunbunwar/GODEngine.h>
#include "BunBunGuiControl.h"
#include "BunBunMenuDrawControl.h"
#include <list>

struct GameData {
	int id;
	std::string filename;
	GODXMLObjectParser* godXmlObject;
};

class BunBunMenuGuiControl : public BunBunGuiControl {
public:
	BunBunMenuGuiControl(BunBunDrawControl* mDrawControl, Timer* mTimer, EventProcessor* mEventProcessor);
	~BunBunMenuGuiControl();

	void mousePressed(MouseEvent* e);
	void mouseReleased(MouseEvent* e);
	void mouseMoved(MouseEvent* e);

	bool handleStartGame(const CEGUI::EventArgs& e);
	bool handleOptions(const CEGUI::EventArgs& e);
	bool handleQuit(const CEGUI::EventArgs& e);
	bool handleStartGameStart(const CEGUI::EventArgs& e);
	bool handleStartGameCancel(const CEGUI::EventArgs& e);
	bool handleGameTypeChange(const CEGUI::EventArgs& e);
	bool handleMissionChange(const CEGUI::EventArgs& e);

protected:
    BunBunMenuDrawControl* mDrawControl;
	std::list<GameData> gameTypeData;
	GODGameTypeObject* selectedGameType;
	GODMissionObject* selectedMission;

	void updateMissionInfo();
	std::list<GameData> retrieveObjects(String win32SearchPath, String xmlPath);
	std::list<String> retrieveDirectoryListing(String win32SearchPath);

	bool onRenderFrame();
	void createScene();
	void setupEventHandlers();
};

#endif
