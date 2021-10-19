#include <strings.h>

#include "../csapp.h"

void doit(int fd);
void clienterror(int fd, const char *cause, const char *errnum,
                 const char *shortmsg, const char *longmsg);
void read_requesthdrs(rio_t *rp);
int parse_uri(const char *uri, char *filename, char *cgiargs);

void serve_static(int fd, const char *filename, int filesize);
void serve_dynamic(int fd, const char *filename, const char *cgiargs);
void get_filetype(const char *filename, char *filetype);

int main(int argc, char **argv) {
  int listenfd, connfd;
  struct sockaddr_storage addr;
  socklen_t addrlen;
  char host[MAXLINE];
  char port[MAXLINE];

  if (argc != 2) {
    fprintf(stderr, "usage: ./echo_server <port>\n");
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]);

  while (1) {
    addrlen = sizeof(struct sockaddr_storage);
    if ((connfd = accept(listenfd, (struct sockaddr *)&addr, &addrlen)) == -1) {
      fprintf(stderr, "error: accept %s\n", strerror(errno));
      exit(1);
    }
    getnameinfo((struct sockaddr *)(&addr), addrlen, host, MAXLINE, port,
                MAXLINE, 0);
    fprintf(stdout, "Get connection from <%s, %s>\n", host, port);

    doit(connfd);

    fprintf(stdout, "close connection\n");
    close(connfd);
  }

  return 0;
}

void doit(int fd) {
  rio_t rio;
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  int is_static;
  char filename[MAXLINE], cgiargs[MAXLINE];
  struct stat statbuf;

  Rio_readinitb(&rio, fd);
  Rio_readlineb(&rio, buf, MAXLINE);
  fprintf(stdout, "Request headers:\n%s", buf);
  sscanf(buf, "%s %s %s", method, uri, version);
  if (strcasecmp(method, "GET") != 0) {
    // put 501 Not implemented
    clienterror(fd, method, "501", "Not implemented",
                "Tiny does not implement this method");
    return;
  }

  read_requesthdrs(&rio);

  is_static = parse_uri(uri, filename, cgiargs);
  if (stat(filename, &statbuf) == -1) {
    clienterror(fd, method, "404", "Not found",
                "Tiny could not find this file");
    return;
  }

  // printf("=======> is_static: %d\n\n", is_static);

  if (is_static == 1) {
    if (!S_ISREG(statbuf.st_mode) || !(S_IRUSR & statbuf.st_mode)) {
      clienterror(fd, method, "403", "Forbidden",
                  "Tiny could not read the file");
      return;
    }
    // do static jobs
    serve_static(fd, filename, statbuf.st_size);
  } else {
    if (!S_ISREG(statbuf.st_mode) || !(S_IXUSR & statbuf.st_mode)) {
      clienterror(fd, method, "403", "Forbidden",
                  "Tiny could not run the CGI program");
      return;
    }
    // do dynamical jobs
    serve_dynamic(fd, filename, cgiargs);
  }
}

void clienterror(int fd, const char *cause, const char *errnum,
                 const char *shortmsg, const char *longmsg) {
  char buf[MAXLINE], body[MAXLINE];
  sprintf(body, "<html><title>Tiny Error</title>");
  sprintf(body, "%s<body bgcolor=ffffff>\r\n", body);
  sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
  sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
  sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

  sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-type: text/html\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
  Rio_writen(fd, buf, strlen(buf));
  Rio_writen(fd, body, strlen(body));
}

void read_requesthdrs(rio_t *rp) {
  char buf[MAXLINE];

  do {
    Rio_readlineb(rp, buf, MAXLINE);
    fprintf(stdout, "%s", buf);
  } while (strcmp(buf, "\r\n") != 0);
}

/**
 * @return 1 - static; 0 - dynamic
 */
int parse_uri(const char *uri, char *filename, char *cgiargs) {
  char *p;

  if (strstr(uri, "cgi-bin") == NULL) {
    // static
    strcpy(cgiargs, "");
    strcpy(filename, ".");
    strcat(filename, uri);
    if (uri[strlen(uri) - 1] == '/') {
      strcat(filename, "home.html");
    }
    return 1;
  } else {
    // dynamic
    if ((p = strchr(uri, '?')) != NULL) {
      strcpy(cgiargs, p + 1);
      *p = '\0';
    } else {
      strcpy(cgiargs, "");
    }
    strcpy(filename, ".");
    strcat(filename, uri);
    return 0;
  }
}

void serve_static(int fd, const char *filename, int filesize) {
  char filetype[MAXLINE];
  char buf[MAXLINE];
  int srcfd;
  char *srcp;

  get_filetype(filename, filetype);
  sprintf(buf, "HTTP/1.0 200 OK\r\n");
  sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
  sprintf(buf, "%sConnection: close\r\n", buf);
  sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
  sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
  Rio_writen(fd, buf, strlen(buf));
  fprintf(stdout, "Response headers:\n%s", buf);

  srcfd = open(filename, O_RDONLY);
  srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
  close(srcfd);
  Rio_writen(fd, srcp, filesize);
  munmap(srcp, filesize);
}

void get_filetype(const char *filename, char *filetype) {
  if (strstr(filename, ".html"))
    strcpy(filetype, "text/html");
  else if (strstr(filename, ".gif"))
    strcpy(filetype, "image/gif");
  else if (strstr(filename, ".png"))
    strcpy(filetype, "image/png");
  else if (strstr(filename, ".jpg"))
    strcpy(filetype, "image/jpeg");
  else
    strcpy(filetype, "text/plain");
}

void serve_dynamic(int fd, const char *filename, const char *cgiargs) {
  char buf[MAXLINE];
  char *emptylist[] = {NULL};

  sprintf(buf, "HTTP/1.0 200 OK\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Server: Tiny Web Server\r\n");
  Rio_writen(fd, buf, strlen(buf));

  if (fork() == 0) {
    setenv("QUERY_STRING", cgiargs, 1);
    dup2(fd, STDOUT_FILENO);
    execve(filename, emptylist, environ);
  }
  wait(0);
}
