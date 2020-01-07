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

	for (auto effect : effectEmitter)
	{
		effect.second->release();
	}
}

void EffectMng::AddEffect(const std::string & imageName,const std::string effectName)
{
	// 指定したエフェクトがnullptrだった場合
	/*if (efk::Effect::create(imageName) != nullptr)
	{
		effectEmitter[] = efk::EffectEmitter::create(manager);
		effectEmitter.emplace(std::make_pair(effectName, efk::Effect::create(imageName)));

		effectEmitter->setEffect(effect[effectName]);
		effectEmitter->setRemoveOnStop(false);
		return;
	}*/
	effectEmitter.emplace(effectName, efk::EffectEmitter::create(manager));


	//_effectData = efk::Effect::create(imageName);
	if (efk::Effect::create(imageName) != nullptr)
	{
		effectEmitter[effectName]->setEffect(efk::Effect::create(imageName));
		effectEmitter[effectName]->setRemoveOnStop(false);
		effectEmitter[effectName]->setScale(20);
		effectEmitter[effectName]->setPlayOnEnter(true);
		effectEmitter[effectName]->retain();
	}
}

void EffectMng::Pos(const std::string effectName, const cocos2d::Vec2& pos)
{
	effectEmitter[effectName]->setPosition(pos);
}

void EffectMng::Scale(const std::string effectName, int scale)
{
	effectEmitter[effectName]->setScale(scale);
}

void EffectMng::Loop(const std::string effectName, bool loop)
{
	effectEmitter[effectName]->setIsLooping(loop);

}

void EffectMng::PlayEffect(const std::string effectName, bool playEffect)
{
	effectEmitter[effectName]->setPlayOnEnter(playEffect);
}

void EffectMng::Rotate(const std::string effectName, const cocos2d::Vec3& rotate)
{
	effectEmitter[effectName]->setRotation3D(rotate);
}

void EffectMng::AddLayer(const std::string effectName, const std::string& layerName)
{

	auto director = cocos2d::Director::getInstance();
	manager->setIsDistortionEnabled(true);
	//effectClone.emplace_back(effectData[effectName]);
	auto a = director->getRunningScene()->getChildByName("FollowerLayer")->getChildByName(layerName);

	efk::EffectEmitter* test;
	test->create(manager);
	test->setScale(effectEmitter[effectName]->getScale());
	test->setPlayOnEnter(effectEmitter[effectName]->getPlayOnEnter());

	a->addChild(effectEmitter[effectName]);
}

void EffectMng::AddLayer(const std::string effectName, const std::string & layerName, const cocos2d::Vec2 pos, const cocos2d::Vec3 rotate)
{
	auto director = cocos2d::Director::getInstance();
	manager->setIsDistortionEnabled(true);
	auto a = director->getRunningScene()->getChildByName("FollowerLayer")->getChildByName(layerName);
	efk::EffectEmitter* test;
	test = efk::EffectEmitter::create(manager);
	test->setEffect(effectEmitter[effectName]->getEffect());
	test->setScale(effectEmitter[effectName]->getScale());
	test->setPlayOnEnter(effectEmitter[effectName]->getPlayOnEnter());
	test->setPosition(pos);
	test->setRotation3D(rotate);

	a->addChild(test);
}

void EffectMng::update()
{
	manager->update();
}
