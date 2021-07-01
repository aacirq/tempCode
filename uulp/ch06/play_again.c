#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define SLEEP_SECOND 2
#define TRIES 3
#define QUESTION "Do you want another transaction"

int get_response(char *question, int maxtries);
void tty_mode(int);
void set_cr_noecho_mode();
void set_nodelay_mode();
void ctrl_c_handler(int signum);

int main() {
    // save tty mode
    tty_mode(0);
    // set chr-by-chr mode
    set_cr_noecho_mode();
    // set no-delay mode
    set_nodelay_mode();

    signal(SIGINT, ctrl_c_handler);
    signal(SIGQUIT, SIG_IGN);

    int res = get_response(QUESTION, TRIES);
    // restore tty mode
    tty_mode(1);

    printf("\n");
    return res;
}

static int get_ok_char() {
    int c;
    while ((c = getchar()) == EOF && strchr("yYnN", c) != NULL)
        ;
    return c;
}

// ask a question and wait for y/n answer
// return: 0->yes, 1->no, 2->timeout
int get_response(char *question, int maxtries) {
    char c;
    printf("%s(y/n): ", question);
    fflush(stdout);

    while (1) {
        sleep(SLEEP_SECOND);
        c = tolower(get_ok_char());
        if (c == 'y') {
            return 0;
        } else if (c == 'n') {
            return 1;
        }
        maxtries--;
        if (maxtries == 0) {
            return 2;
        }
        // printf("Beep\n");
    }
}

// how == 0 -> save current mode
// how == 1 -> restore mode
void tty_mode(int how) {
    static struct termios original_mode;
    static int original_flags;
    static int stored = 0;

    if (how == 0) {
        tcgetattr(0, &original_mode);
        original_flags = fcntl(0, F_GETFL);
        stored = 1;
    } else if (stored) {
        tcsetattr(0, TCSANOW, &original_mode);
        fcntl(0, F_SETFL, original_flags);
    }
}

// put file descriptor 0(stdin) into chr-by-chr mode
void set_cr_noecho_mode() {
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

// set file descriptor 0(stdin) into nodelay mode
void set_nodelay_mode() {
    int termflags;
    termflags = fcntl(0, F_GETFL);
    termflags |= O_NDELAY;
    fcntl(0, F_SETFL, termflags);
}

// Handler of Ctrl-C. restore tty mode and exit;
void ctrl_c_handler(int signum) {
    tty_mode(1);
    printf("\n");
    exit(1);
}