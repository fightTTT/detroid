#include "EffekseerManager.h"
#include "_DebugConOut.h"

#define AddToLayer(emitter) Director::getInstance()->getRunningScene()->getChildByName("FollowerLayer")->getChildByName("EffectLayer")->addChild(emitter);

FXManager* FXManager::_instance = nullptr;

void FXManager::Init(void)
{
	_groupManager = nullptr;
}

bool FXManager::CreateGroupManager(const Size & visibleSize)
{
	_groupManager = EffectManager::create(visibleSize);
	if (_groupManager == nullptr)
	{
		return false;
	}
	return true;
}

void FXManager::CreateEffect(const std::string & name)
{
	AddToLayer(CloneEffect(name));
}

void FXManager::CreateEffect(const std::string & name, const Vec2 & position)
{
	auto tmpEffect = CloneEffect(name);
	tmpEffect->setPosition(position);
	AddToLayer(tmpEffect);
}

void FXManager::CreateEffect(const std::string & name, const Vec2 & position, const bool & flip)
{
	auto tmpEffect = CloneEffect(name);
	tmpEffect->setPosition(position);

	Vec3 rotation;
	if (flip)
	{
		rotation = Vec3(0.0f, -90.0f, 0.0f);
	}
	else
	{
		rotation = Vec3(0.0f, 90.0f, 0.0f);
	}

	tmpEffect->setRotation3D(rotation);
	AddToLayer(tmpEffect);
}

void FXManager::CreateEffect(const std::string & name, Layers & layer)
{
}

EffectEmitter * FXManager::AddEffect(const std::string & name)
{
	_emitterMap.emplace(name, EffectEmitter::create(_groupManager));
	_emitterMap[name]->setEffect(Effect::create(name.c_str()));
	_emitterMap[name]->setPosition(Vec2(300.0f, 20.0f));
	_emitterMap[name]->setScale(20.0f);
	_emitterMap[name]->setPlayOnEnter(false);
	_emitterMap[name]->setRemoveOnStop(false);

	if (_emitterMap[name] == nullptr)
	{
		_emitterMap.erase(name);
		return nullptr;
	}
	return _emitterMap[name];
}

EffectEmitter * FXManager::GetEffect(const std::string & name)
{
	if (MapCheck(name))
	{
		return _emitterMap[name];
	}
	return nullptr;
}

EffectManager * FXManager::GetManager(void)
{
	return _groupManager;
}

void FXManager::Update(void)
{
	_groupManager->update();
}

void FXManager::Shutdown(void)
{
	delete _instance;
	_instance = nullptr;
}

FXManager::FXManager()
{

}

FXManager::~FXManager()
{
}

bool FXManager::MapCheck(const std::string & name)
{
	if (_emitterMap.find(name) == _emitterMap.end())
	{
		//TRACE("Effect %s is not exist.\n", name.c_str());
		return false;
	}
	return true;
}

EffectEmitter * FXManager::CloneEffect(const std::string & name)
{
	auto emitter = EffectEmitter::create(_groupManager);
	emitter->setEffect(_emitterMap[name]->getEffect());
	emitter->setPosition(_emitterMap[name]->getPosition());
	emitter->setRotation3D(_emitterMap[name]->getRotation3D());
	emitter->setScale(_emitterMap[name]->getScale());
	emitter->setPlayOnEnter(true);
	emitter->setRemoveOnStop(true);
	return emitter;
}
