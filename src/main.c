/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include <stdio.h>
#include <unistd.h>

#include <xcb/xcb.h>

#include "utils/utils.h"

#include "main.h"

pid_t ins_pid;

void *client_base;
/* void *engine_base; */

int
main(void)
{
  if (getuid()) {
    fprintf(stderr, "Must run as root.\n");
    return 1;
  }

  if ((ins_pid = pid_by_name(PROCESS_NAME)) < 0) {
    fprintf(stderr, "Insurgency PID not found!\n");
    return 2;
  }

  if ((client_base = module_rw_base("bin/client.so", ins_pid)) == NULL) {
    fprintf(stderr, "R/W base of the bin/client.so not found!\n");
    return 3;
  } /* if ((engine_base = module_rw_base("bin/engine.so", ins_pid)) == NULL) {
    fprintf(stderr, "R/W base of the bin/engine.so not found!\n");
    return 3;
  } */

  if (init_overlay() < 0) {
    fprintf(stderr, "Cannot initialize an overlay!\n");
    return 4;
  }

  draw_overlay_loop();

  return 0;
}

