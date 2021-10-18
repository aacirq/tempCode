#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  struct stat statbuf;
  const char *type;
  const char *readok;

  if (argc != 2) {
    fprintf(stderr, "%s\n", "usage: fstatcheck <file_descriptor>");
    exit(1);
  }

  if (fstat(atoi(argv[1]), &statbuf) < 0) {
    fprintf(stderr, "error: %s\n", strerror(errno));
    exit(1);
  }
  if (S_ISREG(statbuf.st_mode)) {
    type = "regular";
  } else if (S_ISDIR(statbuf.st_mode)) {
    type = "directory";
  } else {
    type = "other";
  }

  if (statbuf.st_mode & S_IRUSR) {
    readok = "yes";
  } else {
    readok = "no";
  }

  fprintf(stdout, "type: %s, read: %s\n", type, readok);

  return 0;
}