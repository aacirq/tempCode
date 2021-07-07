#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void be_dc(int in[2], int out[2]);
void be_bc(int fromdc[2], int todc[2]);

int main() {
    int fromdc[2], todc[2];

    if (pipe(fromdc) == -1 || pipe(todc) == -1) {
        perror("pipe failed");
        exit(1);
    }

    int pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        // child
        be_dc(todc, fromdc);
    } else {
        // parent
        be_bc(fromdc, todc);
        wait(NULL);
    }

    return 0;
}

void be_dc(int in[2], int out[2]) {
    if (dup2(in[0], 0) == -1) {
        perror("dup2");
        exit(1);
    }
    close(in[0]);
    close(in[1]);

    if (dup2(out[1], 1) == -1) {
        perror("dup2");
        exit(1);
    }
    close(out[0]);
    close(out[1]);

    execlp("dc", "dc", "-", NULL);
    perror("execlp failed");
    exit(1);
}

void be_bc(int fromdc[2], int todc[2]) {
    close(fromdc[1]);
    close(todc[0]);

    FILE *fpin = fdopen(fromdc[0], "r");
    FILE *fpout = fdopen(todc[1], "w");
    if (fpin == NULL || fpout == NULL) {
        fprintf(stderr, "Error: %s\n", "error convering pipes to streams");
        exit(1);
    }

    char buf[BUFSIZ];
    int num1, num2;
    char ope;
    while (1) {
        printf("tinybc: ");
        if (fgets(buf, BUFSIZ, stdin) == NULL) {
            printf("\n");
            break;
        }
        if (sscanf(buf, "%d%c%d", &num1, &ope, &num2) != 3) {
            fprintf(stderr, "Error: %s\n", "syntax error");
            continue;
        }
        if (fprintf(fpout, "%d\n%d\n%c\np\n", num1, num2, ope) == EOF) {
            fprintf(stderr, "Error: %s\n", "error writing");
            exit(1);
        }
        fflush(fpout);

        int tlen = 0;
        do {
            if (fgets(buf, BUFSIZ, fpin) == NULL) {
                break;
            }
            tlen = strlen(buf);
            printf("%s", buf);
        } while (tlen > 2 && buf[tlen - 2] == '\\');
    }
    fclose(fpin);
    fclose(fpout);
}