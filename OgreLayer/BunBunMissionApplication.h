#ifndef __BunBunMissionApplication_H__
#define __BunBunMissionApplication_H__
#define CAMERA_ZOOM_DEFAULT 1200
#define CAMERA_X_DEFAULT 0
#define CAMERA_Z_DEFAULT 100
#define CAMERA_LOOKAT_X 0-CAMERA_X_DEFAULT
#define CAMERA_LOOKAT_Y -3800-CAMERA_ZOOM_DEFAULT
#define CAMERA_LOOKAT_Z -500-CAMERA_Z_DEFAULT

#include "BunBunApplication.h" 
#include "BunBunMissionDrawControl.h" 
#include "BunBunMissionGuiControl.h" 
#include <bunbunwar/GODEngine.h>
#include <bunbunwar/OgreGODEngine.h>
#include "BunBunFloorEntityFactory.h"
#include "BunBunSceneManager.h"

class BunBunMissionApplication : public BunBunApplication {
public:
	BunBunMissionApplication(int id, int parentId, int* nextApplication, bool* exitApplication, Root* mRoot, EventProcessor* mEventProcessor);
	~BunBunMissionApplication();

protected:
	BunBunFloorEntityFactory* mBunBunFloorEntityFactory;

	void setup();
    void createCamera();
    void createGuiControl();
    void createScene();
	void createDrawControl();
    void destroyScene();
};


#endif
