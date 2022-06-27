bool checkCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
  float x1w = x1 + w1;
  float y1h = y1 + h1;
  
  float x2w = x2 + w2;
  float y2h = y2 + h2;
  
  return !(x1w < x2 || x1 > x2w || y1h < y2 || y1 > y2h);
}

