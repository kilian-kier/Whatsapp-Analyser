#include "include/options.h"

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

void opt0() {
    int xsize = x_size / 2 < y_size ? x_size : y_size * 2;
    int ysize = x_size / 2 < y_size ? x_size / 2 : y_size;
    FILE *f = fopen("grafics\\icon.ppm", "r");
    if (f == NULL) {
        f = fopen("../grafics\\icon.ppm", "r");
        if (f != NULL) {
            fclose(f);
            draw_picture("../grafics\\icon.ppm", NULL, 0, 0, xsize, ysize);
        }
    } else {
        fclose(f);
        draw_picture("grafics\\icon.ppm", NULL, 0, 0, xsize, ysize);
    }
    free_memory();
}

void opt1() {
    file = fopen(get_file_name(), "rb");
    if (file != NULL)
        pthread_create((pthread_t *) global_threads[0][0], NULL, (void *) global_threads[0][1], NULL);
}

void opt3() {
    exit(0);
}

void opt4() {
    clear_screen();
    DWORD processID = GetCurrentProcessId();
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
    printf("\x1b[%dB", y_pos);
    foreground_color(global_settings.menu_color);
    printf("%s\n", "WhatsApp Analyzer\n");
    printf("Max RAM: %lf MB\n", (double) pmc.PeakWorkingSetSize / 1048576);
    printf("Current RAM: %lf MB\n", (double) pmc.WorkingSetSize / 1048576);
    while (global_input_buffer != '')
        Sleep(sync_delay);
    global_input_buffer = 0;
    file = NULL;
}

void opt1_4_1() {
    dictionary_select(file);
}
void opt1_4_2(){
    dictionary_main(0);
}

void opt1_4_2_1() {
    dictionary_main('A');
}

void opt1_4_2_2() {
    dictionary_main('l');
}

void opt1_4_2_3() {
    dictionary_main('a');
}

void opt1_4_2_4() {
    dictionary_main('r');
}

void opt1_1_1() {
    print_message_len(0);
}

void opt1_1_2() {
    print_message_len(1);
}

void opt1_3_3() {
    print_word_message(NULL);
}

void opt2_4() {
    default_settings();
    init_picture_buffer();
    print_settings_example();
    draw_picture_buffer();
    write_config();
}
