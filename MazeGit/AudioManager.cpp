#include "AudioManager.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager* AudioManager::GetInstance()
{
	if (instance == nullptr)
		instance = new AudioManager();
	return instance;
}

void AudioManager::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}
