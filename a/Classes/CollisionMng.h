#pragma once
#include "cocos2d.h"

#define lpCollisionMng CollisionMng::GetInstance()

class CollisionMng
{
public:

	static CollisionMng &GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new CollisionMng;
		}
		return *s_Instance;
	}

	bool CheckCol(cocos2d::Sprite& sprite1, cocos2d::Sprite& sprite2);
	bool CheckCol(cocos2d::Sprite& sprite);

	~CollisionMng();
private:
	CollisionMng();

	static CollisionMng *s_Instance;
};

