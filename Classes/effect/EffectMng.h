#pragma once
#include "Effekseer.h"
#include <map>

#define lpEffectMng EffectMng::GetInstance()

struct EffectStatus
{
	std::string efkFileName;	// エフェクトファイル名
	cocos2d::Vec2 pos;
	int scale;
};


class EffectMng:public cocos2d::Layer
{
public:
	EffectMng();
	~EffectMng();

	void AddEffect(EffectStatus efkState);
	void update();
//-------------------

	efk::EffectEmitter& GetEfkEmitter();
//---------------------------

private:
	efk::EffectManager* manager = nullptr;
	int count = 0;
	virtual bool init()override;
	efk::EffectEmitter* emitter;
	
};
