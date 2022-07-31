#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 10000
#define MIN_INPUT -10000

#define ERROR_INPUT "Error: Vstup je mimo interval"
#define ERROR_INPUT_VALUE 100

int main(int argc, char *argv[])
{
  int input;
  double count_all_number = 0;
  int count_positiv = 0;
  int count_negativ = 0;
  int count_even = 0;
  int count_odd = 0;
  double average = 0;
  int max_number = -10001;
  int min_number = 10001;
  int number;
  while ((input = scanf("%d", &number)) > 0){
    if (number >= MIN_INPUT && number <= MAX_INPUT){
      if(count_all_number > 0){
        printf(", %d", number);
      }else {
        printf("%d", number);
      }
      count_all_number++;
      
      if (number > 0 && number != 0){
        count_positiv++;
      } else if (number < 0 && number != 0){
        count_negativ++;
      }
      number % 2 == 0 ? count_even++ : count_odd++ ;
      average = average + number;

      if (number > max_number){
          max_number = number;
        } 
        if (number < min_number) {
          min_number = number;
        }
    }else {
      printf("\n%s\n", ERROR_INPUT);
      return ERROR_INPUT_VALUE;
    }
  }
  printf("\n");
  printf("Pocet cisel: %.0f\n",count_all_number);
  printf("Pocet kladnych: %d\n", count_positiv);
  printf("Pocet zapornych: %d\n", count_negativ);
  double percent_pos = ((count_positiv * 100) / (count_all_number)); 
  double percent_neg = ((count_negativ * 100) / (count_all_number)); 
  double percent_even = ((count_even * 100) / (count_all_number)); 
  double percent_odd = ((count_odd * 100) / (count_all_number)); 
  printf("Procento kladnych: %.2f\n", percent_pos);
  printf("Procento zapornych: %.2f\n",percent_neg);
  printf("Pocet sudych: %d\n", count_even);
  printf("Pocet lichych: %d\n", count_odd);
  printf("Procento sudych: %.2f\n", percent_even);
  printf("Procento lichych: %.2f\n", percent_odd);
  printf("Prumer: %.2f\n", average / count_all_number);
  printf("Maximum: %d\n", max_number);
  printf("Minimum: %d\n", min_number);

  return 0;
}
