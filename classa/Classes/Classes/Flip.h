#pragma once
#include "Character.h"

struct Flip
{
	// �L�����̉摜���t�ɂ��鏈��
	bool operator()(Sprite& sprite, Setting& setting);
};