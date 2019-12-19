#include "Collision.h"
#include <vector>
#include <algorithm>

bool BlockCheck(Node * node, float speed, int dir)
{
	// �`�b�v�����郌�C���[�����
	auto scene = Director::getInstance()->getRunningScene();
	auto mapdata = (TMXTiledMap*)scene->getChildByName("GameScene")->getChildByName("BlocksLayer")->getChildByName("MapData");
	auto layer = mapdata->getLayer("Blocks");

	Vec2 pointOne;
	Vec2 pointTwo;

	// �ړ���̍��W�̏�����
	auto movePos = node->getPosition();
	if (dir == 1)
	{
		pointOne = Vec2(movePos.x + 45.0f / 2.0f, layer->getContentSize().height - (movePos.y - 111.0f / 2.0f));
		pointTwo = Vec2(movePos.x + 45.0f / 2.0f, layer->getContentSize().height - (movePos.y + 111.0f / 2.0f));

		pointOne.x += speed;
		pointTwo.x += speed;
	}
	else if (dir == 2)
	{
		pointOne = Vec2(movePos.x, layer->getContentSize().height - (movePos.y - 111.0f / 2.0f));
		pointTwo = Vec2(movePos.x, layer->getContentSize().height - (movePos.y - 111.0f / 2.0f));

		pointOne.y += speed;
		pointTwo.y += speed;
	}
	else if (dir == 3)
	{
		pointOne = Vec2(movePos.x - 45.0f / 2.0f, layer->getContentSize().height - (movePos.y - 111.0f / 2.0f));
		pointTwo = Vec2(movePos.x - 45.0f / 2.0f, layer->getContentSize().height - (movePos.y + 111.0f / 2.0f));

		pointOne.x -= speed;
		pointTwo.x -= speed;
	}
	else if (dir == 4)
	{
		pointOne = Vec2(movePos.x + 45.0f / 2.0f, layer->getContentSize().height - (movePos.y + 111.0f / 2.0f));
		pointTwo = Vec2(movePos.x - 45.0f / 2.0f, layer->getContentSize().height - (movePos.y + 111.0f / 2.0f));

		pointOne.y -= speed;
		pointTwo.y -= speed;
	}

	if (pointTwo.y >= layer->getContentSize().height || pointTwo.y <= 0)
	{
		return true;
	}
	
	// �Ԃ��鐧��
	auto blockOne = layer->getTileGIDAt(pointOne / layer->getMapTileSize().width);	// �Ȃ񂩂P�ɑ�����Ă�炵���ł��B
	auto blockTwo = layer->getTileGIDAt(pointTwo / layer->getMapTileSize().width);
	blockOne--;
	blockTwo--;
	//log("%f,%f,%d", movePos.x, movePos.y, blockTwo);
	if (blockOne == 219 || blockTwo == 219)
	{
		return false;
	}

	if (blockOne == -1 && blockTwo == -1)
	{
		return false;
	}
	return true;
}

bool BlockCheck(Vec2 pos)
{
	// �u���b�N�����郌�C���[�����
	auto scene = Director::getInstance()->getRunningScene();
	auto mapdata = (TMXTiledMap*)scene->getChildByName("GameScene")->getChildByName("BlocksLayer")->getChildByName("MapData");
	auto layer = mapdata->getLayer("Blocks");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	pos.y = visibleSize.height - pos.y;

	if (pos.x <= 0.0f || pos.y <= 0.0f || 
		pos.x >= visibleSize.width || pos.y >= visibleSize.height)
	{
		return true;
	}

	// �u���b�N�̃`�F�b�N
	auto block = layer->getTileGIDAt(pos / layer->getMapTileSize().width);
	if (block != 0)
	{
		return true;
	}
	return false;
}

bool BlockCheck(std::vector<Vec2> pos)
{
	// �u���b�N�����郌�C���[�����
	auto scene = Director::getInstance()->getRunningScene();
	auto mapdata = (TMXTiledMap*)scene->getChildByName("GameScene")->getChildByName("BlocksLayer")->getChildByName("MapData");
	auto layer = mapdata->getLayer("Blocks");

	// Y���W���t�]����
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < pos.size(); i++)
	{
		pos[i].y = visibleSize.height - pos[i].y;
	}

	// ������̔���
	for (auto &pointPos : pos)
	{
		// ��O�����Ɖ�ʊO�ɏo�Ȃ��悤�ɂ���
		if (pointPos.x <= 0.0f || pointPos.y <= 0.0f ||
			pointPos.x >= visibleSize.width || pointPos.y >= visibleSize.height)
		{
			return true;
		}

//		�e�X�g�R�[�h ( ���Ə��� )
		if (layer->getTileGIDAt(pointPos / layer->getMapTileSize().width) == 219 + 1)
		{
			return false;
		}

		if (layer->getTileGIDAt(pointPos / layer->getMapTileSize().width) != 0)
		{
			return true;
		}
	}
	return false;
}

bool SlopeCheck(Node * node, float speed, int dir)
{
	auto scene = Director::getInstance()->getRunningScene();
	auto mapdata = (TMXTiledMap*)scene->getChildByName("GameScene")->getChildByName("BlocksLayer")->getChildByName("MapData");
	auto layer = mapdata->getLayer("Blocks");

	auto movePos = node->getPosition();
	//movePos.x += speed;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto offset = Vec2(movePos.x, visibleSize.height - (movePos.y - 111.0f / 2.0f));
	auto selectedBlock = offset / layer->getMapTileSize().width;

	if (layer->getTileGIDAt(selectedBlock) == 219 + 1)
	{
		auto block = layer->getTileAt(Vec2(4.0f, 9.0f));
		auto hitPos = Vec2(
			(offset.x - block->getPositionX()) / layer->getMapTileSize().width,
			(offset.y - block->getPositionY() + block->getContentSize().height) / layer->getMapTileSize().width);

		// �v���C���[�̈ʒu�ł̃u���b�N�̍������Z�o
		auto blockHight = block->getPositionY() + block->getContentSize().height - (1.0f- hitPos.x) * layer->getMapTileSize().width;

		if (offset.x >= blockHight)
		{
			// �ړ��ʂ�␳����
			node->setPositionY(blockHight + 111.0f/ 2.0f + speed);
			return true;
		}
	}
	return false;
}