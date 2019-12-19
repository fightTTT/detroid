#include "Player.h"
#include "AnimationMng.h"
#include "ActCtrl.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/KeyInput.h"
#else
#include "input/TouchInput.h"
#endif
#include "effect/EffectMng.h"

USING_NS_CC;

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
	_actCtrl = new ActCtrl();
	Init();
}

Player::~Player()
{
	delete _input;
	delete _actCtrl;

}

void Player::Init()
{	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::array<PlayerAnimData, static_cast<int>(PL_ACTION::MAX)> _playerAnimData;

	_actNow = PL_ACTION::FALL;
	_actOld = _actNow;
	// アニメーション情報の登録
	_playerAnimData[static_cast<int>(PL_ACTION::IDLE)]	    = { "playerData/idle.plist" ,"player-idle-" ,4 };
	_playerAnimData[static_cast<int>(PL_ACTION::FALL)]	    = { "playerData/jump.plist" ,"player-jump-" ,6 };
	_playerAnimData[static_cast<int>(PL_ACTION::RIGHT_MOVE)]= { "playerData/run.plist" ,"player-run-" ,10 };
	_playerAnimData[static_cast<int>(PL_ACTION::LEFT_MOVE)] = { "playerData/run.plist" ,"player-run-" ,10 };
	_playerAnimData[static_cast<int>(PL_ACTION::JUMP)]	    = { "playerData/jump.plist" ,"player-jump-" ,6 };
	_playerAnimData[static_cast<int>(PL_ACTION::JUMPING)]	= { "playerData/jump.plist" ,"player-jump-" ,6 };
	_playerAnimData[static_cast<int>(PL_ACTION::RUN_SHOT)]  = { "playerData/run-shot.plist" ,"player-run-shot-" ,10 };

	// アニメーション名の登録
	_animName[static_cast<int>(PL_ACTION::IDLE)]		= "idle";
	_animName[static_cast<int>(PL_ACTION::FALL)]		= "jump";
	_animName[static_cast<int>(PL_ACTION::RIGHT_MOVE)]	= "run";
	_animName[static_cast<int>(PL_ACTION::LEFT_MOVE)]	= "run";
	_animName[static_cast<int>(PL_ACTION::JUMP)]		= "jump";
	_animName[static_cast<int>(PL_ACTION::JUMPING)]		= "jump";
	_animName[static_cast<int>(PL_ACTION::RUN_SHOT)]	= "run-shot";

	// アニメーションの登録
	for (int animType = 0; animType < static_cast<int>(PL_ACTION::MAX); animType++)
	{
		lpAnimationMng.AddAnim(_playerAnimData[animType], _animName[animType]);
	}

	// 初期座標と大きさの設定
	setPosition(Vec2(300 + origin.x, visibleSize.height / 2 + origin.y + 200));
	setScale(1.0);

	Vec2 colSize = { 24.0f, 70.0f };	// 当たり判定の半分のサイズ

	_JumpSpeed = 0.0;
	
	// ノーマル(立ち状態)
	{
		ActModule actData;
		actData.actionType = PL_ACTION::IDLE;
		actData.blackList.emplace_back(PL_ACTION::JUMP);
		actData.blackList.emplace_back(PL_ACTION::JUMPING);
		actData.blackList.emplace_back(PL_ACTION::LEFT_MOVE);
		actData.blackList.emplace_back(PL_ACTION::RIGHT_MOVE);
		actData.blackList.emplace_back(PL_ACTION::RUN_SHOT);
		actData.blackList.emplace_back(PL_ACTION::FALL);
		actData.colNum = { 0,0 };
		actData.speed = { 0.0f, 0.0f };
		_actCtrl->AddAction(actData, "idle");
	}

	// 左移動
	{
		ActModule actData;
		actData.actionType = PL_ACTION::RIGHT_MOVE;
		actData.blackList.emplace_back(PL_ACTION::LEFT_MOVE);
		actData.colOffsetPos = { -colSize.x, -colSize.y };
		actData.colNum = { 0,5 };
		actData.speed = { -3.0f, 0.0f };
		actData.keyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		actData.trgType = INPUT_TRG::ON;
		_actCtrl->AddAction(actData, "moveLeft");
	}

	// 右移動
	{
		ActModule actData;
		actData.actionType = PL_ACTION::LEFT_MOVE;
		actData.blackList.emplace_back(PL_ACTION::RIGHT_MOVE);
		actData.colOffsetPos = { colSize.x, -colSize.y };
		actData.colNum = { 0,5 };
		actData.speed = { 3.0f, 0.0f };
		actData.keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		actData.trgType = INPUT_TRG::ON;
		_actCtrl->AddAction(actData, "moveRight");
	}

	// 落下
	{
		ActModule actData;
		actData.actionType = PL_ACTION::FALL;
		actData.blackList.emplace_back(PL_ACTION::JUMPING);
		actData.colOffsetPos = { -colSize.x, -colSize.y };
		actData.colNum = { 2, 0 };
		actData.speed = { 0.0f, 2.0f };
		actData.keyCode = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
		actData.trgType = INPUT_TRG::OFF;
		_actCtrl->AddAction(actData, "moveDown");
	}

	// ジャンプ
	{
		ActModule actData;
		actData.actionType = PL_ACTION::JUMP;
		actData.blackList.emplace_back(PL_ACTION::FALL);
		actData.blackList.emplace_back(PL_ACTION::JUMPING);
		/*actData.blackList.emplace_back(PL_ACTION::RIGHT_MOVE);
		actData.blackList.emplace_back(PL_ACTION::LEFT_MOVE);*/
		actData.colOffsetPos = { -colSize.x, colSize.y };
		actData.colNum = { 2,0 };
		actData.speed = Vec2(0.0f, 10.0f);
		actData.keyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
		actData.trgType = INPUT_TRG::ON_MOMENT;
		_actCtrl->AddAction(actData, "moveUp");
	}

	// ジャンプ中
	{
		ActModule actData;
		actData.actionType = PL_ACTION::JUMPING;
		actData.blackList.emplace_back(PL_ACTION::FALL);
		/*actData.blackList.emplace_back(PL_ACTION::RIGHT_MOVE);
		actData.blackList.emplace_back(PL_ACTION::LEFT_MOVE);*/
		actData.colOffsetPos = { -colSize.x, colSize.y };
		actData.colNum = { 2, 0 };
		actData.speed = { 0.0f, 10.0f };
		//actData.trgType = INPUT_TRG::ON;
		_actCtrl->AddAction(actData, "jumping");
	}

	RunAnim(_actNow);

	this->scheduleUpdate();
}

