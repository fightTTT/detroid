#pragma once
#include "cocos2d.h"
#include <list>

struct ActModule;
enum class INPUT_TRG;
enum class PL_ACTION;

using actFnc = std::function<bool(cocos2d::Sprite&, ActModule&)>;

struct ActModule
{
	std::list<PL_ACTION> blackList;				// �u���b�N���X�g
	cocos2d::EventKeyboard::KeyCode keyCode;	// ���̓L�[
	INPUT_TRG trgType;
	cocos2d::Vec2 speed;						// �X�s�[�h
	cocos2d::Vec2 colOffsetPos;					// �����蔻��̃I�t�Z�b�g
	cocos2d::Vec2 colNum;						// �����蔻��̐�
	PL_ACTION actionType;						// �A�N�V�����̃^�C�v
	std::list<actFnc> checkList;				// �A�N�V�����̃`�F�b�N���X�g
	actFnc actRun;								// �A�N�V�����̏���
};

class ActCtrl
{
public:
	ActCtrl();
	~ActCtrl();
	// �A�N�V�����̓o�^
	bool AddAction(ActModule& actModule, const std::string& str);
	// �A�N�V�����̐؂�ւ��A���s
	void Update(cocos2d::Sprite& sprite);
private:
	std::map<std::string, ActModule> _actionData;	// �A�N�V�����̃��X�g
};