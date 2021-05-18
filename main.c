#include "include/main.h"
#include "include/menu.h"

int main(int args, char *argv[]) {
    system("cls");
    main_menu();
    //FILE *f = fopen(argv[1], "rb"); readFile(f); read_user(); print_nachricht_len(0), print_nachricht_len(1);
    //FILE *f = fopen(argv[1], "rb"); readFile(f); read_user(); print_nachricht_len(1);
    //FILE *f = fopen(argv[1], "rb"); readFile(f); /*read_user();*/ count_weekday(); count_hours(); count_month(); print_weekday(); print_hour();
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

//kopiert von Internet
char *get_file_name() {
    HWND owner = NULL;
    char *filter = "All Files (*.*)\0*.*\0";
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "";
    char *fileNameStr = malloc(MAX_PATH * sizeof(char));

    if (GetOpenFileName(&ofn))
        strcpy(fileNameStr, fileName);
    return fileNameStr;

}
