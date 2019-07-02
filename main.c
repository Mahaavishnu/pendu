#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "main.h"

int			main(void)
{
	int 	wordNumber;
	srand(time(NULL));
	wordNumber = rand() % lenFile("dico.txt") + 1;
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