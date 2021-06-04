#include "include/read.h"

void *read_file() {
    char buffer[buffersize];
    char two_char_buffer[3];
    char *strtol_buffer;
    Message *ptr = (Message *) malloc(sizeof(Message));
    global_first_message = ptr;
    int size;
    while (get_message(buffer) != NULL) {
        strncpy(two_char_buffer, buffer, 2);
        ptr->day = (short) strtol(two_char_buffer, &strtol_buffer, 10);
        strncpy(two_char_buffer, buffer + 3, 2);
        ptr->month = (short) strtol(two_char_buffer, &strtol_buffer, 10);
        strncpy(two_char_buffer, buffer + 6, 2);
        ptr->year = (short) strtol(two_char_buffer, &strtol_buffer, 10);
        strncpy(two_char_buffer, buffer + 10, 2);
        ptr->hour = (short) strtol(two_char_buffer, &strtol_buffer, 10);
        strncpy(two_char_buffer, buffer + 13, 2);
        ptr->minute = (short) strtol(two_char_buffer, &strtol_buffer, 10);
        if (strchr(buffer + 13, ':') != NULL) {
            size = length(buffer, ':', 18);
            ptr->user = (char *) malloc((size * sizeof(char)));
            strncpy(ptr->user, buffer + 18, size);
            ptr->user[size] = '\0';
            ptr->message = string_convert(buffer, 20 + (int) strlen(ptr->user));
        } else {
            ptr->user = NULL;
            ptr->message = string_convert(buffer, 20);
        }
        Message *next = (Message *) malloc(sizeof(Message));
        ptr->next = next;
        ptr = ptr->next;
    }
    ptr->next = NULL;
    count_message();
    for (int i = 1; i < 7; i++) {
        pthread_create((pthread_t *)global_threads[i][0], NULL, (void *)global_threads[i][1], NULL);
    }
}

char *get_message(char *buffer) {
    buffer[0] = 0;
    char *ret = NULL;
    char temp[buffersize];
    int position;
    do {
        ret = fgets(buffer + strlen(buffer), buffersize, file);
        position = ftello(file);
        fgets(temp, buffersize, file);
        fseeko(file, position, SEEK_SET);
    } while (ret != NULL && !check_new_string(temp));
    return ret;
}

bool check_new_string(const char *string) {
    bool valid = true;
    if (strlen(string) < 9)
        return false;
    if (string[2] != '.' || string[5] != '.' || string[8] != ',') {
        valid = false;
    }
    return valid;
}

int length(const char *buffer, char search, int start) {
    int x = 0;
    while (x < buffersize) {
        if (buffer[x + start] == search) break;
        x++;
    }
    return x;
}


char *string_convert(char *string, int offset) {
    int len = (int) strlen(string), y = 0;
    char string2[len];
    for (int i = offset; i < len; i++) {
        if (string[i] >= 'A' && string[i] <= 'Z') string2[y] = string[i] + 32;
        else if (string[i] == -61 && (string[i + 1] == -92 || string[i + 1] == -100)) {
            string2[y] = '\x84';
            i++;
        } else if (string[i] == -61 && (string[i + 1] == -74 || string[i + 1] == -106)) {
            string2[y] = '\x94';
            i++;
        } else if (string[i] == -61 && (string[i + 1] == -68) || string[i + 1] == -124) {
            string2[y] = '\x81';
            i++;
        } else if (string[i] == -61 && string[i + 1] == -97) {
            string2[y] = '\xe1';
            i++;
        } else if (string[i] < 0) {
            string2[y] = '\1';
            i += 3;
        } else if (string[i] == 13) continue;
        else string2[y] = string[i];
        y++;
    }
    string2[y] = '\0';
    char *ptr = (char *) malloc((y + 1) * sizeof(char));
    strcpy(ptr, string2);
    return ptr;
}
