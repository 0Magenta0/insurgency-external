#include <unistd.h>

#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/shape.h>
#include <xcb/xfixes.h>
#include <xcb/dbe.h>
#include <xcb/composite.h>

#include <stdio.h>

#include "colors.h"
#include "overlay.h"
#include "player_info.h"

#include "../hacks/hacks.h"

struct xcb_connection_t *connection;
struct xcb_screen_t     *screen;
xcb_visualid_t          visual;
xcb_window_t            window;
xcb_xfixes_region_t     region;
xcb_dbe_back_buffer_t   back_buffer;
xcb_gcontext_t          gc;

// TODO: DONT_PROPAGATE | EVENT_MASK is needed?
const uint32_t mask = XCB_CW_BACK_PIXEL    |
                  XCB_CW_BORDER_PIXEL      |
                  XCB_CW_BIT_GRAVITY       |
                  XCB_CW_WIN_GRAVITY       |
                  XCB_CW_OVERRIDE_REDIRECT |
                  XCB_CW_SAVE_UNDER        |
                  XCB_CW_EVENT_MASK        |
                  XCB_CW_DONT_PROPAGATE    |
                  XCB_CW_COLORMAP;

static xcb_visualid_t
visualid_by_depth(uint16_t depth);

static void 
clear_screen(void);

int
init_overlay(void)
{
  if ((connection = xcb_connect(NULL, NULL)) == NULL) {
    return -1;
  }

  if ((screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data) == NULL) {
    xcb_disconnect(connection);
    return -1;
  }

  xcb_colormap_t colormap = xcb_generate_id(connection);
  const uint32_t mask_values[] = {
    0x00000000,
    0,
    0,
    1,
    1,
    1,
    XCB_EVENT_MASK_STRUCTURE_NOTIFY |
      XCB_EVENT_MASK_EXPOSURE |
      XCB_EVENT_MASK_PROPERTY_CHANGE |
      XCB_EVENT_MASK_ENTER_WINDOW |
      XCB_EVENT_MASK_LEAVE_WINDOW |
      XCB_EVENT_MASK_KEY_PRESS |
      XCB_EVENT_MASK_KEY_RELEASE |
      XCB_EVENT_MASK_KEYMAP_STATE,
    XCB_EVENT_MASK_KEY_PRESS |
      XCB_EVENT_MASK_KEY_RELEASE |
      XCB_EVENT_MASK_BUTTON_PRESS |
      XCB_EVENT_MASK_BUTTON_RELEASE |
      XCB_EVENT_MASK_POINTER_MOTION |
      XCB_EVENT_MASK_BUTTON_MOTION,
    colormap
  };

  if((visual = visualid_by_depth(32)) == 0) {
    xcb_disconnect(connection);
    return -1;
  }

  xcb_create_colormap(connection, XCB_COLORMAP_ALLOC_NONE, colormap, screen->root, visual);

  window = xcb_generate_id(connection);
  xcb_create_window(connection,
                    32,
                    window,
                    screen->root,
                    0, 0,
                    screen->width_in_pixels,
                    screen->height_in_pixels,
                    0,
                    XCB_WINDOW_CLASS_INPUT_OUTPUT,
                    visual,
                    mask,
                    mask_values);


  xcb_shape_mask(connection, XCB_SHAPE_SO_SET, XCB_SHAPE_SK_BOUNDING, window, 0, 0, 0);
  xcb_shape_rectangles(connection, XCB_SHAPE_SO_SET, XCB_SHAPE_SK_INPUT, XCB_CLIP_ORDERING_UNSORTED, window, 0, 0, 0, NULL);

  region = xcb_generate_id(connection);
  xcb_xfixes_create_region(connection, region, 0, NULL);
  xcb_xfixes_set_window_shape_region(connection, window, XCB_SHAPE_SK_INPUT, 0, 0, region);
  xcb_xfixes_destroy_region(connection, region);

  back_buffer = xcb_generate_id(connection);
  xcb_dbe_allocate_back_buffer(connection, window, back_buffer, 0);

  xcb_map_window(connection, window);

  gc = xcb_generate_id(connection);
  xcb_create_gc(connection, gc, window, 0, NULL);

  xcb_flush(connection);
  return 0;
}

void
draw_overlay_loop(void)
{
  for (;;) {
    clear_screen();
    if (local_player_health(0) > 0 && local_player_dead_flag(0) == 0) {
      draw_crosshair(connection, screen, window, gc);
      draw_radar(connection, screen, window, gc);
      draw_hud(connection, screen, window, gc);
      draw_esp(connection, screen, window, gc);
    }

    xcb_dbe_swap_buffers(connection, 0, NULL);
    xcb_flush(connection);
    usleep(10000 / 60);
  }

  xcb_free_gc(connection, gc); 
}

static xcb_visualid_t
visualid_by_depth(uint16_t depth)
{
  xcb_depth_iterator_t depth_iterator;
  xcb_visualtype_iterator_t visual_iterator;

  depth_iterator = xcb_screen_allowed_depths_iterator(screen);
  for (; depth_iterator.rem; xcb_depth_next(&depth_iterator)) {
    if (depth_iterator.data->depth != depth) {
      continue;
    }

    visual_iterator = xcb_depth_visuals_iterator(depth_iterator.data);
    if (!visual_iterator.rem) {
      continue;
    }

    return visual_iterator.data->visual_id;
  }

  return 0;
}

static void
clear_screen(void)
{
  color color = { .c = 0x00000000 };
  xcb_rectangle_t screen_rect = { 0, 0, screen->width_in_pixels, screen->height_in_pixels };

  set_foreground_color(connection, gc, color);
  xcb_poly_fill_rectangle(connection, window, gc, 1, &screen_rect);
}
