#include "include/options.h"

void opt0() {
    extern char *_binary_icon_ppm_start;
    extern char *_binary_icon_ppm_end;
    int xsize=x_size/2<y_size?x_size:y_size*2;
    int ysize=x_size/2<y_size?x_size/2:y_size;
    draw_picture((char *) &_binary_icon_ppm_start, (char *) &_binary_icon_ppm_end, 0, 0, x_size,y_size - 1);
    free_memory();
}

void opt1() {
    //file = fopen(get_file_name(), "rb");
    file = fopen("E:\\Desktop\\Schule\\Informatik\\Whatsapp-Analyser - Kopie\\chats\\WhatsApp Chat mit 3BT.txt", "rb");
    if (file != NULL)
        pthread_create((pthread_t *)global_threads[0][0], NULL, (void *)global_threads[0][1], NULL);
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
    foreground_color(global_settings.menucolor);
    printf("%s\n", "WhatsApp Analyzer\n");
    printf("Max RAM: %lf MB\n", (double)pmc.PeakWorkingSetSize / 1048576);
    printf("Current RAM: %lf MB\n", (double)pmc.WorkingSetSize / 1048576);
    while (global_input_buffer != '')
        Sleep(sync_delay);
    global_input_buffer = 0;
    file = NULL;
}

void opt1_1() {
    for (int i = 0; i < 2; i++) {
        pthread_join(*(pthread_t *)global_threads[i][0], NULL);
    }
}

void opt1_2() {
    for (int i = 2; i < 6; i++)
        pthread_join(*(pthread_t *)global_threads[i][0], NULL);
}

void opt1_4() {
    pthread_join(*(pthread_t *)global_threads[6][0], NULL);
    dictionary_main(0);
}

void opt1_4_1() {
    dictionary_select(file);
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

void opt1_1_3() {
    print_average_words();
}

void opt1_2_1() {
    print_month();
}

void opt1_2_2() {
    print_weekday();
}

void opt1_2_3() {
    print_day();
}

void opt1_2_4() {
    print_hour();
}

void opt1_3_1() {
    print_date_message();
}

void opt1_3_2() {
    print_user_message();
}

void opt2_1_1() {
    set_font_color();
    write_config();
}

void opt2_1_2() {
    set_bar_color();
    write_config();
}

void opt2_1_3() {
    set_menu_color();
    write_config();
}

void opt2_1_4() {
    set_background_color();
    write_config();
}

void opt2_2() {
    set_top_n();
    write_config();
}

void opt2_3() {
    set_empty_lines();
    write_config();
}

void opt2_4() {
    default_settings();
    init_picture_buffer();
    print_settings_example();
    draw_picture_buffer();
    write_config();
}
