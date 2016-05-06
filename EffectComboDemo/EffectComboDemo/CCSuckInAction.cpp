#include "CCSuckInAction.h"

CCSuckInAction::CCSuckInAction(void)
{
}

CCSuckInAction::~CCSuckInAction(void)
{
}

bool CCSuckInAction::initWithSize(ccGridSize gridSize, ccTime d, CCPoint p)
{
    if (CCGrid3DAction::initWithSize(gridSize, d))
    {
        this->bkPoint = p;
        return true;
    }
	return false;
}

CCSuckInAction* CCSuckInAction::actionWithSize(ccGridSize gridSize, ccTime d, CCPoint p)
{
	CCSuckInAction* pSuckInAction = new CCSuckInAction();
    pSuckInAction->initWithSize(gridSize, d, p);
    pSuckInAction->autorelease();
    
	return pSuckInAction;
}

void CCSuckInAction::update(ccTime time)
{
	int i, j;
    CCPoint target = this->bkPoint;
	for( i = 0; i < (this->m_sGridSize.x +1); i++ )
	{
		for( j = 0; j < (this->m_sGridSize.y+1); j++ )
		{
			ccVertex3F	v = this->vertex(ccg(i, j));
            
            CGFloat s = ccpDistance(ccp(v.x, v.y), target);
            float distx = fabsf(v.x - target.x);
            float disty = fabsf(v.y - target.y);
            
            if (s > 0) {
                s = s / (20/this->getDuration());
                float valx = distx*time/s;
                if (valx > distx) valx = distx;
                if (valx < 0) valx = 0;
                float valy = disty*time/s;
                if (valy > disty) valy = disty;
                if (valy < 0) valy = 0;
				
                if (v.x < target.x)
                    v.x += valx;
                if (v.x >= target.x)
                    v.x -= valx;
				
                if (v.y < target.y)
                    v.y += valy;
                if (v.y >= target.y)
                    v.y -= valy;
            }
            this->setVertex(ccg(i,j), v);
		}
	}
}

CCObject* CCSuckInAction::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCSuckInAction* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCSuckInAction*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCSuckInAction();
		pZone = pNewZone = new CCZone(pCopy);
	}
    
    
	CCGrid3DAction::copyWithZone(pZone);
    
	pCopy->initWithSize(this->m_sGridSize, this->getDuration(), this->bkPoint);
    
	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

//void CCSuckInAction::runBlackHoleEffect(CCNode *target)
//{
//    //add black hole sprite
//    CCNode *parent = (CCSprite *)target->getParent();
//    CCSprite *bh = CCSprite::spriteWithFile("BlackHole.png");
//    bh->setPosition(ccp(240, 160));
//    parent->addChild(bh, 999);
//    
//    CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions(CCScaleTo::actionWithDuration(0.5f, 1.1f),
//                                                                    CCScaleTo::actionWithDuration(0.5f, 0.9f),
//                                                                    NULL));
//    CCActionInterval* spawn = (CCActionInterval*)(CCSpawn::actions(seq, 
//                                                                   CCRotateBy::actionWithDuration(0.5, 30.0f),
//                                                                   NULL));
//    bh->runAction(CCRepeatForever::actionWithAction(spawn));
//    
//    target->runAction(CCSuck::actionWithGrid(ccg(12, 12), 5.0f, target->getPosition()));
//}


