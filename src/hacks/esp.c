/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include "esp.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <strings.h>

#include "../utils/utils.h"
#include "../main.h"

void
draw_esp(struct xcb_connection_t *connection,
         struct xcb_screen_t     *screen,
         xcb_window_t            window,
         xcb_gcontext_t          gc)
{
  xcb_rectangle_t rect = { 0, 0, ESP_RECT_SIZE, ESP_RECT_SIZE };
  vector3 player_pos = local_player_pos(0);
  vector3 remote_player_pos;
  vector2 angles = { local_player_pitch(0),
                     local_player_yaw(0) };
  enum team player_team = local_player_team(0);
  float fov = player_fov();
  float distance;
  vector2 screen_pos;
  color color;
  char buf[16];

  for (int i = 1; i <= 32; ++i) {
    if ((local_player_health(i) > 0 && local_player_dead_flag(i) == 0)) {
      remote_player_pos = local_player_pos(i);

      if (is_zero_pos(remote_player_pos)) {
        continue;
      }

      if (is_vector3_equals(remote_player_pos, player_pos)) {
        /* May be it fixes dead-alive players problem?
        if (local_player_yaw(i) == 0 && local_player_pitch(i) == 0) {
          puts("PIZDOS");
        } */
        continue;
      }



      if (player_team == local_player_team(i)) {
        color.c = 0x0000FFFF;
      } else {
        color.c = 0x00FF0000;
      }

      screen_pos = world_to_screen(player_pos, remote_player_pos, angles, fov, screen->width_in_pixels, screen->height_in_pixels);

      rect.x = screen_pos.x;
      rect.y = screen_pos.y;
      set_foreground_color(connection, gc, color);
      xcb_poly_rectangle(connection, window, gc, 1, &rect);

      bzero(buf, 16);
      snprintf(buf, 16, "%d", local_player_health(i));
      xcb_image_text_8(connection, strlen(buf), window, gc, rect.x, rect.y - 1, buf);


      distance = vector3_distance(player_pos, remote_player_pos) * 0.0254;

      if (distance > 90) {
        color.c = ESP_COLOR_FAR_RANGE;
      } else if (distance > 50) {
        color.c = ESP_COLOR_NORMAL_RANGE;
      } else if (distance > 25) {
        color.c = ESP_COLOR_WARN_RANGE;
      } else {
        color.c = ESP_COLOR_DANGER_RANGE;
      }

      bzero(buf, 16);
      snprintf(buf, 16, "%.f", distance);
      set_foreground_color(connection, gc, color);
      xcb_image_text_8(connection, strlen(buf), window, gc, rect.x, rect.y + ESP_RECT_SIZE * 2, buf);
    }
  }
}









