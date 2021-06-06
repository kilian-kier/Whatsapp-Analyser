#include "include/main.h"

int main() {
    for (int i = 0; i < 7; i++)
        global_threads[i][0] = malloc(sizeof(pthread_t));
    global_threads[0][1] = read_file;
    global_threads[1][1] = read_user;
    global_threads[2][1] = count_weekday;
    global_threads[3][1] = count_hours;
    global_threads[4][1] = count_month;
    global_threads[5][1] = count_days;
    global_threads[6][1] = create_dictionary;
    read_config();
    global_arrow_keys = 0;
    system("cls");
    main_menu();
}
