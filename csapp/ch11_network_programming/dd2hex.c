#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
  uint32_t host;
  int rc;
  
  if (argc < 2) {
    fprintf(stderr, "usage: ./dd2hex <dot-dicimal> <dot-dicimal> ...\n");
    exit(1);
  }

  for (int i = 1; i < argc; ++i) {
    fprintf(stdout, "%s -> ", argv[i]);
    if ((rc = inet_pton(AF_INET, argv[i], &host)) < 0) {
      fprintf(stderr, "error: inet_pton %s\n", strerror(errno));
      exit(1);
    } else if (rc == 0) {
      fprintf(stdout, "invalid ip\n");
    } else {
      host = ntohl(host);
      fprintf(stdout, "0x%x\n", host);
    }
  }

  return 0;
}