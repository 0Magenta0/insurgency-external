/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#pragma once

#include <stdint.h>

#include <xcb/xcb.h>

typedef union {
  uint32_t c;
  struct {
    uint8_t alpha;
    uint8_t red;
    uint8_t green;
    uint8_t blue;   
  } argb;
} color;


void
set_foreground_color(struct xcb_connection_t *connection,
                     xcb_gcontext_t          gc,
                     color color);

void
set_background_color(struct xcb_connection_t *connection,
                     xcb_gcontext_t gc,
                     color color);
