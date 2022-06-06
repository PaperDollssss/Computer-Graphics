#include "texture_mapping.h"

void PlayMusic(std::string path) {
  mciSendString(TEXT("close start"), NULL, 0, NULL);
  mciSendString(TEXT(("open "+ path +" alias start").c_str()), NULL, 0, NULL);
  mciSendString(TEXT("play start repeat"), NULL, 0, NULL);
}