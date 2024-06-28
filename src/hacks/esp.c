/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include "esp.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "../utils/utils.h"
#include "../main.h"

#define BUF_SIZE 16

void
draw_esp(struct xcb_connection_t *connection,
         struct xcb_screen_t     *screen,
         xcb_window_t            window,
         xcb_gcontext_t          gc)
{
  float     player_fov      = local_player_fov();
  team      player_team     = local_player_team(0);
  vector3   player_pos      = local_player_pos(0);
  vector2   player_rotation = {
    local_player_pitch(0),
    local_player_yaw(0) 
  };

  color           color;
  char            buf[BUF_SIZE];
  xcb_rectangle_t rect = {
    0,
    0,
    ESP_RECT_SIZE,
    ESP_RECT_SIZE
  };

  float   distance;
  vector2 screen_pos;
  vector3 remote_player_pos;

  for (int i = 1; i <= 32; ++i) {
    if ((local_player_health(i) > 0 && local_player_dead_flag(i) == 0)) {
      remote_player_pos = local_player_pos(i);

      if (is_vector3_zero(remote_player_pos)) {
        continue;
      }

      if (is_vector3_equals(remote_player_pos, player_pos)) {
        continue;
      }

      screen_pos = world_to_screen(player_pos,
                                   remote_player_pos,
                                   player_rotation,
                                   player_fov,
                                   screen->width_in_pixels,
                                   screen->height_in_pixels);

      rect.x  = screen_pos.x;
      rect.y  = screen_pos.y;
      color.c = player_team == local_player_team(i) ? ESP_COLOR_FRIEND
                                                    : ESP_COLOR_ENEMY;
      set_foreground_color(connection, gc, color);
      xcb_poly_rectangle(connection, window, gc, 1, &rect);

      bzero(buf, BUF_SIZE);
      snprintf(buf, BUF_SIZE, "%d", local_player_health(i));
      xcb_image_text_8(connection,
                       strlen(buf),
                       window,
                       gc,
                       rect.x,
                       rect.y - 1,
                       buf);

      distance = units_to_meters(vector3_distance(player_pos, remote_player_pos));

      if (distance > 90) {
        color.c = ESP_COLOR_FAR_RANGE;
      } else if (distance > 50) {
        color.c = ESP_COLOR_NORMAL_RANGE;
      } else if (distance > 25) {
        color.c = ESP_COLOR_WARN_RANGE;
      } else {
        color.c = ESP_COLOR_DANGER_RANGE;
      }

      bzero(buf, BUF_SIZE);
      snprintf(buf, BUF_SIZE, "%.f", distance);
      set_foreground_color(connection, gc, color);
      xcb_image_text_8(connection,
                       strlen(buf),
                       window,
                       gc,
                       rect.x,
                       rect.y + ESP_RECT_SIZE * 2,
                       buf);
    }
  }
}









