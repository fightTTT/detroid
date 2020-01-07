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

	// �G�t�F�N�g�̓o�^����
	void AddEffect(const std::string& imageName, const std::string effectName);
	
	void Pos(const std::string effectName, const cocos2d::Vec2& pos);			// ���W�w��
	void Scale(const std::string effectName, int scale);						// �傫��
	void Loop(const std::string effectName, bool loop);
	void PlayEffect(const std::string effectName, bool playEffect);				// �G�t�F�N�g��\�������邩?
	void Rotate(const std::string effectName, const cocos2d::Vec3& rotate);		// ��]
	const cocos2d::Vec3& Rotate(const std::string effectName) { return effectEmitter[effectName]->getRotation3D(); };
	void AddLayer(const std::string effectName, const std::string& layerName);	// ���C���[�ɒǉ�
	void AddLayer(const std::string effectName, const std::string& layerName, const cocos2d::Vec2 pos, const cocos2d::Vec3 rotate);
	efk::EffectManager* GetEffectMng() { return manager; };
	void update();
	~EffectMng();
private:
	EffectMng();
	static EffectMng *s_Instance;

	std::map<std::string, efk::EffectEmitter*> effectEmitter;
	// ���������G�t�F�N�g������
	//efk::Effect* _effectData;
	efk::EffectManager* manager = nullptr;
};
