#pragma once
#include <Windows.h>
class AudioManager
{
public:
	static AudioManager* GetInstance();
	static void DestroyInstance();

	void PlayStartGameSound()
	{
		Beep(70, 75);
		Beep(200, 75);
		Beep(400, 75);
		Beep(400, 40);
		Beep(700, 80);
	}

	void PlayPathBlockedSound()
	{
		Beep(400, 20);
		Beep(280, 30);

	}

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
	void PlayPlayerDamagedSound()
	{
		Beep(1000, 100);
		Beep(800, 50);
	}
private:
	static AudioManager* instance;
	AudioManager() {}
};

