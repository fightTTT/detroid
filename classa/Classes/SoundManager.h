#pragma once
#include "ck/ck.h"
#include "ck/config.h"
#include "ck/bank.h"
#include "ck/sound.h"
#include <string>
#include <map>

class SoundManager
{
public:
	static SoundManager& Instance(void)
	{
		if (_instance == nullptr)
		{
			_instance = new SoundManager();
			_instance->Init();
		}
		return(*_instance);
	}
	void AddBank(const std::string& name);
	void PlayAudio(const std::string& name);
	void PlayAudio(const std::string & bankName, const std::string & soundName);
	void ClearAll(void);
	void Shutdown(void);
	void Update(void);
private:
	SoundManager();
	~SoundManager();
	void Init(void);
	static SoundManager* _instance;
	std::map<std::string, CkSound*> _soundMap;
	std::map<std::string, CkBank*> _bankMap;
};