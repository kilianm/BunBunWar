#ifndef __BunBunMenuApplication_H__
#define __BunBunMenuApplication_H__

#include "BunBunApplication.h" 
#include "BunBunMenuGuiControl.h" 

class BunBunMenuApplication : public BunBunApplication {
public:
	BunBunMenuApplication(int id, int parentId, int* nextApplication, bool* exitApplication, Root* mRoot, EventProcessor* mEventProcessor);
	~BunBunMenuApplication();

protected:
	void setup();
    void createCamera();
    void createGuiControl();
    void createScene();
	void createDrawControl();
    void destroyScene();
};


#endif
