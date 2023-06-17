#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void check_high_score(int score, char *name);
void read_high_score(int *score, char *name);
void check_high_score(int score, char *name) {
  int high_score;
  char high_score_name[50];
  read_high_score(&high_score, high_score_name);
  if (score > high_score) {
    FILE *fptr = fopen("high_scores.txt", "w");
    char name[50];
    printf("\nYou have the Highscore! Give your name: ");
    scanf("%s", name);
    fprintf(fptr, "%d\n%s", score, name);
    fclose(fptr);
  }
}
void read_high_score(int *score, char *name) {
  *score = 0;
  strcpy(name, ""); 
  FILE *fptr = fopen("high_scores.txt", "r");
  if (fptr != NULL) {
    fscanf(fptr, "%d\n%s", score, name);
    fclose(fptr);
  }
}
int menu() {
  int preference;
  printf("\nSimon Says\n");
  printf("\n1:Start\n");
  printf("2:Highscore\n");
  printf("q:Finish\n");
  if(scanf("%d", &preference) != 1){
        return 0;}
  return preference;
}
void high_score(){
  int high_score;
  char high_score_name[50];
  read_high_score(&high_score, high_score_name);
  printf("\nHIGHSCORE: %d - %s\n", high_score, high_score_name);  
}
int main(void) {
start:
while(1>0){
  int preference = menu();
  if (preference == 1) { 
    printf("\nThe numbers:\n");
    int numbers[100];
    int round = 0;
    int guess;
    int x = 0;
    for (int i = 0; i <= round; i++) {
      srand(time(0));
      int number = (rand() % 4) + 1;
      int timer = round + 1;
      numbers[i] = number;
      if (x == 0) {
        printf("%d", number);
        x = 1;
      } else {
        for (int t = 0; t <= i; t++) {
          printf("%d", numbers[t]);
        }
      }
      fflush(stdout);
      sleep(timer);
      system("clear");
      int digits[100];
      int digit = 0;
      printf("Round: %d\n", timer);
      high_score();
      printf("\nGive the numbers: ");
      if(scanf("%d", &guess) != 1){
        fprintf(stderr,"Invalid choice! Please start again.\n");
        return 0;
}
      while (guess > 0) {
        digits[digit] = guess % 10;
        guess /= 10;
        digit++;
      }
      int reverse =
          round;
      for (int k = 0; k <= round; k++) {
        if (digits[reverse] == numbers[k]) {
          reverse--;
          continue;
        }
        else {
          printf("Wrong!\n");
          printf("Score:%d\n", round);
          int current_score = round;
          char current_name[50];
          check_high_score(current_score, current_name);
          high_score();
          goto start;
        }
      }
      printf("\nCorrect! You have %d seconds...\n", round + 2);
      round++;
    }
  } 
  else if (preference == 2){
    high_score();
    goto start;
  }
  else{
    printf("\nGame Over!");
    return 0;
  }
  }  
}