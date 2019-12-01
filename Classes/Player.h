#pragma once
#include <tuple>
#include <map>
#include <list>
#include <memory>
#include "Character.h"
#include "input/Input.h"


// プレイヤーアクションの種類
enum class PL_ACTION
{
	IDLE,		// 立ち状態
	RUN,		// 走る
	JUMP_FALL,		// ジャンプ
	RUN_SHOT,	// 走りながら弾発射
	MAX
};

class ActCtrl;
class EffectMng;

// アニメーションデータ　		 <plist,画像名,フレーム数 >
using PlayerAnimData = std::tuple<std::string, std::string, int>;

using EffectData = std::unique_ptr<EffectMng>;

class Player :
	public Sprite
{
public:
	// プレイヤークラスを生成する
	static Sprite *createSprite();
	Player();
	~Player();
	void Init();
	void update(float delta);

	// keyのトリガー情報を取得する関数
	INPUT_TRG GetInputTrg(cocos2d::EventKeyboard::KeyCode keyCode);
	const PL_ACTION GetActType();
	void SetActType(PL_ACTION actType);
	cocos2d::Layer& GetEffect();
private:
	std::map<std::string, EffectData> _effect;

	Input* _input;

	Layer* layer;

	std::string _animName[static_cast<int>(PL_ACTION::MAX)];
	PlayerAnimData _playerAnimData[static_cast<int>(PL_ACTION::MAX)];

	std::list<PL_ACTION> actFlag;

	ActCtrl* actCtrl;

	PL_ACTION _animNow;					// 現在のアニメーション
	PL_ACTION _animOld;					// 1フレーム前のアニメーション
	// アニメーションの実行
	void RunAnim(PL_ACTION animType);
};
