#pragma once
#include <Windows.h>
class AudioManager
{
public:
	static AudioManager* GetInstance();
	static void DestroyInstance();
	void PlayDoorClosedSound()
	{
		Beep(500, 75);
		Beep(500, 75);
	}
	void PlayDoorOpenSound()
	{
		Beep(1397, 200);
	}
	void PlayKeyPickupSound()
	{
		Beep(1568, 50);
		Beep(1568, 200);
	}
	void PlayKeyDropSound()
	{
		Beep(1568, 200);
		Beep(1568, 50);
	}
private:
	static AudioManager* instance;
	AudioManager() {}
};

