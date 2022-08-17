#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_FOR_MANDATORY 100000000
#define MAX_NUMBERS_SIEVE 1000000

#define ERROR_INPUT 100

// The function takes values from the console
long long read_input();

int *prime_numbers_array;
int sieve_array[MAX_NUMBERS_SIEVE];
int size_sieve = 0;
//Decomposes a number into prime numbers
void decompose(long long number); //mandatory

void decompose_opt(long long number, int* prime_array, int size);

//void sieve(long int number);
void sieve(long long number);

int main(int argc, char *argv[])
{
  long long number;
  
  while((number = read_input()) > 0){
    
    printf("Prvociselny rozklad cisla %lld je:\n",number);
    
    if (number == 1){
      printf("1\n");
    }else{
      
      // prime_numbers_array = (int*)calloc(MAX_NUMBERS_SIEVE,sizeof(int)); 

      
      sieve(number);
      printf("ALOOOOOO %d\n",size_sieve); 
      // for(int i = 0; i < size_sieve; i++){
      //   printf("%d ",prime_numbers_array[i]);
      // }
      for(int i = 0; i < MAX_NUMBERS_SIEVE; i++){
        printf("array_end %d \n",sieve_array[i]);
        if(sieve_array[i] == 1) {
      //     printf("%d ", i);
          prime_numbers_array[i] = i;
          size_sieve++;
        }
      }
      decompose_opt(number,prime_numbers_array, size_sieve);
      
      
    }
    
  }
  if (number < 0){
    fprintf(stderr,"Error: Chybny vstup!\n");
    return ERROR_INPUT;
  }
  
  free(prime_numbers_array);
  return 0;
}

long long read_input(){
  long long number;
  return (scanf("%lld", &number) != 1) ? -1 : number;
}

void decompose_opt(long long number, int* prime_array, int size){
  _Bool space = false;
   
  for(int i = 2; i <= size; ++i){
    int count = 0;
    while(number % prime_array[i] == 0){
      

      number = number / prime_array[i];
      
      count++;
    }
    if(count > 0){
      size = sqrt(size);
      if(space){
        printf(" x ");
      }
      count > 1 ? printf("%d^%d", prime_array[i], count) : printf("%d",prime_array[i]);
      space = true; 
    }
  }
  if(number > 1){
    if (space) printf(" x ");
    printf("%lld",number);
  }
  printf("\n");
}

// void sieve(long number, long *sieve_array){
  
//   for(int i = 1; i < number; i++){
//     sieve_array[i] = 1;
//   }
//   for(int i = 2; i <= sqrt(number); i++){
//     int count = 0;
//     printf("SIEVE_ARRAY ELEMENT %ld\n", sieve_array[i]);
//     if(sieve_array[i] == 1){
      
//       for(int j = i*i; j <= number; j = (i*i)+count*i){      
//         count++;
//         sieve_array[j] = 0;  
//       }
//     }
//   }
// }

void sieve(long long number){
  prime_numbers_array = (int*)calloc(MAX_NUMBERS_SIEVE,sizeof(int)); 

  for(int i = 0; i < MAX_NUMBERS_SIEVE; i++){
    sieve_array[i] = 1;
  }
  
  for(int k = 2; k < MAX_NUMBERS_SIEVE; k++){
    int count = 0;
    //if(sieve_array[k] != 0){
      // printf("sieve_array %d -- index i: %d\n",sieve_array[k], k);
      
      // prime_numbers_array[size_sieve++] = sieve_array[k];
      // for(int j = k; j < MAX_NUMBERS_SIEVE; j = j * 2){
      //   sieve_array[j] = 0;
      // }
      if(sieve_array[k] == 1){
        for(int j = k*k; j < number && j < MAX_NUMBERS_SIEVE; j = (k*k)+count*k){      
          //prime_numbers_array[size_sieve++] = sieve_array[k];
          count++;
          if(j < MAX_NUMBERS_SIEVE){
            sieve_array[j] = 0;
            
            //prime_numbers_array[size_sieve++] = j;
          }
        }
      }
  }
} 