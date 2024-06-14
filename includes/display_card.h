#ifndef DISPLAY_CARD_H
#define DISPLAY_CARD_H

#include "ft_h.h"


void play_card(t_card *head);
void show_card(t_card *head);
void free_card(t_card *head);
int count_card(t_card *head);
void delete_all_card();
void replace_cells(char *line, const char *new_value_A, const char *new_value_B);
void modify_deck(int row_number, const char *new_value_A, const char *new_value_B);
void delete_card(int row_number);
t_card *read_cards_from_file(const char *filename);

#endif
