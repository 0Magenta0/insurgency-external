/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include "radar.h"

#include <math.h>

#include <xcb/xcb.h>

#include "../utils/utils.h"
#include "../main.h"

static void
draw_player(struct xcb_connection_t *connection,
            xcb_window_t            window,
            xcb_gcontext_t          gc,
            vector2                 *pos,
            uint32_t                player_color,
            int                     fy);

void
draw_radar(struct xcb_connection_t *connection,
           struct xcb_screen_t     *screen,
           xcb_window_t            window,
           xcb_gcontext_t          gc)
{
  team    player_team = local_player_team(0);
  float   player_yaw  = local_player_yaw(0);
  vector3 player_pos  = local_player_pos(0);
  vector2 radar_player_pos;

  struct xcb_point_t yaw_points[2];
  vector3            remote_player_pos;
  vector2            radar_pos = {
    (float) screen->width_in_pixels / 2 - (float) RADAR_SIZE / 2,
    0
  };
  float           min_x_pos;
  float           max_x_pos;
  float           min_z_pos;
  float           max_z_pos;
  float           min_radar_pos = 5;
  float           max_radar_pos = RADAR_SIZE - 5;
  float           delta_x;
  float           delta_y;
  float           floor_y;
  color           color;
  xcb_rectangle_t rect = {
    0,
    0,
    RADAR_SIZE,
    RADAR_SIZE
  };

  rect.x = radar_pos.x;
  rect.y = radar_pos.y;
  color.c = RADAR_COLOR_BORDER;
  set_foreground_color(connection, gc, color);
  xcb_poly_rectangle(connection, window, gc, 1, &rect);

  rect.x += 1;
  rect.y += 1;
  rect.width  -= 1;
  rect.height -= 1;
  color.c = RADAR_COLOR_BACKGROUND;
  set_foreground_color(connection, gc, color);
  xcb_poly_fill_rectangle(connection, window, gc, 1, &rect);

  radar_player_pos.x = radar_pos.x + (float) RADAR_SIZE / 2;
  radar_player_pos.y = radar_pos.y + (float) RADAR_SIZE / 2;
  draw_player(connection, window, gc, &radar_player_pos, RADAR_COLOR_PLAYER, 0);

  delta_x = RADAR_YAW_LINE * sin(to_radian(player_yaw));
  delta_y = RADAR_YAW_LINE * cos(to_radian(player_yaw));

  yaw_points[0].x = radar_player_pos.x - 1;
  yaw_points[0].y = radar_player_pos.y - 1;
  yaw_points[1].x = radar_player_pos.x + delta_x;
  yaw_points[1].y = radar_player_pos.y + delta_y;

  color.c = RADAR_COLOR_YAW_LINE;
  set_foreground_color(connection, gc, color);
  xcb_poly_line(connection, XCB_COORD_MODE_ORIGIN, window, gc, 2, yaw_points);

  min_x_pos = player_pos.x - ((float) RADAR_RANGE / 2);
  max_x_pos = player_pos.x + ((float) RADAR_RANGE / 2);
  min_z_pos = player_pos.z - ((float) RADAR_RANGE / 2);
  max_z_pos = player_pos.z + ((float) RADAR_RANGE / 2);

  for (int i = 1; i <= 32; ++i) {
    if ((local_player_health(i) > 0 && local_player_dead_flag(i) == 0)) {
      remote_player_pos = local_player_pos(i);

      if (is_vector3_zero(remote_player_pos)) {
        continue;
      }

      if (remote_player_pos.x > max_x_pos || remote_player_pos.x < min_x_pos ||
          remote_player_pos.z > max_z_pos || remote_player_pos.z < min_z_pos) {
        continue;
      }

      if (is_vector3_equals(remote_player_pos, player_pos)) {
        continue;
      }

      radar_player_pos.x = radar_pos.x + ((remote_player_pos.x - min_x_pos) /
                           (max_x_pos - min_x_pos)) *
                           (max_radar_pos - min_radar_pos) + min_radar_pos;

      radar_player_pos.y = radar_pos.y + ((remote_player_pos.z - min_z_pos) /
                           (max_z_pos - min_z_pos)) *
                           (max_radar_pos - min_radar_pos) + min_radar_pos;

      floor_y = 0;
      if (remote_player_pos.y < player_pos.y - RADAR_PLAYER_FLOOR) {
        floor_y = -1;
      } else if (remote_player_pos.y > player_pos.y + RADAR_PLAYER_FLOOR) {
        floor_y = 1;
      }

      draw_player(connection,
                  window,
                  gc,
                  &radar_player_pos,
                  player_team == local_player_team(i) ? RADAR_COLOR_FRIENDLY
                                                      : RADAR_COLOR_ENEMY,
                  floor_y);
    }
  }
}

static void
draw_player(struct xcb_connection_t *connection,
            xcb_window_t            window,
            xcb_gcontext_t          gc,
            vector2                 *pos,
            uint32_t                player_color,
            int                     fy)
{
  color           color;
  xcb_rectangle_t rect = {
    pos->x - ((float) RADAR_PLAYER_SIZE / 2),
    pos->y - ((float) RADAR_PLAYER_SIZE / 2),
    RADAR_PLAYER_SIZE,
    RADAR_PLAYER_SIZE
  };
  struct xcb_point_t left_floor_points[2] = {
    {
      rect.x,
      fy > 0 ? rect.y : rect.y + RADAR_PLAYER_SIZE
    },
    {
      rect.x + RADAR_PLAYER_SIZE / 2,
      fy > 0 ? rect.y - 5 : rect.y + RADAR_PLAYER_SIZE + 5
    }
  };
  struct xcb_point_t right_floor_points[2] = {
    {
      rect.x - 1 + RADAR_PLAYER_SIZE,
      fy > 0 ? rect.y : rect.y + RADAR_PLAYER_SIZE
    },
    {
      rect.x + RADAR_PLAYER_SIZE / 2,
      fy > 0 ? rect.y - 5 : rect.y + RADAR_PLAYER_SIZE + 5
    }
  };

  color.c = player_color;
  set_foreground_color(connection, gc, color);
  xcb_poly_fill_rectangle(connection, window, gc, 1, &rect);

  if (fy) {
    xcb_poly_line(connection,
                  XCB_COORD_MODE_ORIGIN,
                  window,
                  gc,
                  2,
                  left_floor_points);
    xcb_poly_line(connection,
                  XCB_COORD_MODE_ORIGIN,
                  window,
                  gc,
                  2,
                  right_floor_points);
  }
}
