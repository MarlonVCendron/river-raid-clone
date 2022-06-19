#include "SoundController.h"
#include <sstream>
#include <iostream>

irrklang::ISoundEngine* SoundController::engine = irrklang::createIrrKlangDevice();

void SoundController::play(std::string sound) {
  std::stringstream filePath;
  filePath << "./sounds/" << sound << ".wav";
  try {
    engine->play2D(filePath.str().c_str());
  } catch (...) {
    std::cout << "Erro ao tocar o som " << sound << "\n";
  }
}
