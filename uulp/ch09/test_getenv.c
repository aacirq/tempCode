#include <stdio.h>
#include <stdlib.h>

int main() {
    char *p = getenv("LANG");
    printf("%s\n", p);
    
    return 0;
}