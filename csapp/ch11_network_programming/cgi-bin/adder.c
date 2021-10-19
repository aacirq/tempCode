#include "../../csapp.h"

int main() {
  char *buf, *p;
  char arg1[MAXLINE];
  char arg2[MAXLINE];
  char content[MAXLINE];
  char copy[MAXLINE];
  int n1, n2;

  if ((buf = getenv("QUERY_STRING")) != NULL) {
    strcpy(copy, buf);
    p = strchr(copy, '&');
    *p = '\0';
    strcpy(arg1, copy);
    strcpy(arg2, p + 1);
    n1 = atoi(arg1);
    n2 = atoi(arg2);
  }

  sprintf(content, "QUERY_STRING=%s", buf);
  sprintf(content, "Welcome to add.com: ");
  sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
  sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", content, n1, n2, n1 + n2);
  sprintf(content, "%sThanks for visiting!\r\n", content);

  printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  printf("%s", content);
  fflush(stdout);

  return 0;
}