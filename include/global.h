#ifndef INFORMATIK_PROJEKT_GLOBAL_H
#define INFORMATIK_PROJEKT_GLOBAL_H

#include "structs.h"
#include "menu.h"
#include <pthread.h>

int anz_nachrichten;
struct Nachricht *first_nachricht;
struct User *first_user;
struct Woerterbook *first_word;
pthread_t read_file_tread;
pthread_t read_user_tread;

#endif //INFORMATIK_PROJEKT_GLOBAL_H
