#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  DIR *streamp;
  struct dirent *dir;

  if (argc < 2) {
    fprintf(stderr, "%s\n", "usage: test_readdir <dirname> <dirname> ...");
    exit(1);
  }

  for (int i = 1; i < argc; ++i) {
    fprintf(stdout, "IN dir %s\n", argv[i]);
    streamp = opendir(argv[i]);
    while ((dir = readdir(streamp)) != NULL) {
      fprintf(stdout, "%s ", dir->d_name);
    }
    fprintf(stdout, "\n");
  }

  return 0;
}