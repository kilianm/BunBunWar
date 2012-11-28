#ifndef BUNBUNGUICONTROL_H
#define BUNBUNGUICONTROL_H

#define TIME_FRAME_MS 10 //each 1/100 sec a timeframe occurs.

#include <ogre/Ogre.h>
#include <ogre/OgreEventListeners.h>
#include <ogre/OgreKeyEvent.h>
#include <ogre/OgreMouseEvent.h>
#include <ogre/OgreStringConverter.h>
#include <ogre/OgreException.h>
#include <ogre/OgreTimer.h>
//mem probs without this next one
#include <ogre/OgreNoMemoryMacros.h>
#include <ogre/CEGUI/CEGUIImageset.h>
#include <ogre/CEGUI/CEGUISystem.h>
#include <ogre/CEGUI/CEGUILogger.h>
#include <ogre/CEGUI/CEGUISchemeManager.h>
#include <ogre/CEGUI/CEGUIWindowManager.h>
#include <OgreCEGUIRenderer.h>
#include <OgreCEGUIResourceProvider.h>
#include <ogre/CEGUI/CEGUI.h>
//regular mem handler
#include <ogre/OgreMemoryMacros.h> 

#include "BunBunDrawControl.h"

using namespace Ogre;

class BunBunGuiControl : public FrameListener, KeyListener, public MouseMotionListener, public MouseListener {
public:
	BunBunGuiControl(BunBunDrawControl* mDrawControl, Timer* mTimer, EventProcessor* mEventProcessor);
	virtual ~BunBunGuiControl();

	virtual bool frameStarted(const FrameEvent& evt);
    virtual bool frameEnded(const FrameEvent& evt);
	virtual void keyClicked(KeyEvent* e);
	virtual void keyPressed(KeyEvent* e);
	virtual void keyReleased(KeyEvent* e);
	virtual void keyFocusIn(KeyEvent* e);
	virtual void keyFocusOut(KeyEvent* e);
	virtual void mouseClicked(MouseEvent* e);
	virtual void mouseEntered(MouseEvent* e);
	virtual void mouseExited(MouseEvent* e);
	virtual void mousePressed(MouseEvent* e);
	virtual void mouseReleased(MouseEvent* e);
	virtual void mouseDragEntered(MouseEvent* e);
	virtual void mouseDragExited(MouseEvent* e);
	virtual void mouseDragDropped(MouseEvent* e);
	virtual void mouseMoved(MouseEvent* e);
	virtual void mouseDragged(MouseEvent* e);
	virtual void mouseDragMoved(MouseEvent* e);

protected:
	virtual void createScene()=0;
	virtual void setupEventHandlers()=0;
	virtual bool onRenderFrame()=0;

    BunBunDrawControl* mDrawControl;
	Timer* mTimer;
    EventProcessor* mEventProcessor;
    InputReader* mInputDevice;

	CEGUI::OgreCEGUIRenderer* mGUIRenderer;
	CEGUI::System* mGUISystem;
	CEGUI::Window* mEditorGuiSheet;
	CEGUI::Point mGUIOriginalPoint;
	CEGUI::MouseButton convertOgreButtonToCegui(int buttonID);
private:
};

#endif
