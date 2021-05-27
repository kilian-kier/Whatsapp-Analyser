#include "include/options.h"

void opt1(FILE *f) {
    f = fopen(get_file_name(), "rb");
    pthread_create(&read_file_tread, NULL, read_file, (void *) f);
}

void opt2(__attribute__((unused)) FILE *f) {
    exit(1);
}

void opt1_1(FILE *f) {
    static bool is_read = false;
    if (is_read == false) {
        if (pthread_join(read_file_tread, NULL) != 0)
            read_file(f);
        if (pthread_join(read_user_tread, NULL) != 0)
            read_user();
        is_read = true;
    }
}

void opt1_2(__attribute__((unused)) FILE *f) {
    static bool is_read = false;
    if (is_read == false) {
        if (pthread_join(weekday_thread, NULL) != 0)
            count_weekday();
        if (pthread_join(hour_thread, NULL) != 0)
            count_hours();
        is_read = true;
    }
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
    print_hour();
}

void opt1_3_1(__attribute__((unused)) FILE *f) {
    print_date_message();
}

void opt1_3_2(__attribute__((unused)) FILE *f) {
    print_user_message();
}
