#pragma once

typedef struct {
  float x;
  float y;
  float z;
} vector3;

typedef struct {
  float x;
  float y;
} vector2;

int
is_zero_pos(vector3 pos);

int
is_vector3_equals(vector3 vec1, vector3 vec2);

float
vector3_distance(vector3 vec1, vector3 vec2);

float
to_radian(float degree);

vector2
world_to_screen(vector3 player_pos, vector3 world_pos, vector2 rotation, float fov, int screen_width, int screen_height);
