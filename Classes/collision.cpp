#include <vector>
#include "collision.h"
#include "cocos2d.h"
#include "Console/_DebugConOut.h"

USING_NS_CC;

// 引数(当たり判定をしたいキャラの座標、キャラの画像のオフセット、キャラの向いている方向,当たり判定の数)
bool MoveCol::operator()(Sprite & sprite, ActModule & actModule)
{
	if (actModule.colNum == 0)
	{
		return true;
	}

	auto mapLayer = Director::getInstance()->getRunningScene()->getChildByName("MapLayer");
	auto mapData = (TMXTiledMap*)mapLayer->getChildByName("MapData");
	TMXLayer *ground = mapData->getLayer("ground");

	if (ground == nullptr)
	{
		log("ground is nullptr");
		return false;
	}

	// 当たり判定ごとの間隔を求める
	Vec2 offset = Vec2((std::abs(actModule.colOffSetPos.x) * 2) / (actModule.colNum - 1), 
					   (std::abs(actModule.colOffSetPos.y) * 2) / (actModule.colNum - 1));

	std::vector<Vec2> collisionPos;	// 当たり判定の座標

	if (actModule.speed.y != 0.0f)
	{
		for (int i = 0; i < actModule.colNum; i++)
		{
			collisionPos.push_back(Vec2(sprite.getPosition().x + actModule.colOffSetPos.x + (offset.x * i),
									sprite.getPosition().y + actModule.colOffSetPos.y));
		}
	}

	if (actModule.speed.x != 0.0f)
	{
		for (int i = 0; i < actModule.colNum; i++)
		{
			collisionPos.push_back(Vec2(sprite.getPosition().x + actModule.colOffSetPos.x,
									sprite.getPosition().y + actModule.colOffSetPos.y + (offset.y * i)));
		}
	}

	for (auto &colPos : collisionPos)
	{
		colPos = Vec2((colPos.x + actModule.speed.x) / 48.0f,
					 ( colPos.y - actModule.speed.y) / 48.0f);
		colPos = Vec2(colPos.x, ground->getLayerSize().height - colPos.y);

		// 画面範囲外制御
		if (colPos.x > 0 && colPos.x < ground->getLayerSize().width
			&& colPos.y > 0 && colPos.y < ground->getLayerSize().height)
		{
			// マップレイヤーとの当たり判定
			if (ground->getTileGIDAt(Vec2(colPos.x, colPos.y)))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}