#ifndef RIVERRAID_CHECKCOLLISION_H
#define RIVERRAID_CHECKCOLLISION_H

bool boxCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
  float x1w = x1 + w1;
  float y1h = y1 + h1;
  
  float x2w = x2 + w2;
  float y2h = y2 + h2;
  
  return !(x1w < x2 || x1 > x2w || y1h < y2 || y1 > y2h);
}

bool lineBoxCollision(float x1, float y1, float x2, float y2, float x3, float y3, float w, float h, bool left) {
  if (y3 < y1 || y3+h > y2) return false;

  float a = y1-y2;
  float b = x2-x1;
  float c = (x1-x2)*y1 + (y2-y1)*x1;

  float corner1 = a * x3 + b * y3 + c;
  float corner2 = a * x3 + b * (y3+h) + c;
  float corner3 = a * (x3+w) + b * (y3+h) + c;
  float corner4 = a * (x3+w) + b * y3 + c;

  if(left) {
    return corner1 > 0 || corner2 > 0;
  } else {
    return corner3 < 0 || corner4 < 0;
  }
}

#endif
