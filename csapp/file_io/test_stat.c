#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct stat statbuf;
  const char *type;
  const char *readok;

  if (argc < 2) {
    fprintf(stderr, "%s\n", "usage: test_stat <filename> <filename> ...");
    exit(1);
  }

  for (int i = 1; i < argc; ++i) {
    stat(argv[i], &statbuf);
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

    fprintf(stdout, "%s:\ntype: %s, read: %s\n", argv[i], type, readok);
  }

  return 0;
}