#include "apue.h"
#include <errno.h>
#include <stdarg.h>
#include <limits.h>

static void err_doit(int, int, const char *, va_list);

void err_dump(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  abort();
  exit(1);
}

void err_ret(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
}

void err_sys(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  exit(1);
}

void err_quit(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
  exit(1);
}

static void err_doit(int errnoflag, int error, const char *fmt, va_list ap) {
  char buf[MAXLINE];
  int tmp_len;

  vsnprintf(buf, MAXLINE - 1, fmt, ap);
  tmp_len = strlen(buf);
  if (errnoflag)
    snprintf(buf + tmp_len, MAXLINE - tmp_len - 1, ": %s", strerror(error));
  strcat(buf, "\n");
  fflush(stdout);
  fputs(buf, stderr);
  fflush(NULL);
}

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

#define PATH_MAX_GUESS 4096

char *path_alloc(size_t *sizep) {
  char* ptr;
  size_t size;

  if (posix_version == 0) {
    posix_version = sysconf(_SC_VERSION);
  }

  if (xsi_version == 0) {
    xsi_version = sysconf(_SC_XOPEN_VERSION);
  }

  if (pathmax == 0) {
    errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
      if (errno == 0) {
        pathmax = PATH_MAX_GUESS;
      } else {
        err_sys("pathconf error for _PC_PATH_MAX");
      }
    } else {
      pathmax++;
    }
  }

  if ((posix_version < 200112L) && (xsi_version < 4)) {
    size = pathmax + 1;
  } else {
    size = pathmax;
  }

  if ((ptr = malloc(size)) == NULL)
    err_sys("malloc error for pathname");

  if (sizep != NULL)
    *sizep = size;

  return ptr;
}
