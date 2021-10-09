#include "rio.h"

#include <errno.h>
#include <memory.h>
#include <unistd.h>

/**
 * Read n bytes (unbuffered)
 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n) {
  ssize_t nleft = n;
  ssize_t nread = 0;
  char *buf = (char *)usrbuf;

  while (nleft > 0) {
    if ((nread = read(fd, buf, nleft)) < 0) {
      if (errno == EINTR) {  // This call was interrupted by signal
        nread = 0;
      } else {
        return -1;
      }
    } else if (nread == 0) {
      break;
    }
    nleft -= nread;
    buf += nread;
  }

  return n - nleft;
}

/**
 * Write n butes (unbuffered)
 */
ssize_t rio_writen(int fd, void *usrbuf, size_t n) {
  ssize_t nleft = n;
  ssize_t nread = 0;
  char *buf = (char *)usrbuf;

  while (nleft > 0) {
    if ((nread = write(fd, buf, nleft)) <= 0) {
      if (errno == EINTR) {
        nread = 0;
      } else {
        return -1;
      }
    }
    nleft -= nread;
    buf += nread;
  }

  return n;
}

/**
 * Init rp with fd;
 */
void rio_readinitb(rio_t *rp, int fd) {
  rp->rio_fd = fd;
  rp->rio_cnt = 0;
  rp->rio_bufptr = rp->rio_buf;
}

/**
 * Wrapper of read()
 * transfers min{n, rio_cnt} bytes into usrbuf (buffered)
 * if no buffered bytes in rp, buffer firstly, then do thansformation
 */
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n) {
  int cnt;

  while (rp->rio_cnt <= 0) {
    rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
    if (rp->rio_cnt < 0) {
      if (errno != EINTR) {
        return -1;
      }
    } else if (rp->rio_cnt == 0) {
      // EOF
      return 0;
    } else {
      rp->rio_bufptr = rp->rio_buf;
    }
  }

  cnt = n;
  if (rp->rio_cnt < cnt) {
    cnt = rp->rio_cnt;
  }
  memcpy(usrbuf, rp->rio_bufptr, cnt);
  rp->rio_bufptr += cnt;
  rp->rio_cnt -= cnt;
  return cnt;
}

/**
 * read a line (buffered)
 * set NULL-terminator
 * if EOF occur, just read existing data
 */
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) {
  int n;
  ssize_t rc;
  char c;
  char *bufptr = (char *)usrbuf;

  for (n = 1; n < maxlen; ++n) {
    if ((rc = rio_read(rp, &c, 1)) == 1) {
      *bufptr++ = c;
      if (c == '\n') {
        ++n;
        break;
      }
    } else if (rc == 0) {
      if (n == 0) {
        return 0;  // EOF, no data read
      } else {
        break;     // EOF, some data was read
      }
    } else {
      return -1;
    }
  }
  *bufptr = 0;
  return n - 1;
}

/**
 * read n bytes (buffered)
 */
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n) {
  char *bufptr = (char *)usrbuf;
  ssize_t nleft = n;
  ssize_t nread = 0;

  while (nleft > 0) {
    if ((nread = rio_read(rp, bufptr, nleft)) < 0) {
      return -1;  // error
    } else if (nread == 0) {
      break;      // EOF
    }
    bufptr += nread;
    nleft -= nread;
  }

  return n - nleft;
}
