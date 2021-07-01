#include <stdio.h>
#include <termios.h>

# define QUESTION "Do you want another transaction"

int get_response(char *);
int tty_mode(int);
void set_cr_noecho_mode();

int main() {
    // save tty mode
    tty_mode(0);
    // set chr-by-chr mode
    set_cr_noecho_mode();

    int res = get_response(QUESTION);
    printf("\n");
    // restore tty mode
    tty_mode(1);
    return res;
}

// ask a question and wait for y/n answer
// return: 0->yes, 1->no
int get_response(char *question) {
    char c;
    printf("%s(y/n): ", question);
    while (1) {
        switch (c = getchar()) {
        case 'y':
        case 'Y':
            return 0;
        case 'n':
        case 'N':
        case EOF:
            return 1;
        }
    }
}

// how == 0 -> save current mode
// how == 1 -> restore mode
int tty_mode(int how) {
    static struct termios original_mode;
    if (how == 0) {
        return tcgetattr(0, &original_mode);
    } else {
        return tcsetattr(0, TCSANOW, &original_mode);
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