#pragma once
#include "cocos2d.h"

class ActCtrl;

class Obj
{
public:
	Obj() :life(1) {}
	Obj(int l) :life(l){}
	virtual ~Obj();

	// �I�u�W�F�N�g�̃��C�t���擾����
	const int Life() { return life; };
	//// ���C�t���Z�b�g����
	//void Life(const int life);

protected:
	ActCtrl* _actCtrl;		// �A�N�V�������Ǘ�

	const int life;		// �I�u�W�F�N�g�̃��C�t

};

