#pragma once
#include "Effekseer.h"
#include <map>
#include <vector>

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

	// エフェクトの登録処理
	void AddEffect(const std::string& imageName, const std::string effectName);
	
	void Pos(const std::string effectName, const cocos2d::Vec2& pos);			// 座標指定
	void Scale(const std::string effectName, int scale);						// 大きさ
	void Loop(const std::string effectName, bool loop);
	void PlayEffect(const std::string effectName, bool playEffect);				// エフェクトを表示させるか?
	void Rotate(const std::string effectName, const cocos2d::Vec3& rotate);		// 回転
	const cocos2d::Vec3& Rotate(const std::string effectName) { return effectEmitter[effectName]->getRotation3D(); };
	void AddLayer(const std::string effectName, const std::string& layerName);	// レイヤーに追加
	void AddLayer(const std::string effectName, const std::string& layerName, const cocos2d::Vec2 pos, const cocos2d::Vec3 rotate);
	efk::EffectManager* GetEffectMng() { return manager; };
	void update();
	~EffectMng();
private:
	EffectMng();
	static EffectMng *s_Instance;

	std::map<std::string, efk::EffectEmitter*> effectEmitter;
	// 複製したエフェクトを入れる
	//efk::Effect* _effectData;
	efk::EffectManager* manager = nullptr;
};
