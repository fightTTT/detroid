#pragma once
#include "Character.h"

struct AnimationChanger
{
	// �L�����̃A�j���[�V������ς��鏈��
	bool operator()(Sprite& sprite, Setting& setting);
};