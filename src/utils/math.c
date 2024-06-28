/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include "math.h"

#include <math.h>

int
is_vector3_zero(vector3 vec)
{
  return vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0;
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
world_to_screen(vector3 camera_position,
                vector3 world_position,
                vector2 camera_rotation,
                float fov,
                int screen_width,
                int screen_height)
{
  float   rad_pitch;
  float   rad_yaw;
  float   sin_pitch;
  float   con_pitch;
  float   sin_yaw;
  float   cos_yaw;
  float   temp_x;
  float   temp_y;
  float   temp_z;
  float   multi;
  vector2 screen_pos; 
  vector3 delta_vector;

  camera_rotation.x = -camera_rotation.x;

  delta_vector.x = world_position.x - camera_position.x;
  delta_vector.y = world_position.y - camera_position.y;
  delta_vector.z = world_position.z - camera_position.z;

  rad_pitch = to_radian(camera_rotation.x);
  rad_yaw   = to_radian(camera_rotation.y);

  sin_pitch = sinf(rad_pitch);
  con_pitch = cosf(rad_pitch);
  sin_yaw   = sinf(rad_yaw);
  cos_yaw   = cosf(rad_yaw);

  temp_x = delta_vector.x;
  temp_z = delta_vector.z;
  temp_y = delta_vector.y;

  delta_vector.x = temp_x * cos_yaw - temp_z * sin_yaw;
  delta_vector.z = temp_x * sin_yaw + temp_z * cos_yaw;

  temp_x = delta_vector.x;
  temp_z = delta_vector.z;

  delta_vector.y = temp_y * con_pitch - temp_z * sin_pitch;
  delta_vector.z = temp_y * sin_pitch + temp_z * con_pitch;

  if (delta_vector.z < 1.0f) {
      delta_vector.z = 1.0f;
  }

  multi = (screen_width / 2.0f) / (tanf(fov * (M_PI / 360)) * delta_vector.z);

  delta_vector.x = -delta_vector.x;

  screen_pos.x = screen_width / 2.0f + delta_vector.x * multi;
  screen_pos.y = screen_height / 2.0f - delta_vector.y * multi;

  return screen_pos;
}

float
units_to_meters(float units)
{
  return units * 0.0254;
}
