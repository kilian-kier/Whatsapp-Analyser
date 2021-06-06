#include "include/main.h"

int main(int args, char *argv[]) {
    system("cls");
    main_menu();
}

char *get_file_name() {
    HWND owner = NULL;
    char *filter = "WhatsApp Chats(*.txt)\0WhatsApp Chat*.txt\0All Files (*.*)\0*.*\0";
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
