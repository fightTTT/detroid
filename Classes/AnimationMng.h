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

	// �A�j���[�V�����ǉ�
	void AddAnim(PlayerAnimData& animData, std::string animName);

	~AnimationMng();
private:
	AnimationMng();

	static AnimationMng *s_Instance;

};
