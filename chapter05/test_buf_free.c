#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main() {
  FILE *fp;

  fp = fopen("tmp.txt", "r+");

  char *buf = malloc(sizeof(char) * 1024);
  setvbuf(fp, buf, _IOLBF, 1024);

  char data[1024];
  fgets(data, 1024, fp);
  fputs(data, stdout);
  fflush(stdin);

  fclose(fp);

  printf("%s", buf);
  for (int i = 0; i < 1024; ++i) {
    buf[i] = ' ';
  }
  
  free(buf);

  // 测试可知，如果利用setvbuf将fp的缓冲区自定义，那么fclose的时候不会自动free

  return 0;
}