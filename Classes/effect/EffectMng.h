#pragma once
#include "Effekseer.h"
#include <map>

#define lpEffectMng EffectMng::GetInstance()

struct EffectStatus
{
	std::string effectName;		// �G�t�F�N�g��
	std::string efkFileName;	// �G�t�F�N�g�t�@�C����
};


class EffectMng:public cocos2d::Layer
{
public:
	EffectMng();
	~EffectMng();

	void AddEffect(std::string efkState);
	void update();
//-------------------
	efk::EffectManager& GetEffectMng();

	efk::EffectEmitter* GetEfkEmitter();
//---------------------------

private:
	efk::EffectManager* manager;
	int count = 0;
	virtual bool init()override;
	efk::EffectEmitter* emitter;
	
	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

};
