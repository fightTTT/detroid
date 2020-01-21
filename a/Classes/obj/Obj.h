#pragma once
#include "cocos2d.h"

enum class OBJ_TYPE
{
	PLAYER,
	ENEMY,
	TRAP,
	MAX
};

class ActCtrl;

class Obj:
	public cocos2d::Sprite
{
public:
	Obj() :life(1) {}
	Obj(int l) :life(l){}
	virtual ~Obj();

	virtual void Init() = 0;
	virtual void update(float delta) = 0;

	// �I�u�W�F�N�g�̃��C�t���擾����
	const int Life() { return life; };
	//// ���C�t���Z�b�g����
	//void Life(const int life);

	const bool IsDeath() { return _death; };

protected:
	ActCtrl* _actCtrl;	// �A�N�V�������Ǘ�

	const int life;		// �I�u�W�F�N�g�̃��C�t

	bool _death;

	int _speed;
};

