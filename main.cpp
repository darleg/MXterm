#include "mbed.h"

#define TX PA_11
#define RX PA_12

static BufferedSerial az(TX, RX);

FileHandle *mbed::mbed_override_console(int fd)
{
    return &az;
}

#define clrscn printf("\033[2J")
#define poscur(row,col) printf("\033[%d;%dH",row,col)
#define deftxt printf("\033[0m")
enum attr {rst, bld, dim};
enum fg {fgblk=30, fgred=31, fggrn=32, fgyel=33, fgblu=34};
enum bg {bgblk=40, bgred=41, bggrn=42, bgyel=43, bgblu=44};

char c;

int main() {
    printf("Hit any key");
    az.read(&c, 1);
    clrscn;
    poscur(5,30);
    printf("\033[%d;%d;%dmHi there", bld, fgred, bggrn);
    deftxt;
    poscur(6,32);
    printf("\033[%d;%d;%dmHi there", dim, fgred, bgyel);
    deftxt;
    poscur(7, 34);
    printf("\033[%d;%d;%dmHi there", bld, fggrn, bgblu);
    deftxt;
    poscur(8, 36);
    printf("\033[%d;%d;%dmHi there", dim, fggrn, bgred);
    printf("\n");
    poscur(10,15);
    printf("\033[%d;%d;%dmType anything. ", bld, fgblk, bggrn);

    while(1) {
        
        az.read(&c, 1); // echo input back to terminal
        az.write(&c, 1);
    }
}

