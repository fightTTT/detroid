#include "FXManager.h"
#include "_DebugConOut.h"

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

void FXManager::AddEffect(const std::string & name)
{
	auto effect = Effect::create(name.c_str());
	_emitterMap.emplace(name, EffectEmitter::create(_groupManager));
	_emitterMap[name]->setEffect(effect);
	_emitterMap[name]->setPlayOnEnter(false);
}

void FXManager::Play(const std::string & name)
{
	if (MapCheck(name))
	{
		_emitterMap[name]->play();
	}
}

void FXManager::Play(const std::string & name, Vec2 & position)
{
	if (MapCheck(name))
	{
		_emitterMap[name]->setPosition(position);
		_emitterMap[name]->play();
	}
}

EffectEmitter & FXManager::GetEffect(const std::string & name)
{
	if (MapCheck(name))
	{
		return (*_emitterMap[name]);
	}
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
