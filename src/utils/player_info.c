#include "player_info.h"

#include "memory.h"

#include "../main.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

char
local_player_team(int index)
{
  void *pointer  = client_base + 0x000D72C0;
  char team;

  if (index == 0) {
    pointer  = client_base + 0x000B9EAC;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + PLAYER_TEAM_OFFSET, &team, 1) > 0) {
            return team;
          }
      }
    }
  } else {
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + PLAYER_TEAM_OFFSET, &team, 1) > 0) {
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
  void *pointer  = client_base + 0x000D72C0;
  char health;

  if (index == 0) {
    pointer  = client_base + 0x000B9EAC;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + PLAYER_HEALTH_OFFSET, &health, 1) > 0) {
            return health;
          }
      }
    }
  } else {
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + PLAYER_HEALTH_OFFSET, &health, 1) > 0) {
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
  void *pointer  = client_base + 0x000D72C0;
  char dead_flag;

  if (index == 0) {
    pointer  = client_base + 0x000B9EAC;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + PLAYER_DEAD_FLAG_OFFSET, &dead_flag, 1) > 0) {
            return dead_flag;
          }
      }
    }
  } else {
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + PLAYER_DEAD_FLAG_OFFSET, &dead_flag, 1) > 0) {
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
  void *pointer  = client_base + 0x000D72C0;
  float pos_x;

  if (index == 0) {
    pointer  = client_base + 0x000B9EAC;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + PLAYER_POS_X_OFFSET, &pos_x, 4) == 4) {
            return pos_x;
          }
      }
    }
  } else {
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + PLAYER_POS_X_OFFSET, &pos_x, 4) == 4) {
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
  void *pointer  = client_base + 0x000D72C0;
  float pos_y;

  if (index == 0) {
    pointer  = client_base + 0x000B9EAC;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + PLAYER_POS_Y_OFFSET, &pos_y, 4) == 4) {
            return pos_y;
          }
      }
    }
  } else {
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + PLAYER_POS_Y_OFFSET, &pos_y, 4) == 4) {
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
  void *pointer  = client_base + 0x000D72C0;
  float pos_z;

  if (index == 0) {
    pointer  = client_base + 0x000B9EAC;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + PLAYER_POS_Z_OFFSET, &pos_z, 4) == 4) {
            return pos_z;
          }
      }
    }
  } else {
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + PLAYER_POS_Z_OFFSET, &pos_z, 4) == 4) {
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
  void *pointer  = client_base + 0x000D72C0;
  vector3 pos = { -1, -1, -1 };

  if (index == 0) {
    pointer  = client_base + 0x000B9EAC;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + PLAYER_POS_X_OFFSET, &pos, 12) == 12) {
            return pos;
          }
      }
    }
  } else {
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + PLAYER_POS_X_OFFSET, &pos, 12) == 12) {
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
  void *pointer  = client_base + 0x000D72C0;
  float yaw;

  if (index == 0) {
    pointer  = client_base + 0x000B9EAC;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + PLAYER_YAW_OFFSET, &yaw, 4) == 4) {
            return yaw;
          }
      }
    }
  } else {
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + PLAYER_YAW_OFFSET, &yaw, 4) == 4) {
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
  void *pointer  = client_base + 0x000D72C0;
  float pitch;

  if (index == 0) {
    pointer  = client_base + 0x000B9EAC;
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
          if (memory_read(ins_pid, pointer + PLAYER_PITCH_OFFSET, &pitch, 4) == 4) {
            return pitch;
          }
      }
    }
  } else {
    if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
      if (memory_read(ins_pid, pointer + (0x14 + (0x10 * (index - 1))), &pointer, 4) == 4) {
        if (memory_read(ins_pid, pointer + PLAYER_PITCH_OFFSET, &pitch, 4) == 4) {
          return pitch;
        }
      }
    }
  }

  return -1;
}

float
player_fov(void)
{
  void *pointer = client_base + 0x000B763C;
  float fov;

  if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
    if (memory_read(ins_pid, pointer + 0x25C, &fov, 4) == 4) {
      return fov;
    }
  }

  return -1;
}
