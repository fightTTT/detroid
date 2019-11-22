#include "Player.h"
#include "AnimationMng.h"
#include "ActCtrl.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/KeyInput.h"
#else
#include "input/TouchInput.h"
#endif

Sprite * Player::createSprite()
{
	Player *player = new Player;
	if (player&&player->init())
	{
		player->autorelease();
		return player;
	}

	delete player;
	player = nullptr; 
	return nullptr; 
}

Player::Player()
{
	_playerAnimData[static_cast<int>(PL_ACTION::IDLE)]	   = { "playerData/idle.plist" ,"player-idle-" ,4};
	_playerAnimData[static_cast<int>(PL_ACTION::RUN)]	   = { "playerData/run.plist" ,"player-run-" ,10 };
	_playerAnimData[static_cast<int>(PL_ACTION::JUMP)]	   = { "playerData/jump.plist" ,"player-jump-" ,6 };
	_playerAnimData[static_cast<int>(PL_ACTION::RUN_SHOT)] = { "playerData/run-shot.plist" ,"player-run-shot-" ,10 };
	actCtrl = new ActCtrl();
	Init();
}


Player::~Player()
{

}

void Player::Init()
{	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_animNow = PL_ACTION::IDLE;
	_animOld = _animNow;

	_animName[static_cast<int>(PL_ACTION::IDLE)]	 = "idle";
	_animName[static_cast<int>(PL_ACTION::RUN)]		 = "run";
	_animName[static_cast<int>(PL_ACTION::JUMP)]	 = "jump";
	_animName[static_cast<int>(PL_ACTION::RUN_SHOT)] = "run-shot";

	// アニメーションの登録
	for (int animType = 0; animType < static_cast<int>(PL_ACTION::MAX); animType++)
	{
		lpAnimationMng.AddAnim(_playerAnimData[animType], _animName[animType], PL_ACTION(animType));
	}

	RunAnim(_animNow);

	// 初期座標と大きさの設定
	setPosition(Vec2(300 + origin.x, visibleSize.height / 2 + origin.y));
	setScale(1.0);


	ActModule actData;
	actData.actionType = PL_ACTION::IDLE;
	actData.colOffSetPos = Vec2(-22.5f, -55.5f);
	actData.colNum = 2;
	actData.speed = Vec2(0.0f, 0.0f);
	//AddAction(actData, "idle");

	actData.actionType = PL_ACTION::JUMP;
	actData.colOffSetPos = Vec2(-22.5f, -55.5f);
	actData.colNum = 2;
	actData.speed = Vec2(0.0f, 2.0f);
	actData.keyCode = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	actData.trgType = INPUT_TRG::ON;
	actCtrl->AddAction(actData, "moveDown");

	actData.actionType = PL_ACTION::JUMP;
	actData.colOffSetPos = Vec2(-22.5f, 55.5f);
	actData.colNum = 2;
	actData.speed = Vec2(0.0f, -2.0f);
	actData.keyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
	actData.trgType = INPUT_TRG::ON;
	actCtrl->AddAction(actData, "moveUp");

	actData.actionType = PL_ACTION::RUN;
	actData.blackList.emplace_back(PL_ACTION::RUN_SHOT);
	actData.colOffSetPos = Vec2(-22.5f, -55.5f);
	actData.colNum = 3;
	actData.speed = Vec2(-3.0f, 0.0f);
	actData.keyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	actData.trgType = INPUT_TRG::ON;
	actCtrl->AddAction(actData, "moveLeft");

	actData.actionType = PL_ACTION::RUN_SHOT;
	actData.blackList.emplace_back(PL_ACTION::RUN);
	actData.colOffSetPos = Vec2(22.5f, -55.5f);
	actData.colNum = 3;
	actData.speed = Vec2(3.0f, 0.0f);
	actData.keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	actData.trgType = INPUT_TRG::ON;
	actCtrl->AddAction(actData, "moveRight");

	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_input = new KeyInput;
#else
	_input = new TouchInput;
#endif
	_input->Init(this);
	this->scheduleUpdate();
}

void Player::update(float delta)
{
	_animNow = PL_ACTION::IDLE;

	//アニメーションの切り替え
	auto animChange = [](Player* player)
	{
		if (player->_animOld != player->_animNow)
		{
			player->stopAllActions();
			player->RunAnim(player->_animNow);
		}
	};

	animChange(this);

	actCtrl->Update(*this);

	_animOld = _animNow;

	_input->Update();
}

INPUT_TRG Player::GetInputTrg(cocos2d::EventKeyboard::KeyCode keyCode)
{
	return _input->GetInputType(keyCode);
}

const std::list<PL_ACTION>& Player::ActType()
{
	return actFlag;
}

void Player::SetActType(std::list<PL_ACTION>& actTypeList)
{
	actFlag = actTypeList;
}

void Player::RunAnim(PL_ACTION animType)
{
	Animate* anim = Animate::create(AnimationCache::getInstance()->getAnimation(_animName[static_cast<int>(animType)]));
	runAction(RepeatForever::create(anim));
}
