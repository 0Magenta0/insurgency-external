/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include "player_info.h"

#include "memory.h"

#include "../main.h"

char
local_player_team(int index)
{
  void *pointer;
  char team;

  if (index == 0) {
    pointer = client_base + OFFSET_CLIENT_BASE_2;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + OFFSET_PLAYER_TEAM, &team, 1) > 0) {
            return team;
          }
      }
    }
  } else {
    pointer = client_base + OFFSET_CLIENT_BASE_1;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + OFFSET_PLAYER_TEAM, &team, 1) > 0) {
          return team;
        }
      }
    }
  }

  return -1;
}


char
local_player_health(int index)
{
  void *pointer;
  char health;

  if (index == 0) {
    pointer = client_base + OFFSET_CLIENT_BASE_2;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + OFFSET_PLAYER_HEALTH, &health, 1) > 0) {
            return health;
          }
      }
    }
  } else {
    pointer = client_base + OFFSET_CLIENT_BASE_1;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + OFFSET_PLAYER_HEALTH, &health, 1) > 0) {
          return health;
        }
      }
    }
  }

  return -1;
}

char
local_player_dead_flag(int index)
{
  void *pointer;
  char dead_flag;

  if (index == 0) {
    pointer = client_base + OFFSET_CLIENT_BASE_2;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + OFFSET_PLAYER_DEAD_FLAG, &dead_flag, 1) > 0) {
            return dead_flag;
          }
      }
    }
  } else {
    pointer = client_base + OFFSET_CLIENT_BASE_1;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + OFFSET_PLAYER_DEAD_FLAG, &dead_flag, 1) > 0) {
          return dead_flag;
        }
      }
    }
  }

  return -1;
}

float
local_player_pos_x(int index)
{
  void  *pointer;
  float pos_x;

  if (index == 0) {
    pointer = client_base + OFFSET_CLIENT_BASE_2;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + OFFSET_PLAYER_POS_X, &pos_x, 4) == 4) {
            return pos_x;
          }
      }
    }
  } else {
    pointer = client_base + OFFSET_CLIENT_BASE_1;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + OFFSET_PLAYER_POS_X, &pos_x, 4) == 4) {
          return pos_x;
        }
      }
    }
  }

  return -1;
}

float
local_player_pos_y(int index)
{
  void  *pointer;
  float pos_y;

  if (index == 0) {
    pointer = client_base + OFFSET_CLIENT_BASE_2;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + OFFSET_PLAYER_POS_Y, &pos_y, 4) == 4) {
            return pos_y;
          }
      }
    }
  } else {
    pointer = client_base + OFFSET_CLIENT_BASE_1;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + OFFSET_PLAYER_POS_Y, &pos_y, 4) == 4) {
          return pos_y;
        }
      }
    }
  }

  return -1;
}

float
local_player_pos_z(int index)
{
  void  *pointer;
  float pos_z;

  if (index == 0) {
    pointer = client_base + OFFSET_CLIENT_BASE_2;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + OFFSET_PLAYER_POS_Z, &pos_z, 4) == 4) {
            return pos_z;
          }
      }
    }
  } else {
    pointer = client_base + OFFSET_CLIENT_BASE_1;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + OFFSET_PLAYER_POS_Z, &pos_z, 4) == 4) {
          return pos_z;
        }
      }
    }
  }

  return -1;
}

vector3
local_player_pos(int index)
{
  void    *pointer  = client_base + OFFSET_CLIENT_BASE_1;
  vector3 pos = { -1, -1, -1 };

  if (index == 0) {
    pointer = client_base + OFFSET_CLIENT_BASE_2;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + OFFSET_PLAYER_POS_X, &pos, 12) == 12) {
            return pos;
          }
      }
    }
  } else {
    pointer = client_base + OFFSET_CLIENT_BASE_1;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + OFFSET_PLAYER_POS_X, &pos, 12) == 12) {
          return pos;
        }
      }
    }
  }

  return pos;
}

float
local_player_yaw(int index)
{
  void  *pointer;
  float yaw;

  if (index == 0) {
    pointer = client_base + OFFSET_CLIENT_BASE_2;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + OFFSET_PLAYER_YAW, &yaw, 4) == 4) {
            return yaw;
          }
      }
    }
  } else {
    pointer = client_base + OFFSET_CLIENT_BASE_1;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + OFFSET_PLAYER_YAW, &yaw, 4) == 4) {
          return yaw;
        }
      }
    }
  }

  return -1;
}

float
local_player_pitch(int index)
{
  void  *pointer;
  float pitch;

  if (index == 0) {
    pointer = client_base + OFFSET_CLIENT_BASE_2;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + OFFSET_PLAYER_PITCH, &pitch, 4) == 4) {
            return pitch;
          }
      }
    }
  } else {
    pointer = client_base + OFFSET_CLIENT_BASE_1;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + OFFSET_PLAYER_PITCH, &pitch, 4) == 4) {
          return pitch;
        }
      }
    }
  }

  return -1;
}

float
local_player_fov(void)
{
  void  *pointer = client_base + OFFSET_CLIENT_BASE_3;
  float fov;

  if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
    if (memory_read(ins_pid, pointer + 0x25C, &fov, 4) == 4) {
      return fov;
    }
  }

  return -1;
}
