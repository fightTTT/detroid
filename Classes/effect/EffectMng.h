#pragma once
#include "Effekseer.h"
#include <map>
#include <vector>

#define lpEffectMng EffectMng::GetInstance()

using EffectData = std::map<std::string, efk::EffectEmitter*>;


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
	
	bool Create(std::string imageName);
	void Pos(cocos2d::Vec2 pos);
	void Scale(int scale);
	void PlayEffect(bool playEffect);
	void Rotate(cocos2d::Vec3 pos);
	efk::EffectEmitter* AddLayer(std::string layerName);

	void update();
//-------------------

	efk::EffectEmitter& GetEfkEmitter();
//---------------------------
	~EffectMng();
private:
	EffectMng();

	static EffectMng *s_Instance;

	// 登録したエフェクトを管理するマップ
	std::vector<efk::EffectEmitter*> effectData;


	efk::EffectManager* manager = nullptr;
	int count = 0;
	bool Init();
	efk::EffectEmitter* emitter;
};
