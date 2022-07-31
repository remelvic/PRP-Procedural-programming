#include <stdio.h>
#include <stdlib.h>

#define MAXIMUM 10000
#define MINIMUM -10000

void compute_number(int num1, int num2);

/* The main program */
int main(int argc, char *argv[])
{
  int number1;
  int number2;
  int input = scanf("%d %d", &number1, &number2);

  if (input == 2 && (number1 < MINIMUM || number1 > MAXIMUM || number2 < MINIMUM || number2 > MAXIMUM)){
    printf("Vstup je mimo interval!\n");
    return 0;
  }else{
    compute_number(number1, number2);
  }
  
  return 0;
}

void compute_number(int num1, int num2){
  printf();
  printf("Desitkova soustava: %d %d\n", num1, num2);
  printf("Sestnactkova soustava: %x %x\n", num1, num2);
  printf("Soucet: %d + %d = %d\n", num1,num2, num1+num2);
  printf("Rozdil: %d - %d = %d\n", num1,num2, num1-num2);
  printf("Soucin: %d * %d = %d\n", num1,num2, num1*num2);
  if (num2 != 0)
    printf("Podil: %d / %d = %d\n", num1, num2, num1/num2);
  else 
    printf("Nedefinovany vysledek!\n");
  
  printf("Prumer: %.1f\n", (num1+num2)/2.);
}