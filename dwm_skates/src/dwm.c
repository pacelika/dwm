#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <dwm_skates/wm_func_def.h>

int main(int argc, char *argv[]) {
  wm_init(argc, argv);
  return EXIT_SUCCESS;
}
