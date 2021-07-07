#include <stdlib.h>
#include <stdio.h>

int main() {
    FILE *fp = popen("ls|sort", "r");

    char buf[BUFSIZ];
    int i = 0;
    while (fgets(buf, BUFSIZ, fp) != NULL) {
        printf("%3d  %s", i++, buf);
    }

    pclose(fp);
    return 0;
}