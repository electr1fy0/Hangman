#include <stdio.h>
#include "hangman.h"

// todo: append score to a file
// convert num to str
// shift down other scores if top score is greater than the rest
// count scores

int score = 0;


int main() {
  printf("############ HANGMAN ############\n");
  int chances, temp_chances;
  int level = 1;
  char romanLevel[50];

  printf("How many chances do you want to have?: ");
  scanf("%d", &chances);
  temp_chances = chances;

  printf("Guess the answer in %d turns\n", chances);
printf("Level: I\n");
  while (gameManager(chances)){
      level++;

      LENGTH++;
      toRoman(romanLevel, level);;
      printf("Level: %s\n", romanLevel );
  }


  return 0;
}
