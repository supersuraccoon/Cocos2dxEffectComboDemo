#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "CCSpotLight.h"
#include "CCBlackHoleManager.h"
#include "CCLabelEffectUtil.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MainScene::scene()
{
	CCScene *scene = CCScene::node();
	MainScene *layer = MainScene::node();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    CCDirector::sharedDirector()->setDisplayFPS(false);
    
	CCLabelBMFont *pLabel = CCLabelBMFont::labelWithString("COCOS2DX 1-Year Anniversary", "futura-48.fnt");
    pLabel->setOpacity(0);
    pLabel->setScale(0.6f);
    pLabel->setPosition(240, 50);
    this->addChild(pLabel, 1, 2);
    
    CCLabelBMFont *pLabe2 = CCLabelBMFont::labelWithString("By SuperSuRaccoon", "futura-48.fnt");
    pLabe2->setOpacity(0);
    pLabe2->setScale(0.6f);
    pLabe2->setPosition(240, 160);
    this->addChild(pLabe2, 1, 3);
    
	CCSprite* pBg = CCSprite::spriteWithFile("HelloWorld.png");
    pBg->setPosition( ccp(240, 160) );
    this->addChild(pBg, 0, 1);
    
    runEffect_1();
    
	return true;
}

void MainScene::runEffect_1()
{
    CCRenderTexture *renderLayer = CCRenderTexture::renderTextureWithWidthAndHeight(480, 320);
    renderLayer->setPosition(240, 160);
    renderLayer->getSprite()->setBlendFunc((ccBlendFunc) { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA });
    
    this->addChild(renderLayer, 0);
    
    CCSpotLight *spotLight = CCSpotLight::initSpotLight(renderLayer, 60.0f, ccc4(0, 0, 0, 255), ccp(100, 100));
    this->addChild(spotLight, 1);
    spotLight->runSpotEffect();
    
    spotLight->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(0.8f, ccp(20, 300)),
                                             CCMoveTo::actionWithDuration(0.8f, ccp(460, 300)),
                                             CCMoveTo::actionWithDuration(0.8f, ccp(0, 160)),
                                             CCMoveTo::actionWithDuration(0.8f, ccp(460, 160)),
                                             CCMoveTo::actionWithDuration(0.8f, ccp(20, 20)),
                                             CCMoveTo::actionWithDuration(0.8f, ccp(460, 20)),
                                             CCMoveTo::actionWithDuration(0.8f, ccp(240, 160)),
                                             CCCallFuncN::actionWithTarget(this, callfuncN_selector(MainScene::spotSpreadOut)),
                                             NULL));
}

void MainScene::runEffect_2()
{
    CCLabelBMFont *pLabel = (CCLabelBMFont *)this->getChildByTag(2);
    CCLabelEffectUtil::runLabelEffect_1(pLabel);
    
    this->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(6.0f),
                                        CCCallFunc::actionWithTarget(this, callfunc_selector(MainScene::runEffect_3)),
                                        NULL));
}

void MainScene::runEffect_3()
{
    CCSprite* pSprite = (CCSprite*)this->getChildByTag(1);
    CCBlackHoleManager::sharedManager()->runBlackHoleEffect(ccg(10, 10), 3.0f, ccp(240, 160), pSprite, "BlackHole.png");
    
    this->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(3.0f),
                                        CCCallFunc::actionWithTarget(this, callfunc_selector(MainScene::runEffect_4)),
                                        NULL));
}

void MainScene::runEffect_4()
{
    CCSprite* pHiddenBg = CCSprite::spriteWithFile("bg.png");
    pHiddenBg->setPosition( ccp(240, 160) );
    this->addChild(pHiddenBg, 0);
    
    CCSprite *pRaccoon = CCSprite::spriteWithFile("raccoon.png");
    pRaccoon->setPosition(ccp(400, 160));
    pRaccoon->setScale(0.6f);
    pRaccoon->setOpacity(0);
    this->addChild(pRaccoon, 0);
    
    CCLabelBMFont *pLabel = (CCLabelBMFont *)this->getChildByTag(3);
    CCLabelEffectUtil::runLabelEffect_2(pLabel);
    
    pRaccoon->runAction(CCSequence::actions(CCDelayTime::actionWithDuration(2.5f),
                                            CCFadeIn::actionWithDuration(1.0f),
                                            NULL));
}

void MainScene::spotSpreadOut(CCObject *pSender)
{
    CCSpotLight *spotLight = (CCSpotLight *)pSender;
    spotLight->spreadOutAndRemove();
    
    runEffect_2();
}

