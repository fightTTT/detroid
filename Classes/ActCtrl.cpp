#include "ActCtrl.h"
#include "Player.h"
#include "input/KeyInput.h"
#include "FallAct.h"
#include "JumpAct.h"
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
		_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = MoveLR();

		return true;
	}

	if (str == "moveDown")
	{
		_actionData.insert(std::make_pair(str, actModule));
		_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = FallAct();

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

	bool idleFlag = true;
	for (auto &data : _actionData)
	{
		if (CheckAct(data.second))
		{
			_actionData[data.first].actRun(sprite, data.second);
			((Player&)sprite).SetActType(data.second.actionType);
			idleFlag = false;
		}
	}

	if (idleFlag)
	{
		((Player&)sprite).SetActType(PL_ACTION::IDLE);
	}
}
