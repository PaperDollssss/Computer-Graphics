#include "texture_mapping.h"

void PlayMusic(std::string path) {
	PlaySound(TEXT(path).c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Playaddition(float distance, std::string path) {
	int volume = 0;
	if (distance >= 15.0f) {
		volume = 0;
	}
	else {
		volume = int((1.0 - distance / 15.0f) * 1000.0f);
	}
	//std::cout << volume << std::endl;
	std::string MciCommand = "setaudio start volume to " + std::to_string(volume);
	mciSendString(TEXT("close start"), NULL, 0, NULL);
	mciSendString(TEXT(("open " + path + " alias start").c_str()), NULL, 0, NULL);
	mciSendString(TEXT("play start"), NULL, 0, NULL);
	mciSendString(TEXT(MciCommand.c_str()), NULL, 0, 0);
}