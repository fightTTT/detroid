#pragma once
#include "cocos2d.h"
#include <list>

struct ActModule;
enum class INPUT_TRG;
enum class PL_ACTION;

using actFnc = std::function<bool(cocos2d::Sprite&, ActModule&)>;

struct ActModule
{
	std::list<PL_ACTION> blackList;				// ブラックリスト
	cocos2d::EventKeyboard::KeyCode keyCode;	// 入力キー
	INPUT_TRG trgType;
	cocos2d::Vec2 speed;						// スピード
	cocos2d::Vec2 colOffsetPos;					// 当たり判定のオフセット
	cocos2d::Vec2 colNum;						// 当たり判定の数
	PL_ACTION actionType;						// アクションのタイプ
	std::list<actFnc> checkList;				// アクションのチェックリスト
	actFnc actRun;								// アクションの処理
};

class ActCtrl
{
public:
	ActCtrl();
	~ActCtrl();
	// アクションの登録
	bool AddAction(ActModule& actModule, const std::string& str);
	// アクションの切り替え、実行
	void Update(cocos2d::Sprite& sprite);
private:
	std::map<std::string, ActModule> _actionData;	// アクションのリスト
};