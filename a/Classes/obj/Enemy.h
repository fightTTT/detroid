#pragma once
#include <tuple>
#include "cocos2d.h"

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

// アニメーションデータ　		 <plist,画像名,フレーム数 >
using EnemyAnimData = std::tuple<std::string, std::string, int>;


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

	void RunAnim(ENEM_ACT animType);

	void SetDeth(const bool dethFlag);

private:
	ENEM_ACT _actNow;		// 現在のアニメーション
	ENEM_ACT _actOld;		// 1フレーム前のアニメーション

	cocos2d::Size* _colSize;
	bool _dethFlag;

};

