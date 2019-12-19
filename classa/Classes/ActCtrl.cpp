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
#include "Console/_DebugConOut.h"

ActCtrl::ActCtrl()
{
}

ActCtrl::~ActCtrl()
{
}

bool ActCtrl::AddAction(ActModule & actModule,const std::string& str)
{
	if (str == "idle")
	{
		_actionData.emplace(str, actModule);
		//_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = MoveLR();

		return true;
	}

	

	

	if (str == "moveLeft" || str == "moveRight")
	{
		_actionData.emplace(str, actModule);
		_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = MoveLR();

		return true;
	}

	if (str == "moveDown")
	{
		_actionData.emplace(str, actModule);
		//_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = FallAct();

		return true;
	}

	if (str == "moveUp")
	{
		_actionData.emplace(str, actModule);
		_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = JumpAct();

		return true;
	}

	if (str == "jumping")
	{
		_actionData.emplace(str, actModule);
		//_actionData[str].checkList.emplace_back(KeyCheck());
		_actionData[str].checkList.emplace_back(BlackWhiteCheck());
		_actionData[str].checkList.emplace_back(MoveCol());
		_actionData[str].actRun = JumpingAct();

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
	bool jumpFlag = false;
	for (auto &data : _actionData)
	{
		if (CheckAct(data.second))
		{
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

			if (data.first == "moveRight")
			{
				sprite.setFlippedX(false);
			}
			else if (data.first == "moveLeft")
			{
				sprite.setFlippedX(true);
			}
			else
			{
				// ‰½‚à‚µ‚È‚¢
			}

			TRACE("%d", data.second.actionType);
		}
		else if (data.second.actionType == PL_ACTION::IDLE)
		{
			((Player&)sprite).SetActType(data.second.actionType);
			_actionData[data.first].actRun(sprite, data.second);
		}
		else
		{
			// ‰½‚à‚µ‚È‚¢
		}
	}

	if (!jumpFlag)
	{
		((Player&)sprite).SetJumpSpeed(0);
	}

	//TRACE("%d", ((Player&)sprite).GetActType());
	
}

