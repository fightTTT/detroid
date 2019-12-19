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
	
	bool Create(const std::string& imageName);		// エフェクト作成
	void Pos(const cocos2d::Vec2& pos);				// 座標指定
	void Scale(int scale);							// 大きさ
	void PlayEffect(bool playEffect);				// エフェクトを表示させるか?
	void Rotate(const cocos2d::Vec3& pos);			// 回転
	efk::EffectEmitter* AddLayer(const std::string& layerName);	// レイヤーに追加

	void update();
	~EffectMng();
private:
	EffectMng();
	static EffectMng *s_Instance;

	// 複製したエフェクトを入れる
	std::vector<efk::EffectEmitter*> _effectData;
	efk::EffectManager* manager = nullptr;
};
