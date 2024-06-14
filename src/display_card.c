#include "display_card.h"

void copy_cards_to_array(t_card *head, t_card **array)
{
    t_card *current = head;
    int index = 0;
    while (current != NULL) {
        array[index] = current;
        current = current->next;
        index++;
    }
}

void shuffle_array(t_card **array, int size)
{
	int i;
	i = size -1;
    while (i > 0) 
    {
        int j = rand() % (i + 1);
        t_card *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
	i--;
    }
}

void play_card(t_card *head) {
    int number_card_play;
    int i;
    int score;
    int range_max;
    char answer[MAX_CARD_LENGTH];
    char format[20];

    i = 0;
    snprintf(format, sizeof(format), "%%%ds", MAX_CARD_LENGTH - 1);
    score = 0;
    range_max = count_card(head);

    printf("Combien de sessions ? ");
    scanf("%d", &number_card_play);

    if (range_max <= 0) {
        printf("Pas de cartes disponibles.\n");
        return;
    }

    t_card **card_array = malloc(range_max * sizeof(t_card *));
    if (card_array == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        return;
    }

    copy_cards_to_array(head, card_array);

    srand(time(NULL));

    shuffle_array(card_array, range_max);
    while (i < number_card_play && i < range_max)
    {
	t_card *current = card_array[i];

        printf("Carte numéro %d devant : %s \n", i, current->front_card);
        printf("Derrière ? \n");
        scanf(format, answer);

        if (strcasecmp(answer, current->back_card) == 0)
        {
            printf("Exact\n \n");
	    score++;
        }
        else
        {
	    printf("Faux ! Réponse attendue : %s \n \n", current->back_card);

        }
        current = current->next; 
	i++;
    }
    printf("Votre score : %d / %d", score, number_card_play);
    free(card_array);
}

void show_card(t_card *head)
{
    int i = 1;
    t_card *current = head;
    while (current != NULL)
    {
        printf("Carte numéro %d, devant : %s \n", i, current->front_card);
        printf("Carte numéro %d, derrière : %s \n", i, current->back_card);
        current = current->next;
        i++;
    }
    printf("\n \n");
}

void free_card(t_card *head)
{
    t_card *current = head;
    t_card *next;
    while (current != NULL)
    {
        next = current->next;
        free(current->front_card);
        free(current->back_card);
        free(current);
        current = next;
    }
}

int count_card(t_card *head)
{
    int count = 0;
    t_card *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

t_card *read_cards_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    t_card *head = NULL;
    char line[MAX_CARD_LENGTH * 2];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *front_card = strtok(line, ",");
        char *back_card = strtok(NULL, "\n");

        if (front_card != NULL && back_card != NULL)
        {
            t_card *new_card = (t_card *)malloc(sizeof(t_card));
            if (new_card == NULL)
            {
                printf("Échec de l'allocation mémoire\n");
                fclose(file);
                free_card(head);
                return NULL;
            }

            new_card->front_card = strdup(front_card);
            new_card->back_card = strdup(back_card);
            new_card->next = NULL;

            if (head == NULL)
            {
                head = new_card;
            }
            else
            {
                t_card *current = head;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = new_card;
            }
        }
    }

    fclose(file);
    return head;
}


void delete_all_card()
{
    FILE *file = fopen("Deck.csv", "r");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fclose(file);
    file = fopen("Deck.csv", "w");
    if (file == NULL)
    {
        printf("Erreur lors de la réouverture du fichier pour la suppression.\n");
        return;
    }

    fclose(file);
    printf("Toutes les cartes ont été supprimées avec succès.\n");
}

void replace_cells(char *line, const char *new_value_A, const char *new_value_B) {
    char buffer[BUFFER_SIZE];
    char *token;
    int current_col = 0;

    buffer[0] = '\0';
    token = strtok(line, ",");

    while (token != NULL && current_col < MAX_COLUMNS) {
        if (current_col == 0) {
            strcat(buffer, new_value_A);
        } else if (current_col == 1) {
            strcat(buffer, new_value_B);
        } else {
            strcat(buffer, token);
        }
        token = strtok(NULL, ",");
        if (token != NULL) {
            strcat(buffer, ",");
        }
        current_col++;
    }

    strcpy(line, buffer);
}

void modify_deck(int row_number, const char *new_value_A, const char *new_value_B) {
    FILE *file = fopen("Deck.csv", "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char lines[BUFFER_SIZE][BUFFER_SIZE];
    int line_count = 0;

    // Read the file line by line
    while (fgets(lines[line_count], BUFFER_SIZE, file)) {
        lines[line_count][strcspn(lines[line_count], "\n")] = 0;  // Remove newline character
        line_count++;
    }
    fclose(file);

    // Modify the specified row
    if (row_number > 0 && row_number <= line_count) {
        replace_cells(lines[row_number - 1], new_value_A, new_value_B); // Modify the specified row
    } else {
        printf("Invalid row number.\n");
        return;
    }

    file = fopen("Deck.csv", "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);
}

void delete_card(int row_number) {
    FILE *file = fopen("Deck.csv", "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char lines[BUFFER_SIZE][BUFFER_SIZE];
    int line_count = 0;

    while (fgets(lines[line_count], BUFFER_SIZE, file)) {
        lines[line_count][strcspn(lines[line_count], "\n")] = 0;
        line_count++;
    }
    fclose(file);

    if (row_number <= 0 || row_number > line_count) {
        printf("Numéro de ligne invalide.\n");
        return;
    }

    file = fopen("Deck.csv", "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < line_count; i++) {
        if (i != row_number - 1) {
            fprintf(file, "%s\n", lines[i]);
        }
    }

    fclose(file);
}


