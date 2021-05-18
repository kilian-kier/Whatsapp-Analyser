#include "include/main.h"

int main(int args, char *argv[]) {
    system("cls");
    main_menu();
    /*
    FILE *f = fopen(argv[1], "r");
    read_file((FILE *)f);
    read_user();
    print_message_len(0);
     */
}

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
