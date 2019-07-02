#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "string.h"
#include "main.h"

int			main(void)
{
	int 	wordNumber;
	char 	*mysteryWord;

	srand(time(NULL));
	mysteryWord = NULL;
	wordNumber = rand() % lenFile("dico.txt") + 1;
	printf("Mot numéro : %d \n", wordNumber);
	mysteryWord = extractWord(wordNumber, "dico.txt");
	printf("Mot extrait : %s\n", mysteryWord);
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
	printf("Mot extrait : %s\n", mysteryWord);
	fclose(file);
	return (mysteryWord);
}