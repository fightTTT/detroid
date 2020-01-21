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
//#include "Console/_DebugConOut.h"

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

	for (auto &data : _actionData)
	{
		if (CheckAct(data.second))
		{
			_actionData[data.first].actRun(sprite, data.second);

			if (((Player&)sprite).GetActType() != PL_ACTION::FALL &&
				((Player&)sprite).GetActType() != PL_ACTION::JUMP &&
				((Player&)sprite).GetActType() != PL_ACTION::JUMPING)
			{
				((Player&)sprite).SetActType(data.second.actionType);
			}

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
				// 何もしない
			}

			//TRACE("%d\n", data.second.actionType);
		}
		// 実行しているアクションとチェックリストでfalseが返されたアクションが同じだった時
		else if (((Player&)sprite).GetActType() == data.second.actionType)
		{
			// 何もしない(立ち)状態にする
			((Player&)sprite).SetActType(PL_ACTION::IDLE);
			_actionData[data.first].actRun(sprite, _actionData["idle"]);
		}
		else
		{
			// 何もしない
		}
	}

	//TRACE("%d\n", ((Player&)sprite).GetActType());
}

