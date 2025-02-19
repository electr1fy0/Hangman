#ifndef HANGMAN_H
#define HANGMAN_H

extern int LENGTH;

extern int score;

int compareNums(const void *a, const void *b);
char *wordGenerator(int length);
int Game(const char answer[], char word[], int length);
char gameManager(char chances);

void toRoman(char *arr, int num);
void leaderBoard();


#endif
