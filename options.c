#include "include/options.h"

void opt0(FILE *f) {
    extern char *_binary_icon_ppm_start;
    extern char *_binary_icon_ppm_end;
    draw_picture((char *) &_binary_icon_ppm_start, (char *) &_binary_icon_ppm_end, 15, 0, x_size - 70, y_size - 1);
    free_memory();
}

void opt1(FILE *f) {
    f = fopen(get_file_name(), "rb");
    pthread_create(&read_file_tread, NULL, read_file, (void *) f);
}

void opt2(FILE *f) {
    print_settings_example();
    draw_picture_buffer();
}

void opt3(__attribute__((unused)) FILE *f) {
    exit(0);
}

void opt1_1(FILE *f) {
    int x = pthread_join(read_file_tread, NULL);
    int y = pthread_join(read_user_tread, NULL);
    if (x != 0 && x != 3)
        read_file(f);
    if (y != 0 && y != 3)
        read_user();
}

void opt1_2(__attribute__((unused)) FILE *f) {
    int x = pthread_join(weekday_thread, NULL);
    int y = pthread_join(hour_thread, NULL);
    int z = pthread_join(day_thread, NULL);
    if (x != 0 && x != 3)
        count_weekday();
    if (y != 0 && y != 3)
        count_hours();
    if (z != 0 && z != 3)
        count_days();
}

void opt1_4(FILE *f) {
    dictionary_main(f, 'A');
}

void opt1_4_1(FILE *f) {
    dictionary_select(f);
}

void opt1_4_2_1(FILE *f) {
    dictionary_main(f, 'A');
}

void opt1_4_2_2(FILE *f) {
    dictionary_main(f, 'l');
}

void opt1_4_2_3(FILE *f) {
    dictionary_main(f, 'a');
}

void opt1_4_2_4(FILE *f) {
    dictionary_main(f, 'r');
}

void opt1_1_1(__attribute__((unused)) FILE *f) {
    print_message_len(0);
}

void opt1_1_2(__attribute__((unused)) FILE *f) {
    print_message_len(1);
}

void opt1_1_3(__attribute__((unused)) FILE *f) {
    print_average_words();
}

void opt1_2_1(__attribute__((unused)) FILE *f) {
    print_month();
}

void opt1_2_2(__attribute__((unused)) FILE *f) {
    print_weekday();
}

void opt1_2_3(__attribute__((unused)) FILE *f) {
    print_day();
}

void opt1_2_4(__attribute__((unused)) FILE *f) {
    print_hour();
}

void opt1_3_1(__attribute__((unused)) FILE *f) {
    print_date_message();
}

void opt1_3_2(__attribute__((unused)) FILE *f) {
    print_user_message();
}

void opt2_1_1(FILE *f) {
    set_font_color();
    write_config();
}

void opt2_1_2(FILE *f) {
    set_bar_color();
    write_config();
}

void opt2_1_3(FILE *f) {
    set_menu_color();
    write_config();
}

void opt2_1_4(FILE *f) {
    set_background_color();
    write_config();
}

void opt2_2(FILE *f) {
    set_top_n();
    write_config();
}

void opt2_3(FILE *f) {
    set_empty_lines();
    write_config();
}

void opt2_4(FILE *f) {
    default_settings();
    init_picture_buffer();
    print_settings_example();
    draw_picture_buffer();
    write_config();
}
