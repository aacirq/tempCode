//
// Created by renxin on 2021/6/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void show_baud(speed_t val);

void show_some_flags(struct termios *info);

int main() {
    struct termios info;
    if (tcgetattr(0, &info) == -1) {
        perror("tcgetattr error");
        exit(1);
    }

    show_baud(cfgetospeed(&info));
    printf("The erase character is ascii %d, Ctrl-%c\n",
           info.c_cc[VERASE], info.c_cc[VERASE]-1+'A');
    printf("The line kill character is ascii %d, Ctrl-%c\n",
           info.c_cc[VKILL], info.c_cc[VKILL]-1+'A');
    show_some_flags(&info);
    return 0;
}

void show_baud(speed_t val) {
    switch (val) {
        case B300:
            printf("300\n");
            break;
        case B600:
            printf("600\n");
            break;
        case B1200:
            printf("1200\n");
            break;
        case B1800:
            printf("1800\n");
            break;
        case B2400:
            printf("2400\n");
            break;
        case B4800:
            printf("4800\n");
            break;
        case B9600:
            printf("9600\n");
            break;
        default:
            printf("Fast\n");
            break;
    }
}

struct flaginfo {
    int fl_value;
    char *fl_name;
};

struct flaginfo input_flags[] = {
        IGNBRK, "Ignore break condition",
        BRKINT, "Signal interrupt on break",
        IGNPAR, "Ignore chars with parity errors",
        PARMRK, "Mark parity errors",
        INPCK, "Enable input parity check",
        ISTRIP, "Strip character",
        INLCR, "Map NL to CR on input",
        IGNCR, "Ignore CR",
        ICRNL, "Map CR to NL on input",
        IXON, "Enable start/stop output control",
        IXOFF, "Enable start/stop input control",
        0, NULL
};

struct flaginfo local_flags[] = {
        ISIG, "Enable signals",
        ICANON, "Canonical input(erase and kill)",
        ECHO, "Enable echo",
        ECHOE, "Echo ERASE as BS-SPACE-BS",
        ECHOK, "Echo KILL by starting new line",
        0, NULL
};

void show_flagset(tcflag_t val, const struct flaginfo *pf) {
    for (; pf->fl_value != 0; pf++) {
        printf("%s is ", pf->fl_name);
        if (val & pf->fl_value) {
            printf("ON\n");
        } else {
            printf("OFF\n");
        }
    }
}

void show_some_flags(struct termios *info) {
    show_flagset(info->c_iflag, input_flags);
    show_flagset(info->c_lflag, local_flags);
}