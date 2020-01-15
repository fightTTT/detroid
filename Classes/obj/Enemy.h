#pragma once
#include "cocos2d.h"
#include "ActCtrl.h"

enum class ENEM_ACT
{
	NONE,
	FREEZE,		// 立ち状態(氷結)
	MELT,		// 立ち状態(溶けた)
	RIGHT_MOVE, // 右移動
	LEFT_MOVE,	// 左移動
	FALL,		// 落下する直前
	FALLING,	// 落下中
	JUMP,		// ジャンプする直前
	JUMPING,	// ジャンプ中
	ATTACK,		// 敵ごとの固有攻撃
	MAX
};

class Enemy:
	public cocos2d::Sprite
{
public:
	// プレイヤークラスを生成する
	static cocos2d::Sprite *createSprite();
	Enemy();
	~Enemy();

	void Init();
	void update(float delta);

private:
	ActCtrl* _actCtrl;		// アクションを管理

};

