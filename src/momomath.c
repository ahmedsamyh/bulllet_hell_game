#include <momomath.h>
#include <stdlib.h>

float deg2rad(float deg){
  return (deg / 360.f)*TWO_PI;
}

float rad2deg(float rad){
 return (rad / TWO_PI)*360.f;
}

float randomf(float from, float to) {
  float rn = (float)rand() / (float)RAND_MAX;
  return from + (rn * (to - from));
}

float map(float value, float from_min, float from_max, float to_min, float to_max) {
  return to_min + ((to_max - to_min) / (from_max - from_min)) * (value - from_min);
}

// Raylib
Vector2 vector2_from_degrees(float deg) {
    Vector2 result = {
        .x = cosf(DEG2RAD * deg),
        .y = sinf(DEG2RAD * deg),
    };
    return result;
}
