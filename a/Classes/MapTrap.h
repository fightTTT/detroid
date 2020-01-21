#pragma once
#include "obj/Obj.h"
#include "ActCtrl.h"

enum class TRAP_TYPE
{
	WAIT,		// ‘Ò‹@ó‘Ô
	ICICLE,		// •X’Œ
	PITFALL,	// —‚Æ‚µŒŠ
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

