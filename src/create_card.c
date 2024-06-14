#include "create_card.h"

int verification_card(char *card)
{
    int i = 0;

    while (card[i])
    {
        if ((unsigned char)card[i] < 32 || (unsigned char)card[i] > 127)
        {
            return 0;
        }

        if (i == MAX_CARD_LENGTH - 2)
        {
            printf("Erreur : Trop de caractère \n");
            return 0;
        }
        i++;
    }
    return 1;
}

void create_card(t_card **head)
{
    int verif;
    char reponse_new_card;
    char format[20];
    char verif_card[MAX_CARD_LENGTH];
    t_card *current = *head;

    if (current != NULL)
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
    }

    snprintf(format, sizeof(format), "%%%ds", MAX_CARD_LENGTH - 1);

    while (1)
    {
        t_card *new_card = (t_card *)malloc(sizeof(t_card));
        if (new_card == NULL)
        {
            printf("Échec de l'allocation mémoire\n");
            return;
        }

        new_card->front_card = (char *)malloc(MAX_CARD_LENGTH * sizeof(char));
        new_card->back_card = (char *)malloc(MAX_CARD_LENGTH * sizeof(char));
        new_card->next = NULL;

        if (new_card->front_card == NULL || new_card->back_card == NULL)
        {
            printf("Échec de l'allocation mémoire\n");
            free(new_card);
            return;
        }

        printf("Bienvenue dans la création de flashcard \n");

        verif = 0;
        while (verif == 0)
        {
            printf("Saisir le devant de la carte \n");
            scanf(format, verif_card);
            while ((getchar()) != '\n');
            if (verification_card(verif_card))
                verif = 1;
            else
                verif = 0;
        }
        strncpy(new_card->front_card, verif_card, MAX_CARD_LENGTH - 1);
        new_card->front_card[MAX_CARD_LENGTH - 1] = '\0';

        verif = 0;
        while (verif == 0)
        {
            printf("Saisir le derrière de la carte \n");
            scanf(format, verif_card);
            while ((getchar()) != '\n');
            if (verification_card(verif_card))
                verif = 1;
            else
                verif = 0;
        }
        strncpy(new_card->back_card, verif_card, MAX_CARD_LENGTH - 1);
        new_card->back_card[MAX_CARD_LENGTH - 1] = '\0';

        if (*head == NULL)
        {
            *head = new_card;
        }
        else
        {
            current->next = new_card;
        }
        current = new_card;

        printf("Succès ! \n");

        printf("Souhaitez-vous créer une nouvelle carte? (o/n ou autre touche pour exit) \n");
        scanf(" %c", &reponse_new_card);
        while ((getchar()) != '\n');

        if (reponse_new_card == 'n' || reponse_new_card != 'o')
            break;
    }

    FILE *file = fopen("Deck.csv", "a");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier pour écriture.\n");
        return;
    }

    current = *head;
    while (current != NULL)
    {
        fprintf(file, "%s,%s\n", current->front_card, current->back_card);
        current = current->next;
    }

    fclose(file);
}

