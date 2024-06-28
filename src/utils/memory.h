/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#pragma once

#include <sys/types.h>

ssize_t
memory_read(pid_t pid, void *addr, void *buf, size_t buf_len);

ssize_t
memory_write(pid_t pid, void *addr, void *buf, size_t buf_len);
