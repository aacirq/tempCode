#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "apue.h"

typedef int Myfunc(const char *, const struct stat *, int);

static int myfunc(const char *filename, const struct stat *statbuf, int type);
static int myftw(const char *pathname, Myfunc *func);
static int dopath(Myfunc *func);

static int64_t ntot, nreg, ndir, nchr, nblk, nfifo, nslnk, nsock;

int main(int argc, char *argv[]) {
  int ret;

  if (argc < 2) {
    fprintf(stderr, "%s\n", "usage: a.out <directory>");
    exit(1);
  }

  ret = myftw(argv[1], myfunc);

  ntot = nreg + ndir + nchr + nblk + nfifo + nslnk + nsock;
  printf("regular files  = %7ld, %5.2f %%\n", nreg, 100.0 * nreg / ntot);
  printf("directory      = %7ld, %5.2f %%\n", ndir, 100.0 * ndir / ntot);
  printf("char special   = %7ld, %5.2f %%\n", nchr, 100.0 * nchr / ntot);
  printf("block special  = %7ld, %5.2f %%\n", nblk, 100.0 * nblk / ntot);
  printf("fifos          = %7ld, %5.2f %%\n", nfifo, 100.0 * nfifo / ntot);
  printf("symbolic links = %7ld, %5.2f %%\n", nslnk, 100.0 * nslnk / ntot);
  printf("sockets        = %7ld, %5.2f %%\n", nsock, 100.0 * nsock / ntot);

  return 0;
}

#define FTW_F 1    // file other than directory
#define FTW_D 2    // directory
#define FTW_DNR 3  // directory that can not be read
#define FTW_NS 4   // file that we can not stat

static char *fullpath;
static size_t pathlen;

static int myftw(const char *pathname, Myfunc *func) {
  fullpath = path_alloc(&pathlen);

  if (pathlen <= strlen(pathname)) {
    pathlen = 2 * strlen(pathname);
    if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
      err_sys("realloc failed");
    }
  }
  strcpy(fullpath, pathname);
  return dopath(func);
}

static int dopath(Myfunc *func) {
  struct stat statbuf;
  struct dirent *dirp;
  DIR *dp;
  int ret, n;

  if (lstat(fullpath, &statbuf) < 0) {
    return func(fullpath, &statbuf, FTW_NS);
  }
  if (S_ISDIR(statbuf.st_mode) == 0) {
    return func(fullpath, &statbuf, FTW_F);
  }

  func(fullpath, &statbuf, FTW_D);
  n = strlen(fullpath);
  if (n + 4096 + 2 > pathlen) {
    pathlen *= 2;
    if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
      err_sys("realloc failed");
    }
  }
  fullpath[n++] = '/';
  fullpath[n] = '\0';
  if ((dp = opendir(fullpath)) == NULL) {
    return func(fullpath, &statbuf, FTW_DNR);
  }

  while ((dirp = readdir(dp)) != NULL) {
    if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
      continue;
    strcpy(fullpath + n, dirp->d_name);
    if ((ret = dopath(func)) != 0) break;
  }
  fullpath[n - 1] = '\0';
  if (closedir(dp) < 0) err_ret("can not close directory %s", fullpath);
  return 0;
}

static int myfunc(const char *filename, const struct stat *statbuf, int type) {
  mode_t md;

  switch (type) {
    case FTW_F:
      md = statbuf->st_mode;
      switch (statbuf->st_mode & __S_IFMT) {
        case __S_IFREG:
          ++nreg;
          break;
        case __S_IFCHR:
          ++nchr;
          break;
        case __S_IFBLK:
          ++nblk;
          break;
        case __S_IFIFO:
          ++nfifo;
          break;
        case __S_IFLNK:
          ++nslnk;
          break;
        case __S_IFSOCK:
          ++nsock;
          break;
        case __S_IFDIR:
          err_dump("for __S_IFDIR for %s", filename);
          break;
      }
      break;
    case FTW_D:
      ++ndir;
      break;
    case FTW_DNR:
      err_ret("can not read directory %s", filename);
      break;
    case FTW_NS:
      err_ret("can not stat file %s", filename);
      break;
    default:
      err_dump("unknown type %d for pathname %s", type, filename);
      break;
  }

  return 0;
}
