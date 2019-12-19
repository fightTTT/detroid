#include "Player.h"
#include "Fall.h"
#include "MoveLR.h"
#include "CollisionCheck.h"
#include "Jump.h"
#include "JumpTrg.h"
#include "AnimationChanger.h"
#include "Flip.h"
#include "EffekseerManager.h"
#include "GameScene.h"

#define ANI(action) RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(action)))

Character * Player::createPlayer()
{
	return Player::create();
}

Player::Player()
{
	this->setName("player");
	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	// アニメーションの初期化
	AnimationInit();

	this->runAction(ANI("idle"));
	_currentAnimation = "idle";

	// 毎フレームの更新
	this->scheduleUpdate();

	Setting fall;
	fall.AddFunction(Fall());
	fall.collisionPoint[0] = Vec2(-45.0f / 2.0f, -111.0f / 2.0f);
	fall.collisionPoint[1] = Vec2(45.0f / 2.0f, -111.0f / 2.0f);
	fall.velocity = Vec2(0.0f, -5.0f);
	fall.AddCheck(CollisionCheck());
	fall.animation = "idle";
	AddToUpdate(fall);

	Setting moveR;
	moveR.input = INPUT_TYPE::DOWN;
	moveR.AddFunction(MoveLR());
	moveR.key = EventKeyboard::KeyCode::KEY_D;
	moveR.velocity = Vec2(5.0f, 0.0f);
	moveR.collisionPoint[0] = Vec2(45.0f / 2.0f, 111.0f / 2.0f);
	moveR.collisionPoint[1] = Vec2(45.0f / 2.0f, -111.0f / 2.0f);
	moveR.AddCheck(CollisionCheck());
	moveR.flip = false;
	moveR.AddFunction(Flip());
	moveR.animation = "run";
	AddToUpdate(moveR);

	Setting moveL;
	moveL.input = INPUT_TYPE::DOWN;
	moveL.AddFunction(MoveLR());
	moveL.key = EventKeyboard::KeyCode::KEY_A;
	moveL.velocity = Vec2(-5.0f, 0.0f);
	moveL.collisionPoint[0] = Vec2(-45.0f / 2.0f, 111.0f / 2.0f);
	moveL.collisionPoint[1] = Vec2(-45.0f / 2.0f, -111.0f / 2.0f);
	moveL.AddCheck(CollisionCheck());
	moveL.flip = true;
	moveL.AddFunction(Flip());
	moveL.animation = "run";
	AddToUpdate(moveL);

	Setting jump;
	jump.input = INPUT_TYPE::DOWN_MOMENT;
	jump.key = EventKeyboard::KeyCode::KEY_SPACE;
	jump.velocity = Vec2(0.0f, 60.0f);
	jump.AddFunction(JumpTrg());
	AddToUpdate(jump);

	Setting jumping;
	jumping.AddFunction(Jump());
	jumping.animation = "jump";
	AddToUpdate(jumping);
}

Player::~Player()
{
}

bool Player::AnimationInit(void)
{
	const char *action[] = { "idle","stand","cling","hurt","duck","jump","run","run-shot","shoot-up" };
	const int aniFrame[] = { 4,3,1,2,1,6,10,10,1 };

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player/player.plist");

	for (int i = 0; i < sizeof(action) / sizeof(char*); i++)
	{
		auto animation = Animation::create();

		for (int j = 1; j <= aniFrame[i]; j++)
		{
			__String* str = nullptr;
			if (aniFrame[i] != 1)
			{
				str = __String::createWithFormat("player-%s-%d.png", action[i], j);
			}
			else
			{
				str = __String::createWithFormat("player-%s.png", action[i]);
			}

			auto currentFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
			currentFrame->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			animation->addSpriteFrame(currentFrame);
		}

		animation->setDelayPerUnit(1.0f / 15.0f);
		animation->setRestoreOriginalFrame(true);

		AnimationCache::getInstance()->addAnimation(animation, action[i]);
	}
	return true;
}

void Player::update(float delat)
{
	auto checkAll = [&](Setting& action)
	{
		for (auto& check : action.checkList)
		{
			if (!check(*this, action))
			{
				return false;
			}
		}
		return true;
	};

	for (auto& action : _update)
	{
		if (checkAll(action))
		{
			for (auto & function : action.functionList)
			{
				function(*this, action);
			}
		}
	}

	auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
	auto oprtState = gameScene->GetOprtState();

	if (oprtState->GetKeyDown(EventKeyboard::KeyCode::KEY_F))
	{
		FXManager::Instace().CreateEffect("Laser01.efk", this->getPosition(),this->isFlippedX());
	}

	oprtState->Update();
}

void Player::ChangeAnimation(const char *action)
{
	this->stopAllActions();

	if (AnimationCache::getInstance()->getAnimation(action) == nullptr)
	{
		log("Animation %s is missing or not exisit", action);
		return;
	}

	this->runAction (ANI(action));
}