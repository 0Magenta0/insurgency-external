#include "crosshair.h"

#include <xcb/xcb.h>

#include "../utils/utils.h"
#include "../main.h"

void
draw_crosshair(struct xcb_connection_t *connection,
               struct xcb_screen_t     *screen,
               xcb_window_t            window,
               xcb_gcontext_t          gc)
{
  struct xcb_point_t vertical_points[2] = {
    { screen->width_in_pixels / 2,
      screen->height_in_pixels / 2 - CROSSHAIR_SIZE
    },
    { screen->width_in_pixels / 2,
      screen->height_in_pixels / 2 + CROSSHAIR_SIZE
    }
  };

  struct xcb_point_t horizontal_points[2] = {
    { screen->width_in_pixels / 2 - CROSSHAIR_SIZE,
      screen->height_in_pixels / 2
    },
    {
      screen->width_in_pixels / 2 + CROSSHAIR_SIZE,
      screen->height_in_pixels / 2
    }
  };

  color color = { .c = CROSSHAIR_COLOR_NORMAL };

  set_foreground_color(connection, gc, color);
  xcb_poly_line(connection, XCB_COORD_MODE_ORIGIN, window, gc, 2, vertical_points);
  xcb_poly_line(connection, XCB_COORD_MODE_ORIGIN, window, gc, 2, horizontal_points);
}
