#pragma once
#include "Character.h"

struct Jump 
{
	// �W�����v���̏���
	bool operator()(Sprite& sprite, Setting& setting);
};