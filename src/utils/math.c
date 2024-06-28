/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include "math.h"

#include <math.h>
#include <stdio.h>

int
is_zero_pos(vector3 pos)
{
  return pos.x == 0.0 && pos.y == 0.0 && pos.z == 0.0;
}

int
is_vector3_equals(vector3 vec1, vector3 vec2)
{
  return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

float
vector3_distance(vector3 vec1, vector3 vec2)
{
  return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2) + pow(vec1.z - vec2.z, 2));
}

float
to_radian(float degree)
{
  return degree * (M_PI / 180);
}


vector2
world_to_screen(vector3 camera_position, vector3 world_position, vector2 camera_rotation, float fov, int screen_width, int screen_height)
{
  vector2 screen_pos; 
  camera_rotation.x = -camera_rotation.x;

  vector3 v_delta;
  v_delta.x = world_position.x - camera_position.x;
  v_delta.y = world_position.y - camera_position.y;
  v_delta.z = world_position.z - camera_position.z;

  float rad_pitch = camera_rotation.x * M_PI / 180.0f;
  float rad_yaw = camera_rotation.y * M_PI / 180.0f;

  float sp = sinf(rad_pitch);
  float cp = cosf(rad_pitch);
  float sy = sinf(rad_yaw);
  float cy = cosf(rad_yaw);

  float temp_x = v_delta.x;
  float temp_z = v_delta.z;

  v_delta.x = temp_x * cy - temp_z * sy;
  v_delta.z = temp_x * sy + temp_z * cy;

  temp_x = v_delta.x;
  temp_z = v_delta.z;

  float temp_y = v_delta.y;
  v_delta.y = temp_y * cp - temp_z * sp;
  v_delta.z = temp_y * sp + temp_z * cp;
  temp_z = v_delta.z;

  if (v_delta.z < 1.0f) {
      v_delta.z = 1.0f;
  }

  float multi = (screen_width / 2.0f) / (tanf(fov * 0.00872665f) * v_delta.z);

  v_delta.x = -v_delta.x;

  screen_pos.x = screen_width / 2.0f + v_delta.x * multi;
  screen_pos.y = screen_height / 2.0f - v_delta.y * multi;

  return screen_pos;
}

