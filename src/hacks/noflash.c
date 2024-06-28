#include "noflash.h"

#include "../main.h"
#include "../utils/utils.h"

#ifdef UNSAFE
void
noflash(void) {
  void  *pointer  = client_base + OFFSET_CLIENT_BASE_1;
  float max_alpha = 1;

  if (memory_read(ins_pid, pointer, &pointer, 4) == 4) {
    if (memory_read(ins_pid, pointer + 0x4, &pointer, 4) == 4) {
      memory_write(ins_pid, pointer + OFFSET_PLAYER_MAX_ALPHA, &max_alpha, 4);
    }
  }
}
#endif
