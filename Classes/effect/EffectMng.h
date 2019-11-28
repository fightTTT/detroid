#pragma once
#include "Effekseer.h"
#include <map>

#define lpEffectMng EffectMng::GetInstance()

struct EffectStatus
{
	std::string effectName;		// エフェクト名
	std::string efkFileName;	// エフェクトファイル名
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
