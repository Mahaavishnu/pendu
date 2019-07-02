#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "main.h"

int			main(void)
{
	int 	wordNumber;
	char 	*mysteryWord;
	int		tries;
	int		*tab;
	int		len;

	srand(time(NULL));
	mysteryWord = NULL;
	tries = 10;
	wordNumber = rand() % lenFile("dico.txt") + 1;
	printf("Mot numéro : %d \n", wordNumber);
	mysteryWord = extractWord(wordNumber, "dico.txt");
	len = strlen(mysteryWord);
	tab = (int *)malloc(sizeof(int)*len);
	while (len)
	{
		tab[len-1] = 0;
		len--;
	}
	//printf("Mot extrait : %s\n", mysteryWord);
	printf("Bienvenu dans le Pendu !\n\n");
	while (tries)
	{
		printf("Il vous reste %d coups à jouer.\nQuel est le mot secret ? ", tries);
		printWord(mysteryWord, tab);
		printf("Proposez une lettre : ");
		if (guessChar(mysteryWord, tab) == 0)
			tries--;
		else if (testEndGame(mysteryWord, tab) == 1)
		{
			printf("Gagné ! le mot secret était bien : %s.\n", mysteryWord);
			return (0);
		}
		printf("\n");
	}
	free(mysteryWord);
	return (0);
}

char		readChar()
{
	char 	toRead;

	toRead = 0;
	toRead = getchar();
	toRead = toupper(toRead);

	while (getchar() != '\n');

	return (toRead);
}

int			lenFile(char *filename)
{
	FILE 	*file;
	char 	toRead;
	int		len;

	file = NULL;
	file = fopen(filename, "r");
	if (file == NULL)
		return (-1);
	toRead = 0;
	len = 0;
	while ((toRead = fgetc(file)) != EOF)
		if (toRead == '\n')
			len++;
	fclose(file);
	return (len + 1);
}

char		*extractWord(int wordNumber, char *filename)
{
	FILE 	*file;
	int		len;
	char 	*mysteryWord;

	len = 0;
	mysteryWord = NULL;
	file = NULL;
	file = fopen(filename, "r");
	if (file == NULL)
		return NULL;
	while (--wordNumber)
		while (fgetc(file) != '\n');
	while (fgetc(file) != '\n')
		len++;
	fseek(file, -len-1, SEEK_CUR);
	mysteryWord = (char *)malloc(sizeof(char)*len+1);
	if (mysteryWord == NULL)
		printf("malloc mysteryWord échoué\n");
	printf("Longueur du mot : %d\n", len);
	if (fgets(mysteryWord, len+1, file) == NULL)
		printf("problème avec fgets");
	//printf("Mot extrait : %s\n", mysteryWord);
	fclose(file);
	return (mysteryWord);
}

void		printWord(char *mysteryWord, int *tab)
{
	int		len;
	int		pos;

	len = strlen(mysteryWord);
	pos = 0;
	while (pos != len)
	{
		if (tab[pos] == 1)
			printf("%c", mysteryWord[pos]);
		else
			printf("*");
		pos++;
	}
	printf("\n");
}

int			guessChar(char *mysteryWord, int *tab)
{
	int		len;
	char 	guess;
	int 	result;

	len = strlen(mysteryWord);
	guess = readChar();
	result = 0;
	while (len)
	{
		if (mysteryWord[len-1] == guess)
		{
			tab[len-1] = 1;
			result = 1;
		}
		len--;
	}
	return (result);
}

int		testEndGame(char *mysteryWord, int *tab)
{
	int	len;

	len = 0;
	len = strlen(mysteryWord);
	while (len)
	{
		if (tab[len-1] == 0)
			return (0);
		len--;
	}
	return (1);
}