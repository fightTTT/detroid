#pragma once
#include "Effekseer.h"
#include "cocos2d.h"
#include <string>
#include <map>
#include <list>

#define EFFECT(name) FXManager::Instace().GetEffect(name)

enum class Layers
{
	BACKGROUND,
	BLOCK,
	PLAYER,
	INFO,
	MAX
};

USING_NS_CC;
using namespace efk;

class FXManager
{
public:
	static FXManager& Instace(void)
	{
		if (_instance == nullptr)
		{
			_instance = new FXManager();
			_instance->Init();
		}
		return (*_instance);
	}
	bool CreateGroupManager(const Size& viewSize);
	void CreateEffect(const std::string& name);
	void CreateEffect(const std::string& name, const Vec2& position);
	void CreateEffect(const std::string& name, const Vec2& position, const bool& flip);
	void CreateEffect(const std::string& name, Layers& layer);
	EffectEmitter* CloneEffect(const std::string& name);		// マップ配列のemitterをクローンする
	EffectEmitter* AddEffect(const std::string& name);			// マップ配列にemitterを登録する
	EffectEmitter* GetEffect(const std::string& name);
	EffectManager* GetManager(void);
	void Update(void);
	void Shutdown(void);
private:
	FXManager();
	~FXManager();

	static FXManager* _instance;
	std::map<std::string, EffectEmitter*> _emitterMap;	// 設定したemitterを登録する
	EffectManager* _groupManager;
	std::list<EffectEmitter*> _emitterList;

	void Init(void);
	// マップ配列の要素をチェックする	true : 要素あり	false : 要素ない
	bool MapCheck(const std::string& name);
};