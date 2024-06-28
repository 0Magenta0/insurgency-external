/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#pragma once

#include "math.h"

typedef enum {
  NONE      = 0,
  SPECTATOR = 1,
  SECURITY  = 2,
  INSURGENT = 3
} team;


/*
 * NOTICE: zero index refers to local player.
 */

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
local_player_fov(void);
