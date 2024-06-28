/*
 * https://github.com/0Magenta0/insurgency-external
 * Copyright 0Magenta0 2024
 * MIT License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>

#include "procfs.h"
#include "hex.h"

pid_t
pid_by_name(const char *name)
{
  DIR           *procfs_dir;
  struct dirent *procfs_dirent;
  char          buf[28];
  FILE          *f;

  if (name == NULL) {
    return -1;
  }

  if ((procfs_dir = opendir("/proc/")) == NULL) {
    return -1;
  }

  while ((procfs_dirent = readdir(procfs_dir)) != NULL) {
    bzero(buf, sizeof(buf));
    snprintf(buf, strlen(procfs_dirent->d_name) + 12, "/proc/%s/comm", procfs_dirent->d_name); // Just don't care about SEGV...
    if ((f = fopen(buf, "r")) == NULL) {
      continue;
    }

    bzero(buf, sizeof(buf));
    if (fgets(buf, sizeof(buf), f)) {
      if (!strncmp(buf, name, strlen(name))) {
        return (pid_t) atoi(procfs_dirent->d_name);
      }
    }
  }

  return -1;
}

void *
module_rw_base(const char *module_name, pid_t ins_pid)
{
  char buf[1024];
  char *file_line;
  size_t line_len;
  size_t module_len = strlen(module_name);
  size_t read;
  uint32_t base_addr = 0;
  FILE *f;

  bzero(buf, sizeof(buf));
  snprintf(buf, 1024, "/proc/%d/maps", ins_pid);
  if ((f = fopen(buf, "r")) == NULL) {
    return NULL;
  }

  while ((read = getline(&file_line, &line_len, f)) >= 0) {
    file_line[read - 1] = 0;
    if (!strcmp(file_line + read - module_len - 1, module_name)) {
      if (!strncmp(file_line + 18, "rw-p", 4)) {
        for (int i = 0; i < 8; i += 2) {
          base_addr |= hex_to_byte(file_line[i]) << ((7 - i) * 4);
          base_addr |= hex_to_byte(file_line[i + 1]) << ((7 - i - 1) * 4);
        }

        return (void *) base_addr;
      }
    }
  }

  return NULL;
}
