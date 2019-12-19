#include "EffectMng.h"

EffectMng* EffectMng::s_Instance = nullptr;

EffectMng::EffectMng()
{
	manager = nullptr;

	auto director = cocos2d::Director::getInstance();
	auto rsize = director->getOpenGLView()->getDesignResolutionSize();

	manager = efk::EffectManager::create(rsize);
}

EffectMng::~EffectMng()
{
	manager->release();
}

bool EffectMng::Create(const std::string& imageName)
{
	auto effect = efk::Effect::create(imageName);
	if (effect == nullptr)
	{
		return false;
	}
	_effectData.emplace_back(efk::EffectEmitter::create(manager));
	
	_effectData.back()->setEffect(effect);

		//return true;
	
	return false;
}

void EffectMng::Pos(const cocos2d::Vec2& pos)
{
	_effectData.back()->setPosition(pos);
}

void EffectMng::Scale(int scale)
{
	_effectData.back()->setScale(scale);
}

void EffectMng::PlayEffect(bool playEffect)
{
	_effectData.back()->setPlayOnEnter(playEffect);
}

void EffectMng::Rotate(const cocos2d::Vec3& rotate)
{
	_effectData.back()->setRotation3D(rotate);
}

efk::EffectEmitter* EffectMng::AddLayer(const std::string& layerName)
{
	auto director = cocos2d::Director::getInstance();
	manager->setIsDistortionEnabled(true);
	//effectClone.emplace_back(effectData[effectName]);
	auto a = director->getRunningScene()->getChildByName(layerName);
	a->addChild(_effectData.back())
	;
	return _effectData.back();
}

void EffectMng::update()
{
	manager->update();
}
