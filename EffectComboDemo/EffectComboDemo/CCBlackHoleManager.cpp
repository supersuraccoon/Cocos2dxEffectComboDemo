#include "CCBlackHoleManager.h"
#include "CCSuckInAction.h"

static CCBlackHoleManager *gSharedManager = NULL;


CCBlackHoleManager::CCBlackHoleManager(void){}

CCBlackHoleManager::~CCBlackHoleManager(void){}


CCBlackHoleManager* CCBlackHoleManager::sharedManager(void)
{
	CCBlackHoleManager *pRet = gSharedManager;
    
	if (! gSharedManager)
	{
		pRet = gSharedManager = new CCBlackHoleManager();
        
		if (! gSharedManager->init())
		{
			// delete CCBlackHoleManager if init error
			delete gSharedManager;
			gSharedManager = NULL;
			pRet = NULL;
		}
	}
    
	return pRet;
}

bool CCBlackHoleManager::init(void)
{
    this->m_isRunning = false;
	return true;
}

void CCBlackHoleManager::runBlackHoleEffect(ccGridSize gridSize, 
                                         ccTime duration, 
                                         CCPoint bkPoint, 
                                         CCNode *pTarget,
                                         const char *pszFileBlackHole)
{
    if (this->m_isRunning)
    {
        return;
    }
    
    CCAssert(pTarget != NULL, "Invalid Target!");
    
    CCNode *parent = (CCSprite *)pTarget->getParent();
    CCAssert(parent != NULL, "Invalid parent!");
    
    if (strcmp(pszFileBlackHole, "") != 0)
    {
        this->runBlackHoleSprite(parent, duration, bkPoint, pszFileBlackHole);
    }
    
    this->m_isRunning = true;
    pTarget->runAction(CCSequence::actions(CCSuckInAction::actionWithSize(gridSize, duration, bkPoint),
                                           CCCallFuncN::actionWithTarget(this, callfuncN_selector(CCBlackHoleManager::removeSprite)),
                                           NULL));
}

void CCBlackHoleManager::runBlackHoleSprite(CCNode *pParent, 
                                            ccTime duration,
                                            CCPoint bkPoint, 
                                            const char *pszFileBlackHole)
{
    CCSprite *pBlackHoleSprite = CCSprite::spriteWithFile(pszFileBlackHole);
    CCAssert(pBlackHoleSprite != NULL, "Invalid BlackHole Sprite!");
    
    pBlackHoleSprite->setPosition(bkPoint);
    pParent->addChild(pBlackHoleSprite, INT_MAX, kBlackHoleSprite);
    
    CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions(CCScaleTo::actionWithDuration(0.5f, 0.8f),
                                                                    CCScaleTo::actionWithDuration(0.5f, 0.4f),
                                                                    NULL));
    CCActionInterval* spawn = (CCActionInterval*)(CCSpawn::actions(seq, 
                                                                   CCRotateBy::actionWithDuration(1.0f, 720.0f),
                                                                   NULL));
    pBlackHoleSprite->runAction(CCSequence::actions(CCRepeat::actionWithAction(spawn, int(duration)),
                                                    CCSpawn::actions(CCScaleTo::actionWithDuration(1.0f, 50.0f),
                                                                     CCFadeOut::actionWithDuration(0.8f),
                                                                     NULL),
                                                    CCCallFuncN::actionWithTarget(this, callfuncN_selector(CCBlackHoleManager::removeSprite)),
                                                    NULL));
}

void CCBlackHoleManager::removeSprite(CCNode *pSender)
{
    pSender->removeFromParentAndCleanup(true);
    this->m_isRunning = false;
}
