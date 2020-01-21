#pragma once
#include <vector>
#include <array>
#include "obj/Obj.h"
#include "cocos2d.h"
#include "ShotType.h"
#include "input/KeyInput.h"

#define CAST_INT(X)	static_cast<int>(X)

enum class SHOT_TYPE
{
	NORMAL,
	DIFFUSION,
	TRACKING,
	MAX
};

struct ShotData
{
	SHOT_TYPE shotType;
	cocos2d::Vec2 vel;
	std::vector<cocos2d::Sprite*> shot;
};

using ShotArray = std::array <ShotData, static_cast<int>(SHOT_TYPE::MAX)>;

class Shot
{
public:
	static cocos2d::Sprite *createSprite(cocos2d::Vec2 pos, cocos2d::Vec2& speed, SHOT_TYPE shotType);
	Shot();
	Shot(cocos2d::Vec2& pos,cocos2d::Vec2& speed, SHOT_TYPE shotType);
	~Shot();
	void Init();
	void Update(Input* input);
	const bool CheckDeth();
	const cocos2d::Vec2& GetColSize();
	ShotArray GetShotData();

private:

	void NormalShot();			// í èÌíe
	void DiffusionShot();		// ägéUíe
	void TrackingShot();		// í«îˆíe
	
	cocos2d::Vec2 _speed;
	bool dethFlag;
	cocos2d::Vec2 _colSize;
	SHOT_TYPE _shotType;

	ShotArray _shotData;
};
