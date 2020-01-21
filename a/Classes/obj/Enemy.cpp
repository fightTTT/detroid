#include "Enemy.h"
#include "AnimationMng.h"

USING_NS_CC;

cocos2d::Sprite * Enemy::createSprite()
{
	Enemy *enemy = new Enemy;
	if (enemy&&enemy->init())
	{
		enemy->autorelease();
		return enemy;
	}

	delete enemy;
	enemy = nullptr;
	return nullptr;
}

Enemy::Enemy()
{
	Init();
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	EnemyAnimData enemyAnimData;
	{
		enemyAnimData = { "enemyData/crab/crab-idle.plist" ,"crab-idle-" ,4 };
		lpAnimationMng.AddAnim(enemyAnimData, "crab-idle");
	}

	_actNow = ENEM_ACT::FREEZE;
	_actOld = _actNow;

	setPosition(Vec2(250 + origin.x,48));
	setScale(1.0);
	setContentSize(Size(36, 48));

	_dethFlag = false;

	RunAnim(_actNow);

	scheduleUpdate();
}

void Enemy::update(float delta)
{

}

void Enemy::RunAnim(ENEM_ACT animType)
{
	Animate* anim;

	if (animType == ENEM_ACT::FREEZE)
	{
		anim = Animate::create(AnimationCache::getInstance()->getAnimation("crab-idle"));
	}

	runAction(RepeatForever::create(anim));
}

void Enemy::SetDeth(const bool dethFlag)
{
	_dethFlag = dethFlag;
}
