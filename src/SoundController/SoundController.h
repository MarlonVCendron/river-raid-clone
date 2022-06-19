#ifndef RIVERRAID_SOUNDCONTROLLER_H
#define RIVERRAID_SOUNDCONTROLLER_H

#include <string>
#include "../../lib/IrrKlang/include/irrKlang.h"

class SoundController {

public:
  static irrklang::ISoundEngine* engine;
  static void play(std::string sound);

};

#endif
