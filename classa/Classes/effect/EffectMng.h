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
	
	bool Create(const std::string& imageName);		// �G�t�F�N�g�쐬
	void Pos(const cocos2d::Vec2& pos);				// ���W�w��
	void Scale(int scale);							// �傫��
	void PlayEffect(bool playEffect);				// �G�t�F�N�g��\�������邩?
	void Rotate(const cocos2d::Vec3& pos);			// ��]
	efk::EffectEmitter* AddLayer(const std::string& layerName);	// ���C���[�ɒǉ�

	void update();
	~EffectMng();
private:
	EffectMng();
	static EffectMng *s_Instance;

	// ���������G�t�F�N�g������
	std::vector<efk::EffectEmitter*> _effectData;
	efk::EffectManager* manager = nullptr;
};
