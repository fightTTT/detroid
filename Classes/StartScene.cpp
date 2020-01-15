#include "StartScene.h"
#include "GameScene.h"

cocos2d::Scene * StartScene::createScene()
{
	return StartScene::create();
}

bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();												
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	float scale = (visibleSize.height == 1024) ? 1.5f : (visibleSize.height == 576) ? 1.0f : visibleSize.height / 1024 * 1.5f;	

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(StartScene::NextGameScene), 3);

	cocos2d::Sprite* backgroundSprite = cocos2d::Sprite::create("StartBG.png");												
	backgroundSprite->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));		
	backgroundSprite->setScale(scale);																							
	this->addChild(backgroundSprite);

	this->scheduleUpdate();

	return true;
}

void StartScene::NextGameScene(float dt)
{
	cocos2d::Scene* scene = GameScene::createScene();	
	scene->setName("gameScene");
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5, scene));				
}
