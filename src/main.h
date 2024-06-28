/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#pragma once

#include <sys/types.h>

#define PROCESS_NAME "insurgency_linu"

#define PLAYER_TEAM_OFFSET      0xDC
#define PLAYER_DEAD_FLAG_OFFSET 0x1890
#define PLAYER_HEALTH_OFFSET    0xE8
#define PLAYER_POS_X_OFFSET     0x90
#define PLAYER_POS_Y_OFFSET     0x94
#define PLAYER_POS_Z_OFFSET     0x98
#define PLAYER_YAW_OFFSET       0xB4
#define PLAYER_PITCH_OFFSET     0x1894
#define PLAYER_FOV_OFFSET       0x000B763C

#define CROSSHAIR_SIZE 5
#define CROSSHAIR_COLOR_NORMAL 0x0000FF00
#define CROSSHAIR_COLOR_FRIEND 0x0000FFFF
#define CROSSHAIR_COLOR_ENEMY  0x00FF0000

#define RADAR_SIZE             250
#define RADAR_RANGE            5000
#define RADAR_YAW_LINE         18
#define RADAR_PLAYER_SIZE      5
#define RADAR_PLAYER_FLOOR     100
#define RADAR_COLOR_BORDER     0x00FF0000
#define RADAR_COLOR_BACKGROUND 0x55005500
#define RADAR_COLOR_PLAYER     0x00FFFFFF
#define RADAR_COLOR_ENEMY      0x00FF0000
#define RADAR_COLOR_FRIENDLY   0x0000FFFF
#define RADAR_COLOR_YAW_LINE   0x00FF00FF

#define ESP_RECT_SIZE          8
#define ESP_COLOR_FAR_RANGE    0x00A600FF
#define ESP_COLOR_NORMAL_RANGE 0x0000FF00
#define ESP_COLOR_WARN_RANGE   0x00FFBB00
#define ESP_COLOR_DANGER_RANGE 0x00FF0000

#define HUD_NORMAL_HP          0x0000FF00
#define HUD_DANGER_HP          0x00FF0000

extern pid_t ins_pid;

extern void *client_base;
/* extern void *engine_base; */