void Player::update(float delta)
{
	static bool inputFlag = false;

	if (!inputFlag)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_input = new KeyInput;
#else
	_input = new TouchInput;
#endif
	auto layer = Director::getInstance()->getRunningScene()->getChildByName("MapLayer");
	_input->Init(this, (Layer*)layer);
	}

	if (_input->GetInputType(EventKeyboard::KeyCode::KEY_Z) == INPUT_TRG::ON_MOMENT)
	{
		lpEffectMng.Create("Laser01.efk");
		lpEffectMng.Scale(20);
		lpEffectMng.Pos(getPosition());
		lpEffectMng.PlayEffect(true);
		lpEffectMng.Rotate({ 0.0f,90.0f,0.0f });
		if (isFlippedX())
		{
			lpEffectMng.Rotate({ 0.0f,-90.0f,0.0f });
		}
		lpEffectMng.AddLayer("EffectLayer");
	}

	if (_actNow == PL_ACTION::JUMP)
	{
		lpEffectMng.Create("Laser01.efk");
		lpEffectMng.Scale(20);
		lpEffectMng.Pos(getPosition());
		lpEffectMng.PlayEffect(true);
		lpEffectMng.Rotate({ 0.0f,90.0f,90.0f });
		lpEffectMng.AddLayer("EffectLayer");
	}

	lpEffectMng.update();

	//アニメーションの切り替え
	auto animChange = [](Player* player)
	{
		if (player->_actOld != player->_actNow)
		{
			player->stopAllActions();
			player->RunAnim(player->_actNow);
		}
	};

	_actCtrl->Update(*this);
	animChange(this);
	_actOld = _actNow;
	_input->Update();

	inputFlag = true;
}

INPUT_TRG Player::GetInputTrg(EventKeyboard::KeyCode keyCode)
{
	return _input->GetInputType(keyCode);
}

const PL_ACTION Player::GetActType()
{
	return _actNow;
}

void Player::SetActType(PL_ACTION actType)
{
	_actNow = actType;
}

const float Player::GetJumpSpeed()
{
	return _JumpSpeed;
}

void Player::SetJumpSpeed(float jumpSpeed)
{
	_JumpSpeed = jumpSpeed;
}

void Player::RunAnim(PL_ACTION animType)
{
	Animate* anim = Animate::create(AnimationCache::getInstance()->getAnimation(_animName[static_cast<int>(animType)]));
	runAction(RepeatForever::create(anim));
}
