#pragma once
#include "cocos2d.h"

class ActCtrl;

class Obj
{
public:
	Obj() :life(1) {}
	Obj(int l) :life(l){}
	virtual ~Obj();

	// オブジェクトのライフを取得する
	const int Life() { return life; };
	//// ライフをセットする
	//void Life(const int life);

protected:
	ActCtrl* _actCtrl;		// アクションを管理

	const int life;		// オブジェクトのライフ

};

