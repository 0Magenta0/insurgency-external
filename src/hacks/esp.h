/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#pragma once

#include <xcb/xcb.h>

void
draw_esp(struct xcb_connection_t *connection,
         struct xcb_screen_t     *screen,
         xcb_window_t            window,
         xcb_gcontext_t          gc);
