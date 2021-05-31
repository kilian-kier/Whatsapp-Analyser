#include "include/main.h"

int main(int args, char *argv[]) {
    system("cls");
    main_menu();
    /*
    x_size = 169;
    y_size = 65;
    //opt0(NULL);
    FILE *f = fopen("E:\\Desktop\\Schule\\Informatik\\Whatsapp-Analyser\\chats\\WhatsApp Chat mit 3BT.txt", "r");
    read_file((FILE *)f);
    read_user();
    count_days();
    print_day();
    opt0(NULL);
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
