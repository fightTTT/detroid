#include "SoundManager.h"
#include "_DebugConOut.h"
#include "CricketAndroidJni.h"

SoundManager* SoundManager::_instance = nullptr;

void SoundManager::AddBank(const std::string & name)
{
	if (_bankMap.find(name) == _bankMap.end())
	{
		std::string path = "Audio/" + name;
		_bankMap.emplace(name, CkBank::newBank(path.c_str()));
		if (_bankMap[name] == nullptr)
		{
			//TRACE("Bank is not found or missing.\n");
			return;
		}
		//TRACE("Successfully added Bank %s.\n", name.c_str());
		return;
	}
	//TRACE("Bank %s is already added.\n", name.c_str());
}

void SoundManager::PlayAudio(const std::string & name)
{
	if (_soundMap.find(name) == _soundMap.end())
	{
		std::string path;

#if CK_PLATFORM_ANDROID
		path = "Audio/" + name;
#else
		path = "Resources/Audio/" + name;
#endif
		
		_soundMap.emplace(name, CkSound::newStreamSound(path.c_str()));

		if (_soundMap[name] == nullptr)
		{
			//TRACE("Sound is not found or missing.\n");
			return;
		}
	}
	_soundMap[name]->play();
}

void SoundManager::PlayAudio(const std::string & bankName, const std::string & soundName)
{
	if (_bankMap.find(bankName) == _bankMap.end())
	{
		//TRACE("Bank is not registered.\n");
		return;
	}

	if (_soundMap.find(soundName) == _soundMap.end())
	{
		_soundMap.emplace(soundName, CkSound::newBankSound(_bankMap[bankName], soundName.c_str()));
		if (_soundMap[soundName] == nullptr)
		{
			//TRACE("Sound is not found or missing.\n");
			return;
		}
	}
	_soundMap[soundName]->play();
}

void SoundManager::ClearAll(void)
{
	if (_soundMap.size() != 0)
	{
		for (auto& sound : _soundMap)
		{
			if (sound.second != nullptr)
			{
				sound.second->destroy();
			}
		}
		_soundMap.clear();
	}

	if (_bankMap.size() != 0)
	{
		for (auto& bank : _bankMap)
		{
			if (bank.second != nullptr)
			{
				bank.second->destroy();
			}
		}
		_bankMap.clear();
	}
}

void SoundManager::Shutdown(void)
{
	ClearAll();
	CkShutdown();
	delete _instance;
	_instance = nullptr;
}

void SoundManager::Update(void)
{
	CkUpdate();
}

void SoundManager::Init(void)
{
#if CK_PLATFORM_ANDROID
#else
	CkConfig config;
	CkInit(&config);
#endif
}

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}