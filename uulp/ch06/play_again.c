#include <stdio.h>
#include <termios.h>

# define QUESTION "Do you want another transaction"

int get_response(char *);
int tty_mode(int);
void set_crmode();

int main() {
    tty_mode(0);  // save tty mode
    set_crmode(); // set chr-by-chr mode
    int res = get_response(QUESTION);
    tty_mode(1);  // restore tty mode
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
        default:
            printf("\ncannot understand %c, Please type <y> or <n>\n", c);
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
void set_crmode() {
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}