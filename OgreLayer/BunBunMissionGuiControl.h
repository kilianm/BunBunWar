#ifndef BUNBUNMISSIONGUICONTROL_H
#define BUNBUNMISSIONGUICONTROL_H

#include <bunbunwar/OgreGODEngine.h>
#include <bunbunwar/GODEngine.h>
#include "BunBunGuiControl.h"
#include "BunBunMissionDrawControl.h"

class BunBunMissionGuiControl : public BunBunGuiControl {
public:
	BunBunMissionGuiControl(BunBunDrawControl* mDrawControl, Timer* mTimer, EventProcessor* mEventProcessor);
	~BunBunMissionGuiControl();

	void mousePressed(MouseEvent* e);
	void mouseReleased(MouseEvent* e);
	void mouseMoved(MouseEvent* e);
	void mouseDragged(MouseEvent* e);

	bool handleQuit(const CEGUI::EventArgs& e);
	bool handleMainMenu(const CEGUI::EventArgs& e);
	bool handlePause(const CEGUI::EventArgs& e);
	bool handleBuildTower(const CEGUI::EventArgs& e);
	bool handleUpgradeTower(const CEGUI::EventArgs& e);
	bool handleDeleteTower(const CEGUI::EventArgs& e);
	bool handleRollupToggle(const CEGUI::EventArgs& e);
	void handleTitlebarChange(int money, int lives);
	void handleSelectionText(String name, int newValue, int originalValue);
	void handleFinishedMission(bool victory);

protected:
    BunBunMissionDrawControl* mDrawControl;
	bool textIsClean;

	void setGuiAlpha(bool alphaOn);

	bool onRenderFrame();
	void createScene();
	void setupEventHandlers();
};

#endif