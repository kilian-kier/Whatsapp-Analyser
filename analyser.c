#include "include/analyser.h"

void *count_weekday() {
    Message *ptr = global_first_message;
    global_week_arr = (int *) malloc(7 * sizeof(int));
    for (int x = 0; x < 7; x++) {
        *(global_week_arr + x) = 0;
    }
    unsigned short weekday, h, k;
    while (ptr->next != NULL) {
        if ((int) ptr->month <= 2) {
            h = (int) ptr->month + 12;
            k = (int) ptr->year - 1;
        } else {
            h = (int) ptr->month;
            k = (int) ptr->year;
        }
        weekday = (int) ((int) ptr->day + 2 * h + (3 * h + 3) / 5 + k + k / 4 - k / 100 + k / 400 + 1) % 7;
        *(global_week_arr + weekday) += 1;
        ptr = ptr->next;
    }
}

unsigned int count_words(const char *string) {
    unsigned int words = 0;
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] == ' ' || string[i] == '\n')
            words++;
        i++;
    }
    return words;
}

void count_message() {
    global_message_n = 0;
    Message *ptr = global_first_message;
    while (ptr != NULL) {
        global_message_n++;
        ptr = ptr->next;
    }
}

void *count_hours() {
    Message *ptr = global_first_message;
    global_hour_arr = (int *) malloc(24 * sizeof(int));
    for (int x = 0; x < 24; x++) {
        *(global_hour_arr + x) = 0;
    }
    while (ptr->next != NULL) {
        *(global_hour_arr + (int) ptr->hour) += 1;
        ptr = ptr->next;
    }
}

void *count_month() {
    Message *ptr = global_first_message;
    global_month_arr = (int *) calloc(12, sizeof(int));
    while (ptr->next != NULL) {
        global_month_arr[(int) ptr->month - 1]++;
        ptr = ptr->next;
    }
}

void *count_days() {
    pthread_join(*(pthread_t *) global_threads[5][0], NULL);
    Message *ptr = global_first_message;
    global_day_arr = (Day_count *) calloc(global_settings.top_n, sizeof(Day_count));
    Day_count *tmp = (Day_count *) calloc(global_settings.top_n, sizeof(Day_count));
    unsigned int n = 0, day = 0, month = 0, year = 0;
    while (ptr->next != NULL) {
        if (ptr->day != day || ptr->month != month || ptr->year != year) {
            day = ptr->day;
            month = ptr->month;
            year = ptr->year;
            for (int i = 0; i < global_settings.top_n; i++) {
                if (n > global_day_arr[i].n) {
                    // TODO: Insertion ohne an 2. Array
                    for (int j = i + 1; j < global_settings.top_n; j++) {
                        tmp[j] = global_day_arr[j - 1];
                    }
                    global_day_arr[i] = *create_day_count(day, month, year, n);
                    for (int j = i + 1; j < global_settings.top_n; j++) {
                        global_day_arr[j] = tmp[j];
                    }
                    break;
                }
            }
            n = 0;
        } else
            n++;
        ptr = ptr->next;
    }
    free(tmp);
}

bool true_day(unsigned int day, unsigned int month) {
    int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day >= 1 && day <= month_days[month - 1])
        return true;
    return false;
}

bool true_month(unsigned int month) {
    if (month >= 1 && month <= 12)
        return true;
    return false;
}

bool true_date(unsigned int day, unsigned int month, unsigned int year, Message *max_date) {
    if (year < (int) global_first_message->year || year > (int) max_date->year)
        return false;
    else if (year == (int) global_first_message->year) {
        if (month < (int) global_first_message->month)
            return false;
        else if (month == (int) global_first_message->month) {
            if (day < (int) global_first_message->day)
                return false;
        }
    } else if (year == (int) max_date->year) {
        if (month > (int) max_date->month)
            return false;
        else if (month == (int) max_date->month) {
            if (day > (int) max_date->day)
                return false;
        }
    }
    return true;
}

User *user_exists(char *username) {
    User *temp = global_first_user;
    while (temp->next != NULL) {
        if (strcmp(temp->name, strtok(username, "\n\0")) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

int check_date(unsigned int day1, unsigned int month1, unsigned int year1, unsigned int day2, unsigned int month2,
               unsigned int year2) {
    if (year1 == year2) {
        if (month1 == month2) {
            if (day1 == day2)
                return 0;
            else if (day1 < day2)
                return -1;
            else
                return 1;
        } else if (month1 < month2)
            return -1;
        else
            return 1;
    } else if (year1 < year2)
        return -1;
    else
        return 1;
}

bool true_highlight(const char *string, int offset) {
    for (int i = 0; i < offset; i++) {
        if (string[i] == '\n' || string[i] == '\r' || string[i] == '\0')
            return false;
    }
    return true;
}