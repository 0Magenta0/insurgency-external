/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include "hud.h"

#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "../utils/utils.h"
#include "../main.h"

void
draw_hud(struct xcb_connection_t *connection,
         struct xcb_screen_t     *screen,
         xcb_window_t            window,
         xcb_gcontext_t          gc)
{
  char buf[64];
  char health = local_player_health(0);
  color color = { .c = (health > 30 ? HUD_NORMAL_HP : HUD_DANGER_HP) };

  set_foreground_color(connection, gc, color);

  bzero(buf, 64);
  snprintf(buf, 64, "HP: %d", health);
  xcb_image_text_8(connection, strlen(buf), window, gc, screen->width_in_pixels / 2 - RADAR_SIZE / 2, 300, buf);
}
