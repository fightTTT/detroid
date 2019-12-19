#pragma once
#include "Effekseer.h"
#include "cocos2d.h"
#include <string>
#include <map>

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
	void AddEffect(const std::string& name);
	void Play(const std::string& name);
	void Play(const std::string& name, Vec2& position);
	EffectEmitter& GetEffect(const std::string& name);
	void Shutdown(void);
private:
	FXManager();
	~FXManager();
	void Init(void);
	// �}�b�v�z��̗v�f���`�F�b�N����	ture : �v�f����	false : �v�f�Ȃ�
	bool MapCheck(const std::string& name);
	static FXManager* _instance;
	std::map<std::string, EffectEmitter*> _emitterMap;
	EffectManager* _groupManager;
};