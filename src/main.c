/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <username@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:00:00 by username          #+#    #+#             */
/*   Updated: 2024/06/08 10:00:00 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_card.h"
#include "display_card.h"

int display_menu(void)
{
	int choice;
	
	printf(" Menu:\n");
	printf("1. Créer des cartes\n");
	printf("2. Afficher toutes les cartes\n");
	printf("3. Jouer\n");
	printf("4. Quitter\n");
	printf("Entrez votre choix: \n");
	scanf("%d", &choice);
	printf("\n");
	return choice;
}

int display_menu_choice_two(t_card **head)
{
	int choice;
	
	*head = read_cards_from_file("Deck.csv");
	if (*head == NULL)
	{
		printf("Le fichier est vide ou n'existe pas.\n");
	}
	else
	{
		show_card(*head);
		free_card(*head);
		*head = NULL;
	}
	
	printf(" Voulez vous : \n");
	printf("1. Supprimer une carte ? \n");
	printf("2. Modifier une carte ? \n");
	printf("3. Supprimer toutes les cartes ? \n");
	printf("Autres touche : retour menu\n");
	scanf("%d", &choice);
	
	return choice;
}

void handle_choice_two(int choice)
{
	int number_card_delete;
	int number_card_modify;
	int verif;
	char new_value_front[MAX_CARD_LENGTH];
	char new_value_back[MAX_CARD_LENGTH];

	if (choice == 1)
	{
		printf("Saisir numéro carte à supprimer : ");
		scanf("%d", &number_card_delete);
		delete_card(number_card_delete);
		printf("Le fichier deck.csv a été mis à jour.\n");
	}
	else if (choice == 2)
	{
		verif = 0;
		printf("Saisir numéro carte à modifier :");
		scanf("%d", &number_card_modify);
		while (verif != 1)
		{
			printf("Nouvelle valeur carte avant %d: ", number_card_modify);
			scanf("%s", new_value_front);
			verif = verification_card(new_value_front);
		}
		verif = 0;
		while (verif != 1)
		{
			printf("Nouvelle valeur carte arrière %d: ", number_card_modify);
			scanf("%s", new_value_back);
			verif = verification_card(new_value_back);
		}
		modify_deck(number_card_modify, new_value_front, new_value_back);
		printf("Succès !\n");
	}
	else if (choice == 3)
	{
		delete_all_card();
	}
}

int main(void)
{
	t_card *head = NULL;
	int choice = 0;

	while (choice != 4)
	{
		choice = display_menu();
		while ((getchar()) != '\n')
			;

		if (choice == 1)
		{
			create_card(&head);
		}
		else if (choice == 2)
		{
			choice = display_menu_choice_two(&head);
			handle_choice_two(choice);
			choice = 0;
		}
		else if (choice == 3)
		{
			head = read_cards_from_file("Deck.csv");
			if (head == NULL)
			{
				printf("Le fichier est vide ou n'existe pas.\n");
			}
			else
			{
				play_card(head);
				free_card(head);
				head = NULL;
			}
		}
		else if (choice == 4)
		{
			printf("Sortie du programme.\n");
		}
		else
		{
			printf("Choix invalide, veuillez réessayer.\n");
		}
		printf("\n\n");
	}

	free_card(head);
	return 0;
}

