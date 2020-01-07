#include "collision.h"
#include "cocos2d.h"
#include "Console/_DebugConOut.h"
#include "Player.h"

USING_NS_CC;

// 引数(当たり判定をしたいキャラの座標、キャラの画像のオフセット、キャラの向いている方向,当たり判定の数)
bool MoveCol::operator()(Sprite & sprite, ActModule & actModule)
{
	if (actModule.colNum.x == 0 && actModule.colNum.y == 0)
	{
		return true;
	}

	auto mapLayer = Director::getInstance()->getRunningScene()->getChildByName("FollowerLayer")->getChildByName("MapLayer");
	auto mapData = (TMXTiledMap*)mapLayer->getChildByName("MapData");
	TMXLayer *ground = mapData->getLayer("ground");

	if (ground == nullptr)
	{
		log("ground is nullptr");
		return false;
	}

	// 当たり判定ごとの間隔を求める
	Vec2 offset = Vec2((std::abs(actModule.colOffsetPos.x) * 2) / (actModule.colNum.x - 1), 
					   (std::abs(actModule.colOffsetPos.y) * 2) / (actModule.colNum.y - 1));

	if (actModule.colNum.x == 0)
	{
		offset.x =0;
	}
	else if(actModule.colNum.y == 0)
	{
		offset.y = 0;
	}
	else
	{
		// 何もしない
	}
	
	for (int i = 0; i < std::max(actModule.colNum.x, actModule.colNum.y); i++)
	{
		Vec2 colPos = { 0,0 };
		colPos = Vec2(sprite.getPosition().x + actModule.colOffsetPos.x + (offset.x * i),
					  sprite.getPosition().y + actModule.colOffsetPos.y + (offset.y * i));

		if (actModule.actionType == PL_ACTION::JUMPING)
		{
			colPos = Vec2((colPos.x + ((Player&)sprite).GetJumpSpeed()) / 48.0f,
							(colPos.y + ((Player&)sprite).GetJumpSpeed()) / 48.0f);
		}
		else
		{
			colPos = Vec2((colPos.x + actModule.speed.x) / 48.0f,
				(colPos.y - actModule.speed.y) / 48.0f);
		}

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