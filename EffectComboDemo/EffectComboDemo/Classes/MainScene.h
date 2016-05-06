#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::CCLayer
{
public:
	virtual bool init();  
    static cocos2d::CCScene* scene();
	LAYER_NODE_FUNC(MainScene);

    
    void spotSpreadOut(CCObject *pSender);
    void runEffect_1();
    void runEffect_2();
    void runEffect_3();
    void runEffect_4();
};

#endif // __MAIN_SCENE_H__
