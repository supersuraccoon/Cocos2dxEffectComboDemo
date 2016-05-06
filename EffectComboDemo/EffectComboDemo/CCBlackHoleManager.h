#ifndef __CCBLACKHOLEUTIL_H__
#define __CCBLACKHOLEUTIL_H__

#import "cocos2d.h"
using namespace cocos2d;

typedef enum CCBlackHoleTag 
{
	kBlackHoleSprite = 9999,
} CCBLACKHOLE_TAG; 

class CCBlackHoleManager: public CCNode
{
private:
    CCBlackHoleManager(void);
    ~CCBlackHoleManager(void);
    
    bool m_isRunning;

public:
    bool init(void);
    static CCBlackHoleManager* sharedManager(void);
    
    void runBlackHoleEffect(ccGridSize gridSize, 
                            ccTime duration, 
                            CCPoint bkPoint, 
                            CCNode *pTarget,
                            const char *pszFileBlackHole);
    void runBlackHoleSprite(CCNode *pParent, 
                            ccTime duration,
                            CCPoint bkPoint, 
                            const char *pszFileBlackHole);
    void removeSprite(CCNode *pSender);
};

#endif // __CCBLACKHOLEUTIL_H__

