#include "Enemy.h"


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
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::update(float delta)
{
}
