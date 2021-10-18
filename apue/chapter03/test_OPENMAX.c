#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

int main() {
#ifdef OPEN_MAX
  printf("%s\n", OPEN_MAX);
#else
  printf("no symbol for OPEN_MAX\n");
#endif

#ifdef _SC_OPEN_MAX
  long val;
  if ((val = sysconf(_SC_OPEN_MAX)) < 0) {
    if (errno != 0) {
      if (errno == EINVAL) {
        printf(" (no support)");
      } else {
        fprintf(stderr, "sysconf error");
      }
    } else {
      printf(" (no limits)\n");
    }
  } else {
    printf("%ld\n", val);
  }
#else
  printf("no symbol for _SC_OPEN_MAX");
#endif
  return 0;
}