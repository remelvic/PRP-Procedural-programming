#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_NUMBERS_SIEVE 1000000
#define ERROR_INPUT 100
 
int sieve_array[MAX_NUMBERS_SIEVE];
int primes_index = 0;

// The function takes values from the console
long long read_input();

//Decomposes a number into prime numbers. For mandatory and optional parts
void decompose(long number, int* prime_array, int size);

//I return the number of primes in the array. 
//Prime_array in all places has either 0 or prime numbers up to 1000000
int sieve();

//Initializing an array to find prime numbers
void init_prime_array();

//get all prime numbers 
int* get_prime_numbers(int* prime_array);

int main(int argc, char *argv[]){

  long number;

  init_prime_array();
  
  primes_index = sieve();
  
  int prime_array[primes_index];
  
  int *prime_numbers_array = get_prime_numbers(prime_array);

  while((number = read_input()) > 0){
    
    printf("Prvociselny rozklad cisla %ld je:\n",number);
    
    if (number == 1){
      printf("1\n");
    }else{
      
      decompose(number,prime_numbers_array, primes_index);
    }
    
  }
  if (number < 0){
    fprintf(stderr,"Error: Chybny vstup!\n");
    return ERROR_INPUT;
  }
  
  return 0;
}

void init_prime_array(){
  for(int i = 0; i < MAX_NUMBERS_SIEVE; i++){
    if (i <= 1){
      sieve_array[i] = 0;
    }else {
      sieve_array[i] = i;
    }
  }
}

long long read_input(){
  long number;
  return (scanf("%ld", &number) != 1) ? -1 : number;
}

int sieve(){
	int count = 0;
	
	for (int i = 0; i * i < MAX_NUMBERS_SIEVE; ++i){
		if (sieve_array[i] != 0){
			for(int k = (2 * i); k < MAX_NUMBERS_SIEVE; k += i){
				sieve_array[k] = 0;
			}
		}
	}
	for(int i = 0; i < MAX_NUMBERS_SIEVE; i++){
		if (sieve_array[i] != 0){
			count++;
		}
	}
	return count;
}

int* get_prime_numbers(int* prime_array){
  //get numbers from sieve
  int count = 0;
  for(int i = 2; i < MAX_NUMBERS_SIEVE; i++){
    
    if(sieve_array[i] != 0) {  
      prime_array[count] = sieve_array[i];
      count++;
    }
  }
  return prime_array;
}

void decompose(long number, int prime_array[], int size){
  _Bool space = false;
   
  for(int i = 0; i <= size; ++i){
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
      if (count > 1) { 
        printf("%d^%d", prime_array[i], count); 
      } else {
        printf("%d",prime_array[i]);
      }
      space = true; 
    }
  }
  if(number > 1){
    if (space) printf(" x ");
    printf("%ld",number);
  }
  printf("\n");
}
