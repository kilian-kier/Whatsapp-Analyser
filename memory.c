#include "include/memory.h"

void free_messages(Message *ptr) {
    if (ptr == NULL)
        return;
    free_messages(ptr->next);
    if (ptr->next != NULL)
        free(ptr->message);
    ptr->next = NULL;
    free(ptr);
}
void free_users(User *ptr) {
    if (ptr == NULL)
        return;
    free_users(ptr->next);
    free(ptr);
}

void free_dictionary(Dictionary *ptr) {
    if (ptr == NULL)
        return;
    free_dictionary(ptr->left);
    free_dictionary(ptr->right);
    free(ptr);
}

void free_memory() {
    if (global_first_message != NULL) {
        clear_screen();
        for (int i = 0; i < 7; i++) {
            pthread_cancel(*((pthread_t *)global_threads[i][0]));
            pthread_join(*((pthread_t *)global_threads[i][0]), NULL);
        }
        free_messages(global_first_message);
        free_users(global_first_user);
        free_dictionary(global_first_word);
        free(global_hour_arr);
        free(global_day_arr);
        free(global_month_arr);
        free(global_week_arr);
        global_first_message = NULL;
    }
}

void free_tree(Tree *node) {
    if (node == NULL)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void run_memory_thread() {
    pthread_t pth;
    pthread_create(&pth, NULL, memory_thread, NULL);
}

void *memory_thread() {
    Sleep(500);
    while (1) {
        DWORD processID = GetCurrentProcessId();
        HANDLE hProcess;
        PROCESS_MEMORY_COUNTERS pmc;
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
        GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        GetConsoleScreenBufferInfo(hStdout, &bufferInfo);
        SetConsoleCursorPosition(hStdout, (COORD){0, 20});
        foreground_color(global_settings.menucolor);
        printf("RAM Nutzung:\n%.2lf MB\n", (double)pmc.WorkingSetSize / 1048576);
        SetConsoleCursorPosition(hStdout, bufferInfo.dwCursorPosition);
        Sleep(500);
    }
}