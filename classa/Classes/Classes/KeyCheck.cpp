#include "KeyCheck.h"
#include "GameScene.h"

bool KeyCheck::operator()(Sprite & sprite, Setting & setting)
{
	auto player = (Player*)&sprite;

	if (player == nullptr)
	{
		log("Player is missing or can't get data.");
		return false;
	}

	auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
	auto oprtState = gameScene->GetOprtState();

	for (int i = 1; i < static_cast<int>(INPUT_TYPE::MAX); i++)
	{
		if (setting.input == static_cast<INPUT_TYPE>(i))
		{
			if (oprtState->GetKey(setting.key, static_cast<INPUT_TYPE>(i)))
			{
				return true;
			}
		}
	}
	return false;
}
