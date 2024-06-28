#pragma once

#include "math.h"

enum team {
  NONE      = 0,
  SPECTATOR = 1,
  SECURITY  = 2,
  INSURGENT = 3
};

char
local_player_team(int index);

char
local_player_health(int index);

char
local_player_dead_flag(int index);

float
local_player_pos_x(int index);

float
local_player_pos_y(int index);

float
local_player_pos_z(int index);

vector3
local_player_pos(int index);

float
local_player_yaw(int index);

float
local_player_pitch(int index);

float
player_fov(void);
