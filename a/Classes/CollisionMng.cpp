#include "CollisionMng.h"

CollisionMng* CollisionMng::s_Instance = nullptr;

USING_NS_CC;

CollisionMng::CollisionMng()
{
}


bool CollisionMng::CheckCol(cocos2d::Sprite& sprite1, cocos2d::Sprite& sprite2)
{
	auto sprite2col = sprite2.getContentSize();

	auto sprite1Size = sprite1.getContentSize();

	if (sprite1.getPositionX() + sprite1Size.width >= sprite2.getPositionX() - sprite2col.width
	 && sprite1.getPositionX() - sprite1Size.width <= sprite2.getPositionX() + sprite2col.width
	 && sprite1.getPositionY() + sprite1Size.height >= sprite2.getPositionX() - sprite2col.height
	 && sprite1.getPositionX() - sprite1Size.height <= sprite2.getPositionX() + sprite2col.height)
	{
		return  true;
	}

	return false;
}

bool CollisionMng::CheckCol(cocos2d::Sprite & sprite)
{
	//auto mapLayer = Director::getInstance()->getRunningScene()->getChildByName("FollowerLayer")->getChildByName("MapLayer");
	//auto mapData = (TMXTiledMap*)mapLayer->getChildByName("MapData");
	//auto ground = mapData->getLayer("ground");

	//if (ground == nullptr)
	//{
	//	log("ground is nullptr");
	//	return false;
	//}

	return false;
}

CollisionMng::~CollisionMng()
{
}
