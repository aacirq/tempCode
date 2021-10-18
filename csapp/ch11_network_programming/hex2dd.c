#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  uint32_t num;
  char addr_buf[16];
  const char *res;

  if (argc < 2) {
    fprintf(stderr, "usage: ./hex2dd <hex-num> <hex-num> ...\n");
    exit(1);
  }

  for (int i = 1; i < argc; ++i) {
    sscanf(argv[i], "%x", &num);
    num = htonl(num);
    if ((res = inet_ntop(AF_INET, &num, addr_buf, 16)) == NULL) {
      fprintf(stderr, "error: inet_ntop %s\n", strerror(errno));
      exit(1);
    }
    fprintf(stdout, "%s -> %s\n", argv[i], res);
  }

  return 0;
}