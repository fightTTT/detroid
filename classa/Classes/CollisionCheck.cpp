#include "CollisionCheck.h"
#include <cmath>

bool CollisionCheck::operator()(Sprite & sprite, Setting & setting)
{
	// �`�b�v�����郌�C���[�����
	auto scene = Director::getInstance()->getRunningScene();
	auto mapdata = (TMXTiledMap*)scene->getChildByName("FollowerLayer")->getChildByName("BlocksLayer")->getChildByName("MapData");
	auto layer = mapdata->getLayer("Blocks");

	if (layer == nullptr)
	{
		log("Layer is not exist");
		return false;
	}

	// �ړ���̍��W�̏�����
	Vec2 mapPosition[] =
	{
		sprite.getPosition() + setting.collisionPoint[0] + setting.velocity,
		sprite.getPosition() + setting.collisionPoint[1] + setting.velocity,
	};

	// Y�����t�]����
	for (auto& point : mapPosition)
	{
		point.y = std::abs(point.y - layer->getContentSize().height);
	}

	// ��O����
	for (auto& point : mapPosition)
	{
		if (point.x <= 0 ||
			point.y <= 0 ||
			point.x >= layer->getContentSize().width ||
			point.y >= layer->getContentSize().height)
		{
			return false;
		}
	}

	// �Ԃ��鐧��
	auto blockOne = layer->getTileGIDAt(mapPosition[0] / layer->getMapTileSize().width);	// �Ȃ񂩂P�ɑ�����Ă�炵���ł��B
	auto blockTwo = layer->getTileGIDAt(mapPosition[1] / layer->getMapTileSize().width);
	blockOne--;
	blockTwo--;

	if (blockOne == -1 && blockTwo == -1)
	{
		return true;
	}

	if (((Character&)sprite).IsFall())
	{
 		((Character&)sprite).IsJump(false);
		((Character&)sprite).IsJumpReady(true);
		return false;
	}
	else if (((Character&)sprite).IsJump())
	{
		((Character&)sprite).IsFall(true);
		((Character&)sprite).JumpVelocity(0.0f);
		return false;
	}

	return false;
}