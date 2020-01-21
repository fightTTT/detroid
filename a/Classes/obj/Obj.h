#pragma once
#include "cocos2d.h"

enum class OBJ_TYPE
{
	PLAYER,
	ENEMY,
	TRAP,
	MAX
};

class ActCtrl;

class Obj:
	public cocos2d::Sprite
{
public:
	Obj() :life(1) {}
	Obj(int l) :life(l){}
	virtual ~Obj();

	virtual void Init() = 0;
	virtual void update(float delta) = 0;

	// オブジェクトのライフを取得する
	const int Life() { return life; };
	//// ライフをセットする
	//void Life(const int life);

	const bool IsDeath() { return _death; };

protected:
	ActCtrl* _actCtrl;	// アクションを管理

	const int life;		// オブジェクトのライフ

	bool _death;

	int _speed;
};

