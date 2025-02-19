#include "hangman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int LENGTH = 5;

int compareNums(const void *a, const void *b) { return *(int *)b - *(int *)a; }

char *wordGenerator(int length) {
  srand(time(NULL));

  char *word = malloc(length + 1);
  if (!word)
    return NULL;

  for (int i = 0; i < length; ++i) {
    int letter = rand() % 26 + 97;
    word[i] = (char)letter;
  }
  word[length] = '\0';
  return word;
}

int Game(const char answer[], char word[], int length) {
  printf("%s ", word); // print the dashes and hints
  int score = 0;

  char input[length + 1];
  scanf("%s", input);

  for (int i = 0; i < length; ++i) {
    if (input[i] == answer[i]) {
      word[i] = input[i];
    }
    if (strcmp(answer, word) == 0) {
      return 1;
    }
  }
  // printf("%s\n", word);
  return 0;
}

void leaderBoard() {
  int score_top[6];

  FILE *score_file_ptr;
  score_file_ptr = fopen("score.txt", "r+");
  while (score_file_ptr == NULL) {
    fopen("score.txt", "w");

    printf("Error saving the score\n, retrying...");
    score_file_ptr = fopen("score.txt", "r+");
  }
  score_top[5] = score;
  for (int i = 0; i < 5; ++i)
    fscanf(score_file_ptr, "%d", &score_top[i]);

  qsort(score_top, 6, sizeof(int), compareNums);
  fseek(score_file_ptr, 0, SEEK_SET);
  char entry[50];
  for (int i = 0; i < 5; ++i) {
    fprintf(score_file_ptr, "%d\n", score_top[i]);
  }

  // fputs(entry, score_file_ptr);
  // fputs("\n", score_file_ptr);
  fclose(score_file_ptr);
  printf("############ LEADERBOARD ############\n");

  for (int i = 0; i < 5; ++i) {
    printf("%d: %d", i + 1, score_top[i]);
    if (score_top[i] == score)
      printf(" <- You\n");
    else
      printf("\n");
  }
}

char gameManager(char chances) {
  char approval = 'y';

  char *answer = wordGenerator(LENGTH);
  if (!answer) {
    printf("Memory allocation failed!\n");
    exit(1);
  }

  char *word = malloc(LENGTH + 1);
  if (!word) {
    free(answer);
    printf("Memory allocation failed!\n");
    exit(1);
  }

  for (int i = 0; i < LENGTH; ++i) {
    word[i] = '-';
  }

  printf("Answer: %s\n", answer);

  while (chances--) {
    if (Game(answer, word, LENGTH)) {
      score += 50;
      printf("\nYour current score is %d. Press y to continue: ", score);

      fflush(stdin);
      scanf("%c", &approval);
      free(answer);
      free(word);

      break;
    }

    else if (chances > 1)
      printf("Try again. %d chances left.\n", chances);
    else if (chances == 1)
      printf("Try again. %d last chance now.\n", chances);
    else {
      printf("Game over! Your final score is %d.\n", score);
      leaderBoard();
      return 0;
    }
  }
  if (approval == 'y') {
    return 1;
  } else {
    printf("Game over! Alright, see ya then.\n");
    leaderBoard();

    return 0;
  }
}

void toRoman(char *arr, int num) {
  struct {
    int n;
    const char *value;
  } roman[] = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
               {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
               {5, "V"},    {4, "IV"},   {1, "I"}};
  int i = 0;
  int j = 0;
  while (num > 0) {
    while (num >= roman[i].n) {
      num -= roman[i].n;
      for (int k = 0; roman[i].value[k] != '\0'; ++k) {
        *(arr + j++) = roman[i].value[k];
      }
    }
    i++;
  }
  arr[j] = '\0';
}

void numToStr(char target[]) { // unused I think
  int num = score;
  if (num == 0) {
    target[0] = '0';
    target[1] = '\0';
    return;
  }
  int temp_num = num;
  int num_length = 0;
  while (temp_num > 0) {
    num_length++;
    temp_num /= 10;
  }

  for (int i = num_length - 1; i >= 0; --i) {
    target[i] = num % 10 + '0';
    num /= 10;
  }

  target[num_length] = '\0';
}
