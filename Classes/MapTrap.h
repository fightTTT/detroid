#pragma once
#include "obj/Obj.h"
#include "ActCtrl.h"

enum class TRAP_TYPE
{
	WAIT,		// �ҋ@���
	ICICLE,		// �X��
	PITFALL,	// ���Ƃ���
	MAX
};

class MapTrap:
	public Obj
{
public:
	MapTrap();
	~MapTrap();

	void Init();
	void update(float delta);

private:
	ActCtrl* actCtrl;
};

