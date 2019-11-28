#include <vector>
#include "collision.h"
#include "cocos2d.h"
#include "Console/_DebugConOut.h"

USING_NS_CC;

// ����(�����蔻����������L�����̍��W�A�L�����̉摜�̃I�t�Z�b�g�A�L�����̌����Ă������,�����蔻��̐�)
bool MoveCol::operator()(Sprite & sprite, ActModule & actModule)
{
	auto mapLayer = Director::getInstance()->getRunningScene()->getChildByName("MapLayer");
	auto mapData = (TMXTiledMap*)mapLayer->getChildByName("MapData");
	TMXLayer *ground = mapData->getLayer("ground");

	if (ground == nullptr)
	{
		log("ground is nullptr");
		return false;
	}

	Vec2 offset = Vec2((std::abs(actModule.colOffSetPos.x) * 2) / (actModule.colNum - 1), 
					   (std::abs(actModule.colOffSetPos.y) * 2) / (actModule.colNum - 1));

	std::vector<Vec2> colPos;

	if (actModule.speed.y != 0.0f)
	{
		for (int i = 0; i < actModule.colNum; i++)
		{
			colPos.push_back(Vec2(sprite.getPosition().x + actModule.colOffSetPos.x + (offset.x * i),
									sprite.getPosition().y + actModule.colOffSetPos.y));
		}
	}
	if (actModule.speed.x != 0.0f)
	{
		for (int i = 0; i < actModule.colNum; i++)
		{
			colPos.push_back(Vec2(sprite.getPosition().x + actModule.colOffSetPos.x,
									sprite.getPosition().y + actModule.colOffSetPos.y + (offset.y * i)));
		}
	}

	for (auto &playerPos : colPos)
	{
		playerPos = Vec2((playerPos.x + actModule.speed.x) / 48.0f,( playerPos.y - actModule.speed.y) / 48.0f);
		playerPos = Vec2(playerPos.x, ground->getLayerSize().height - playerPos.y);

		// ��ʔ͈͊O����
		if (playerPos.x > 0 && playerPos.x < ground->getLayerSize().width
			&& playerPos.y > 0 && playerPos.y < ground->getLayerSize().height)
		{
			// �}�b�v���C���[�Ƃ̓����蔻��
			if (ground->getTileGIDAt(Vec2(playerPos.x, playerPos.y)))
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