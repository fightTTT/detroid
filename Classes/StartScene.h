#pragma once
#include "cocos2d.h"
#ifndef __STARTSCENE_SCENE_H__
#define __STARTSCENE_SCENE_H__

class StartScene : 
	public cocos2d::Scene 
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(StartScene);

private:
	void NextGameScene(float dt);
};

#endif // __HELLOWORLD_SCENE_H__