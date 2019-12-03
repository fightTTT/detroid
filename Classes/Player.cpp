#include "Player.h"
#include "AnimationMng.h"
#include "ActCtrl.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/KeyInput.h"
#else
#include "input/TouchInput.h"
#endif
#include "effect/EffectMng.h"


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

	_animNow = PL_ACTION::IDLE;
	_animOld = _animNow;

	_playerAnimData[static_cast<int>(PL_ACTION::IDLE)]	   = { "playerData/idle.plist" ,"player-idle-" ,4 };
	_playerAnimData[static_cast<int>(PL_ACTION::RUN)]	   = { "playerData/run.plist" ,"player-run-" ,10 };
	_playerAnimData[static_cast<int>(PL_ACTION::JUMP)]	   = { "playerData/jump.plist" ,"player-jump-" ,6 };
	_playerAnimData[static_cast<int>(PL_ACTION::RUN_SHOT)] = { "playerData/run-shot.plist" ,"player-run-shot-" ,10 };

	_animName[static_cast<int>(PL_ACTION::IDLE)]	 = "idle";
	_animName[static_cast<int>(PL_ACTION::RUN)]		 = "run";
	_animName[static_cast<int>(PL_ACTION::JUMP)]	 = "jump";
	_animName[static_cast<int>(PL_ACTION::RUN_SHOT)] = "run-shot";

	// アニメーションの登録
	for (int animType = 0; animType < static_cast<int>(PL_ACTION::MAX); animType++)
	{
		lpAnimationMng.AddAnim(_playerAnimData[animType], _animName[animType]);
	}

	// 初期座標と大きさの設定
	setPosition(Vec2(300 + origin.x, visibleSize.height / 2 + origin.y + 150));
	setScale(1.0);


	ActModule actData;
	// ノーマル(立ち状態)
	{
		
		actData.actionType = PL_ACTION::IDLE;
		actData.colOffSetPos = Vec2(-22.5f, -55.5f);
		actData.colNum = 2;
		actData.speed = Vec2(0.0f, 0.0f);
		_actCtrl->AddAction(actData, "idle");
	}

	// 落下
	{
		actData.actionType = PL_ACTION::IDLE;
		actData.colOffSetPos = Vec2(-22.5f, -55.5f);
		actData.colNum = 2;
		actData.speed = Vec2(0.0f, 2.0f);
		//actData.keyCode = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
		actData.trgType = INPUT_TRG::ON;
		_actCtrl->AddAction(actData, "moveDown");
	}

	// ジャンプ
	{
		actData.actionType = PL_ACTION::JUMP;
		actData.colOffSetPos = Vec2(-22.5f, 55.5f);
		actData.colNum = 2;
		actData.speed = Vec2(0.0f, -2.0f);
		actData.keyCode = EventKeyboard::KeyCode::KEY_UP_ARROW;
		actData.trgType = INPUT_TRG::ON;
		_actCtrl->AddAction(actData, "moveUp");
	}

	// 左移動
	{
		actData.actionType = PL_ACTION::RUN;
		actData.blackList.emplace_back(PL_ACTION::JUMP);
		actData.blackList.emplace_back(PL_ACTION::RUN_SHOT);
		actData.colOffSetPos = Vec2(-22.5f, -55.5f);
		actData.colNum = 3;
		actData.speed = Vec2(-3.0f, 0.0f);
		actData.keyCode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		actData.trgType = INPUT_TRG::ON;
		_actCtrl->AddAction(actData, "moveLeft");
	}

	// 右移動
	{
		actData.blackList.clear();
		actData.actionType = PL_ACTION::RUN_SHOT;
		actData.blackList.emplace_back(PL_ACTION::JUMP);
		actData.blackList.emplace_back(PL_ACTION::RUN);
		actData.colOffSetPos = Vec2(22.5f, -55.5f);
		actData.colNum = 3;
		actData.speed = Vec2(3.0f, 0.0f);
		actData.keyCode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		actData.trgType = INPUT_TRG::ON;
		_actCtrl->AddAction(actData, "moveRight");
	}

	/*lpEffectMng.Create("circle", "Laser01.efk");
	lpEffectMng.Scale("circle", 20);
	lpEffectMng.Pos("circle", getPosition());
	lpEffectMng.PlayEffect("circle", false);*/

	RunAnim(_animNow);
	
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
	/*CkBank* bank = CkBank::newBank("my_bank.ckb");
	CkSound* sound = CkSound::newBankSound(bank, "my_sound");
	sound->play();*/

	/*if (_input->GetInputType(EventKeyboard::KeyCode::KEY_0) == INPUT_TRG::ON_MOM)
	{
		_effect.try_emplace("test", std::make_unique<EffectMng>());

		_effect["test"]->AddEffect("EffectLayer");

		auto effect = efk::Effect::create("Simple_Distortion.efk");
		_effect["test"]->GetEfkEmitter().setPlayOnEnter(false);
		_effect["test"]->GetEfkEmitter().setPosition(getPosition());
		_effect["test"]->GetEfkEmitter().setScale(20);
		_effect["test"]->GetEfkEmitter().setEffect(effect);

		if (_effect["test"]->GetEfkEmitter().getPlayOnEnter())
		{
			_effect["test"]->GetEfkEmitter().setPlayOnEnter(false);
		}
		else if(!_effect["test"]->GetEfkEmitter().getPlayOnEnter())
		{
			_effect["test"]->GetEfkEmitter().setPlayOnEnter(true);
		}
	}

	if (_effect.size())
	{
		for (auto &effect : _effect)
		{
			effect.second.get()->update();
		}
	}*/

	if (_input->GetInputType(EventKeyboard::KeyCode::KEY_0) == INPUT_TRG::ON_MOM)
	{

		auto director = cocos2d::Director::getInstance();
		/*if (lpEffectMng.Create("circle", "Laser01.efk"))
		{*/
			/*lpEffectMng.AddLayer("EffectLayer", "circle");*/

		/*}
		lpEffectMng.Scale("circle", 20);
		lpEffectMng.Pos("circle", getPosition());
		lpEffectMng.PlayEffect("circle", true);*/

		auto effectLayer = director->getRunningScene()->getChildByName("EffectLayer");
		auto emmiter = (efk::EffectEmitter*)effectLayer->getChildByName("circleEffect");
		emmiter->setPlayOnEnter(true);
		emmiter->setPosition(getPosition());
	}

	lpEffectMng.update();

	//アニメーションの切り替え
	auto animChange = [](Player* player)
	{
		if (player->_animOld != player->_animNow)
		{
			player->stopAllActions();
			player->RunAnim(player->_animNow);
		}
	};

	_actCtrl->Update(*this);

	animChange(this);

	_animOld = _animNow;

	_input->Update();
}

INPUT_TRG Player::GetInputTrg(EventKeyboard::KeyCode keyCode)
{
	return _input->GetInputType(keyCode);
}

const PL_ACTION Player::GetActType()
{
	return _animNow;
}

void Player::SetActType(PL_ACTION actType)
{
	_animNow = actType;
}

void Player::RunAnim(PL_ACTION animType)
{
	Animate* anim = Animate::create(AnimationCache::getInstance()->getAnimation(_animName[static_cast<int>(animType)]));
	runAction(RepeatForever::create(anim));
}
