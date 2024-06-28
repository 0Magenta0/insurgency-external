#define _GNU_SOURCE

#include "memory.h"

#include <sys/uio.h>

ssize_t
memory_read(pid_t pid, void *addr, void *buf, size_t buf_len)
{
  struct iovec local[1];
  struct iovec remote[1];
  ssize_t read;

  local[0].iov_base = buf;
  local[0].iov_len = buf_len;
  remote[0].iov_base = addr;
  remote[0].iov_len = buf_len;

  read = process_vm_readv(pid, local, 1, remote, 1, 0);

  return read;
}

/*
ssize_t
memory_write(pid_t pid, void *addr, void *buf, size_t buf_len)
{
  struct iovec local[1];
  struct iovec remote[1];
  ssize_t read;

  local[0].iov_base = buf;
  local[0].iov_len = buf_len;
  remote[0].iov_base = addr;
  remote[0].iov_len = buf_len;

  read = process_vm_writev(pid, local, 1, remote, 1, 0);

  return read;
}
*/
