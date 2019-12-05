#include "ActCtrl.h"
#include "Player.h"
#include "input/KeyInput.h"
#include "FallAct.h"
#include "JumpAct.h"
#include "jumpingAct.h"
#include "MoveLR.h"
#include "KeyCheck.h"
#include "BlackWhiteCheck.h"
#include "collision.h"

ActCtrl::ActCtrl()
{
}

ActCtrl::~ActCtrl()
{
}

bool ActCtrl::AddAction(ActModule & actModule, std::string str)
{
	if (str == "idle")
	{
		_actionData.insert(std::make_pair(str,actModule));
		//_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = MoveLR();

		return true;
	}

	if (str == "jumping")
	{
		_actionData.insert(std::make_pair(str, actModule));
		_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = JumpingAct();

		return true;
	}

	if (str == "moveUp")
	{
		_actionData.insert(std::make_pair(str, actModule));
		_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = JumpAct();

		return true;
	}

	if (str == "moveDown")
	{
		_actionData.insert(std::make_pair(str, actModule));
		//_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = FallAct();

		return true;
	}

	if (str == "moveLeft" || str == "moveRight")
	{
		_actionData.insert(std::make_pair(str, actModule));
		_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = MoveLR();

		return true;
	}

	return false;
}

void ActCtrl::Update(cocos2d::Sprite& sprite)
{
	auto CheckAct = [&](ActModule actData)
	{
		for (auto check : actData.checkList)
		{
			if (!check(sprite, actData))
			{
				return false;
			}
		}

		return true;
	};

	auto CheckFlip = [&](EventKeyboard::KeyCode keyCode)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			return false;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			return true;
		}

		return sprite.isFlippedX();
	};

	bool jumpFlag = false;
	bool idleFlag = true;
	for (auto &data : _actionData)
	{
		if (CheckAct(data.second))
		{
			if (data.first == "idle")
			{
				continue;
			}

			if (data.second.actionType == PL_ACTION::JUMPING)
			{
				if (((Player&)sprite).GetJumpSpeed() <= 0)
				{
					//data.second.speed.y = 10.0f;
					continue;
				}
				jumpFlag = true;
			}
			else if (data.second.actionType == PL_ACTION::JUMP)
			{
				jumpFlag = true;
			}
			else
			{
				// ‰½‚à‚µ‚È‚¢
			}

			((Player&)sprite).SetActType(data.second.actionType);
			_actionData[data.first].actRun(sprite, data.second);
			sprite.setFlippedX(CheckFlip(data.second.keyCode));
			idleFlag = false;
		}
	}

	if (!jumpFlag)
	{
		((Player&)sprite).SetJumpSpeed(0);
	}


	if (idleFlag)
	{
		_actionData["idle"].actRun(sprite, _actionData["idle"]);
		((Player&)sprite).SetActType(PL_ACTION::IDLE);
	}
}

char ActCtrl::GetActKeyCode(std::string actName)
{
	return static_cast<char>(_actionData[actName].keyCode);
}

