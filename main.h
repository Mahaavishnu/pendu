char		readChar();
int			lenFile(char *filename);
char		*extractWord(int wordNumber, char *filename);
void		printWord(char *mysteryWord, int *tab);
int			guessChar(char *mysteryWord, int *tab);
int			testEndGame(char *mysteryWord, int *tab);