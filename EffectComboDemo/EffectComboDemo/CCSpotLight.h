#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__

#include "cocos2d.h"
using namespace cocos2d;

class CCSpotLight : public CCSprite
{
public:
    CCRenderTexture *renderTexture;
	float spotLightRadius;
	ccColor4B renderColor;
    
public:
    CCSpotLight(void);
    virtual ~CCSpotLight(void);
    
    void runSpotEffect();
    void tick(ccTime delta);
    
    static CCSpotLight* initSpotLight(CCRenderTexture* texture,
                                      float rarius, 
                                      ccColor4B color,
                                      CCPoint pt);
    void spreadOutAndRemove();
    void spreadOutTimer();
};

#endif // __SPOTLIGHT_H__
