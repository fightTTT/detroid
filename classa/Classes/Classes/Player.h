#pragma once

#include "cocos2d.h"
#include <vector>
#include "Character.h"

enum class P_ANIMATION {
	IDLE,
	STAND,
	CLING,
	HURT,
	DUCK,
	JUMP,
	RUN,
	RUN_SHOOT,
	SHOOT_UP,
	MAX
};

USING_NS_CC;

class Player : public Character{
public:
	static Character* createPlayer();		// 全てのプレイヤーの情報が返す
	Player();
	~Player();
private:
	CREATE_FUNC(Player);						// 継承されたクラスを初期化してプレイヤーをコンストラクタする
	bool AnimationInit(void);					// プレイヤーのアニメーションデータを登録する
	void update(float delta);					// 更新制御
	void ChangeAnimation(const char*action);	// 別のアニメーションに切り替えする
};