#pragma once
#include <tuple>
#include "Player.h"

#define lpAnimationMng AnimationMng::GetInstance()

class AnimationMng
{
public:

	static AnimationMng &GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new AnimationMng;
		}
		return *s_Instance;
	}

	void AddAnim(PlayerAnimData& animData, std::string animName, PL_ACTION animType);

	~AnimationMng();
private:
	AnimationMng();

	static AnimationMng *s_Instance;

	//cocos2d::FiniteTimeAction* playerAnim[static_cast<int>(PL_ACTION::MAX)];
};
