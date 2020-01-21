#include <cmath>
#include "Shot.h"
#include "ActCtrl.h"

#include "Console/_DebugConOut.h"

USING_NS_CC;

cocos2d::Sprite * Shot::createSprite(cocos2d::Vec2 pos, cocos2d::Vec2& speed, SHOT_TYPE shotType)
{
	//Shot *shot = new Shot(pos, speed,shotType);
	//if (shot&&shot->init())
	//{
	//	shot->autorelease();
	//	return shot;
	//}

	//delete shot;
	//shot = nullptr;
	return nullptr;
}

Shot::Shot()
{
}

Shot::Shot(cocos2d::Vec2& pos, cocos2d::Vec2& speed,SHOT_TYPE shotType)
{
	//setPosition(pos);
	_speed = speed;
	_shotType = shotType;
	Init();
}


Shot::~Shot()
{
}

void Shot::Init()
{
	cocos2d::Animate* anim;
	anim = Animate::create(AnimationCache::getInstance()->getAnimation("shot"));
	//runAction(RepeatForever::create(anim));
	//setGlobalZOrder(99);
	//auto layer = Director::getInstance()->getRunningScene()->getChildByName("FollowerLayer")->getChildByName("PlayerLayer");
	//layer->addChild(this);
	_colSize = {18,12};
	dethFlag = false;

	_shotData[0].shotType = SHOT_TYPE::NORMAL;
	_shotData[1].shotType = SHOT_TYPE::DIFFUSION;
	_shotData[2].shotType = SHOT_TYPE::TRACKING;

	for (auto &shot : _shotData)
	{
		shot.vel.x = 10;
		shot.vel.y = 10;
	}

	/*this->scheduleUpdate();*/
}

void Shot::Update(Input* input)
{
	if (input->GetInputType(EventKeyboard::KeyCode::KEY_Z) == INPUT_TRG::ON_MOMENT)
	{
		NormalShot();
	}
	else if (input->GetInputType(EventKeyboard::KeyCode::KEY_X) == INPUT_TRG::ON_MOMENT)
	{
		DiffusionShot();
	}
	else if (input->GetInputType(EventKeyboard::KeyCode::KEY_C) == INPUT_TRG::ON_MOMENT)
	{
		TrackingShot();
	}
	else
	{
		// ‰½‚à‚µ‚È‚¢
	}

}

const bool Shot::CheckDeth()
{
	return dethFlag;
}

const cocos2d::Vec2 & Shot::GetColSize()
{
	return _colSize;
}

ShotArray Shot::GetShotData()
{
	return _shotData;
}

void Shot::NormalShot()
{
	//setPositionX(getPositionX() + _speed.x);
}

void Shot::DiffusionShot()
{
	auto layer = Director::getInstance()->getRunningScene()->getChildByName("FollowerLayer")->getChildByName("PlayerLayer");
	auto player = layer->getChildByName("player");

	if (!((Sprite&)player).isFlippedX())
	{
		auto testshot = new ShotType();
		for (int i = 2; i > -3; i--)
		{
			_speed.x = cos((15 * i * M_PI / 180)) * 2;
			_speed.y = sin((15 * i * M_PI / 180)) * 2;
			_shotData[CAST_INT(SHOT_TYPE::DIFFUSION)].shot.emplace_back(testshot->createSprite(_speed));
		}
	}
	else
	{
		auto testshot = new ShotType();
		for (int i = 2; i > -3; i--)
		{
			_speed.x = cos(130 + (15 * i * M_PI / 180)) * 2;
			_speed.y = sin(130 + (15 * i * M_PI / 180)) * 2;
			_shotData[CAST_INT(SHOT_TYPE::DIFFUSION)].shot.emplace_back(testshot->createSprite(_speed));
		}
	}
	//_shotData[CAST_INT(SHOT_TYPE::DIFFUSION)].shot
}

void Shot::TrackingShot()
{
}
