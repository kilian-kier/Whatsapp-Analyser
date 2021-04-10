#include "main.h"

int main(int argc, char *argv[]) {
    /*argc - wie viele Paramter (.exe inclusiv)
      argv - Array mit den Paramter (.exe inclusiv)*/
    FILE *f = fopen(argv[1], "r");
    readFile(f);
    return 0;
}

void print_nachricht(Nachricht *nachricht) {
    printf("%02u.", nachricht->tag);
    printf("%02u.", nachricht->monat);
    printf("%02u\n", nachricht->jahr);
    printf("%02u:", nachricht->stunde);
    printf("%02u\n", nachricht->minute);
    printf("%s schrieb:\n", nachricht->user);
    printf("%s\n", nachricht->nachricht);
}
