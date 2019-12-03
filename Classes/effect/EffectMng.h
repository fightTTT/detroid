#pragma once
#include "Effekseer.h"
#include <map>

#define lpEffectMng EffectMng::GetInstance()


class EffectMng
{
public:

	static EffectMng &GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new EffectMng;
		}
		return *s_Instance;
	}
	
	bool Create(std::string effectName, std::string imageName);
	void Pos(std::string effectName, cocos2d::Vec2 pos);
	void Scale(std::string effectName, int scale);
	void PlayEffect(std::string effectName, bool playEffect);
	efk::EffectEmitter* AddLayer(std::string layerName, std::string effectName);

	void update();
//-------------------

	efk::EffectEmitter& GetEfkEmitter();
//---------------------------
	~EffectMng();
private:
	EffectMng();

	static EffectMng *s_Instance;

	// 登録したエフェクトを管理するマップ
	std::map<std::string, efk::EffectEmitter*> effectData;

	efk::EffectManager* manager = nullptr;
	int count = 0;
	bool Init();
	efk::EffectEmitter* emitter;
};
