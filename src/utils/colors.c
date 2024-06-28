/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include "colors.h"

#include <xcb/xcb.h>

void
set_foreground_color(struct xcb_connection_t *connection,
                     xcb_gcontext_t          gc,
                     color color)
{
  uint32_t values[] = { color.c };

  xcb_change_gc(connection, gc, XCB_GC_FOREGROUND, values);
}

void
set_background_color(struct xcb_connection_t *connection,
                     xcb_gcontext_t          gc,
                     color                   color)
{
  uint32_t values[] = { color.c };

  xcb_change_gc(connection, gc, XCB_GC_BACKGROUND, values);
}
