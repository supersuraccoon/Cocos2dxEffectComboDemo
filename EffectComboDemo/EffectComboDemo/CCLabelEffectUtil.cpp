#include "CCLabelEffectUtil.h"

CCLabelEffectUtil::CCLabelEffectUtil(void){}

CCLabelEffectUtil::~CCLabelEffectUtil(void){}

void CCLabelEffectUtil::runLabelEffect_1(CCLabelBMFont *pBmLabel)
{
    CCAssert(pBmLabel != NULL, "Invalid CCLabelBMFont!");
    
    int count = 0;
	CCArray *lArray = pBmLabel->getChildren();
	CCObject* lObj = NULL;
    //appear
	CCARRAY_FOREACH(lArray, lObj)
    {
        CCNode *lNode = (CCNode *)lObj;
        lNode->setRotation(-30.0f);
        lNode->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.1f * count++),
                                             CCSpawn::actions(CCScaleTo::actionWithDuration(0.2f, 0.9f),
                                                              CCFadeIn::actionWithDuration(0.2f),
                                                              CCRotateBy::actionWithDuration(0.2f, 30.0f),
                                                              NULL),
                                             NULL));
    }
    
    // jump
    CCARRAY_FOREACH(lArray, lObj)
    {
        CCNode *lNode = (CCNode *)lObj;
        lNode->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.3f + 0.1f * count++),
                                             CCJumpBy::actionWithDuration(0.2f, ccp(0, 0), 50, 1),
                                             NULL));
    }
    
    pBmLabel->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.3f + 0.1f * count + 0.2),
                                            CCFadeOut::actionWithDuration(0.5f),
                                            NULL));
}

void CCLabelEffectUtil::runLabelEffect_2(CCLabelBMFont *pBmLabel)
{
    CCAssert(pBmLabel != NULL, "Invalid CCLabelBMFont!");
    
    int count = 0;
	CCArray *lArray = pBmLabel->getChildren();
	CCObject* lObj = NULL;
    //appear
	CCARRAY_FOREACH(lArray, lObj)
    {
        CCNode *lNode = (CCNode *)lObj;
        lNode->setRotation(-30.0f);
        lNode->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(0.1f * count++),
                                             CCSpawn::actions(CCScaleTo::actionWithDuration(0.2f, 0.9f),
                                                              CCFadeIn::actionWithDuration(0.2f),
                                                              CCRotateBy::actionWithDuration(0.2f, 30.0f),
                                                              NULL),
                                             NULL));
    }
}
