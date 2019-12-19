#pragma once
#include "Character.h"

struct AnimationCheck
{
	bool operator()(Sprite& sprite, Setting& setting);
};