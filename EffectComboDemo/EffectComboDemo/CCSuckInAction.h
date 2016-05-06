#ifndef __CCSUCKINACTION_H__
#define __CCSUCKINACTION_H__

#import "cocos2d.h"
using namespace cocos2d;

class CCSuckInAction: public CCGrid3DAction
{
public:
    CCPoint bkPoint;

public:
    CCSuckInAction(void);
    virtual ~CCSuckInAction(void);
    
    virtual CCObject* copyWithZone(CCZone *pZone);
	virtual void update(ccTime dt);
    
    static CCSuckInAction* actionWithSize(ccGridSize gridSize, ccTime d, CCPoint p);
    bool initWithSize(ccGridSize gridSize, ccTime d, CCPoint p);
};

#endif // __CCSUCKINACTION_H__

