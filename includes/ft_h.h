#ifndef FT_H_H
#define FT_H_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CARD_LENGTH 256
#define BUFFER_SIZE 1024
#define MAX_COLUMNS 2

typedef struct s_card {
    char *front_card;
    char *back_card;
    struct s_card *next;
} t_card;


#endif

