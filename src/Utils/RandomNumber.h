#ifndef RIVERRAID_RANDOMNUMBER_H
#define RIVERRAID_RANDOMNUMBER_H

#include <cstdlib>

float randomFloat(float x) {
  return static_cast <float> (rand()) / (static_cast <float> (float(RAND_MAX) / x));
}

#endif
