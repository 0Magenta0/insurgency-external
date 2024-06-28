/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#pragma once

#include <sys/types.h>

/*
 * Returns pid by it's name.
 * On error returns -1.
 */
pid_t
pid_by_name(const char *name);

/*
 * Returns base address.
 * On error returns NULL.
 */
void *
module_rw_base(const char *module_name, pid_t ins_pid);
