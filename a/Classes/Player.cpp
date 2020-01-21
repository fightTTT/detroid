#include "Player.h"
#include "AnimationMng.h"
#include "ActCtrl.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "input/KeyInput.h"
#else
#include "input/TouchInput.h"
#endif
#include "effect/EffectMng.h"
#include "obj/Shot.h"
#include "Console/_DebugConOut.h"


USING_NS_CC;


std::vector<cocos2d::Sprite*> Player::_shotObj;


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
	_shot = new Shot();
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

	// アニメーション情報の登録
	{
		PlayerAnimData playerAnimData;

		playerAnimData = { "playerData/idle.plist" ,"player-idle-" ,4 };
		lpAnimationMng.AddAnim(playerAnimData, "idle");
		playerAnimData = { "playerData/jump.plist" ,"player-jump-" ,6 };
		lpAnimationMng.AddAnim(playerAnimData, "jump");
		playerAnimData = { "playerData/run.plist" ,"player-run-" ,10 };
		lpAnimationMng.AddAnim(playerAnimData, "run");
		playerAnimData = { "playerData/run-shot.plist" ,"player-run-shot-" ,10 };
		lpAnimationMng.AddAnim(playerAnimData, "run-shot");


		playerAnimData = { "playerData/shot.plist" ,"shot-" ,2};
		lpAnimationMng.AddAnim(playerAnimData, "shot");
	}

	_actNow = PL_ACTION::FALL;
	_actOld = _actNow;

	// アニメーションの登録
	//for (int animType = 0; animType < static_cast<int>(PL_ACTION::MAX); animType++)
	//{
	//	lpAnimationMng.AddAnim(_playerAnimData[animType], _animName[animType]);
	//}


	// 初期座標と大きさの設定
	setPosition(Vec2(250 + origin.x, visibleSize.height / 2 + origin.y + 200));
	setScale(1.0);

	Vec2 colSize = { 24.0f, 70.0f };	// 当たり判定の半分のサイズ

	_JumpSpeed = 0.0;

	_life = 3;
	
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
		actData.speed = { -5.0f, 0.0f };
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
		actData.speed = {5.0f, 0.0f };
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
		actData.blackList.emplace_back(PL_ACTION::RIGHT_MOVE);
		actData.blackList.emplace_back(PL_ACTION::LEFT_MOVE);
		actData.colOffsetPos = { -colSize.x, colSize.y };
		actData.colNum = { 2, 0 };
		actData.speed = { 0.0f, _JumpSpeed };
		_actCtrl->AddAction(actData, "jumping");
	}

	RunAnim(_actNow);

	lpEffectMng.AddEffect("Laser01.efk", "Laser");
	
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

	inputFlag = true;
	/*lpEffectMng.Rotate("Laser", { 0.0f,90.0f,-90.0f });
	lpEffectMng.Loop("Laser", true);
	lpEffectMng.AddLayer("Laser", "EffectLayer", getPosition(), lpEffectMng.Rotate("Laser"));*/
	}

	// Zキーでレーザービーム発射
	//if (_input->GetInputType(EventKeyboard::KeyCode::KEY_Z) == INPUT_TRG::ON_MOMENT)
	//{
	//	if (isFlippedX())
	//	{
	//		lpEffectMng.Rotate("Laser", { 0.0f,-90.0f,0.0f });
	//	}
	//	else
	//	{
	//		lpEffectMng.Rotate("Laser", { 0.0f,90.0f,0.0f });
	//	}
	//	
	//	lpEffectMng.AddLayer("Laser", "EffectLayer", getPosition(), lpEffectMng.Rotate("Laser"));
	//}
	if (isFlippedX())
	{
		int a = 0;//lpEffectMng.Rotate("Laser", { 0.0f,-90.0f,0.0f });
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

	auto deth_itr = std::remove_if(_shotObj.begin(), _shotObj.end(), [](cocos2d::Sprite* shot) 
	{
		if (shot->getName() == "dethShot")
		{
			auto action = RemoveSelf::create();
			shot->runAction(action);
			return true;
		}
		return false;
	});
	_shotObj.erase(deth_itr, _shotObj.end());

	/*auto deth_itr = std::remove_if(_shotObj.begin(), _shotObj.end(), [](Shot* shot) {return shot->CheckDeth(); });
	_shotObj.erase(deth_itr, _shotObj.end());*/
	Shooting();

	// アクションの更新
	_actCtrl->Update(*this);

	// アニメーションの更新
	animChange(this);

	// 1フレーム前のアクションを保存する
	_actOld = _actNow;

	_shot->Update(_input);

	// 入力状態の更新
	_input->Update();


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

void Player::Life(const int life)
{
	_life = life;
}

ShotArray Player::GetShotArray()
{

	return _shot->GetShotData();
}

void Player::RunAnim(PL_ACTION animType)
{
	Animate* anim;
	if (animType == PL_ACTION::JUMP ||
		animType == PL_ACTION::JUMPING ||
		animType == PL_ACTION::FALL)
	{
		anim = Animate::create(AnimationCache::getInstance()->getAnimation("jump"));
	}
	else if (animType == PL_ACTION::LEFT_MOVE ||
		animType == PL_ACTION::RIGHT_MOVE)
	{
		anim = Animate::create(AnimationCache::getInstance()->getAnimation("run"));
	}
	else if (animType == PL_ACTION::RUN_SHOT)
	{
		anim = Animate::create(AnimationCache::getInstance()->getAnimation("run-shot"));
	}
	else
	{
		anim = Animate::create(AnimationCache::getInstance()->getAnimation("idle"));
	}

	runAction(RepeatForever::create(anim));
}

bool Player::Shooting(void)
{
	/*auto deth_itr = std::remove_if(_shotObj.begin(), _shotObj.end(), [](std::shared_ptr<Obj> obj) {return obj->IsDeath(); });
	_shotObj.erase(deth_itr, _shotObj.end());*/

	//if (_input->GetInputType(EventKeyboard::KeyCode::KEY_Z) == INPUT_TRG::ON_MOMENT)
	//{
	//	/*ShotData shot;
	//	auto mapLayer = Director::getInstance()->getRunningScene()->getChildByName("FollowerLayer")->getChildByName("MapLayer");
	//	shot.shotSprite = cocos2d::Sprite::create("image/Sprites/Fx/shot/shot-1.png");
	//	shot.shotSprite->setPosition(this->getPosition());
	//	shot.shotSprite->setGlobalZOrder(99);
	//	mapLayer->addChild(shot.shotSprite,20);*/
	//	//shot.eraseFlag = false;
	//	if (isFlippedX())
	//	{
	//		if (_shotObj.size() < 2)
	//		{
	//			auto a = Shot::createSprite(this->getPosition(), -10,SHOT_TYPE::NORMAL);
	//			_shotObj.emplace_back(a);
	//		}
	//	}
	//	else
	//	{
	//		if (_shotObj.size() < 2)
	//		{
	//			auto a = Shot::createSprite(this->getPosition(), 10, SHOT_TYPE::NORMAL);
	//			_shotObj.emplace_back(a);
	//		}
	//	}
	//}

	//for (auto &shot : _shotObj)
	//{
	//	if (shot.flippedFlag)
	//	{
	//		shot.shotSprite->setPositionX(shot.shotSprite->getPositionX() - 10);
	//	}
	//	else
	//	{
	//		shot.shotSprite->setPositionX(shot.shotSprite->getPositionX() + 10);
	//	}

	//	if (abs(shot.shotSprite->getPositionX() - this->getPositionX()) > 200)
	//	{
	//		shot.eraseFlag = true;
	//	}
	//}

	//auto deth_itr = std::remove_if(_shotObj.begin(), _shotObj.end(), [](std::vector obj) 
	//{
	//	return obj->CheckDeth(); 
	//});
	//objList->erase(deth_itr, _shotObj.end());

	return true;
}