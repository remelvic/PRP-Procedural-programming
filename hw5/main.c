#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#define A 65             // According 
#define SMALL_A 97       // to the
#define Z 90             // ASCII
#define SMALL_Z 122      // table
#define ALL_LETTERS 52   
#define ALPHABET 26
 
enum {ERROR_INPUT = 100, ERROR_LENGHT = 101, ERROR_MALLOC = -100};
 
int search(char *array_test, char *array_control);        // Looking for the maximum match by characters
char *shift(char *arr_shift, int size_arr_shift);         // Shift fields letter by letter
char *shift2(char *arr_shift, int size_arr_shift,int shift2);
int read_input(char *array,_Bool flag);                   // Read input and return size of array 
void controll_malloc(char *array, int row_number);        // Checking the correct memory allocation
void free_memory(char *first_array, char *second_array);  // Freeing memory 

int len_arr1 = 0; // The length of the first array
int len_arr2 = 0; // The length of the second array
char *array1;
char *array2;
 
int main(int argc, char *argv[])
{
  array1 = malloc(len_arr1 *sizeof(char)); // Allocate space for the first array
  controll_malloc(array1, __LINE__);

  len_arr1 = read_input(array1,false);
  
  array2 = malloc(sizeof(char) * len_arr2); // allocate space for the second array 
  controll_malloc(array2, __LINE__);
  
  len_arr2 = read_input(array2, true);
 
  if (len_arr1 != len_arr2) { // equal length check
    fprintf(stderr, "Error: Chybna delka vstupu!\n");
    free_memory(array1, array2);
    return ERROR_LENGHT;
  }
 
  int max = search(array1, array2); 
  int maxshift2 = 0;
  for (int i = 0; i < ALL_LETTERS; i++) {      // 52 because 26 small letters + 26 large letters
    array1 = shift(array1, len_arr1);     // looking for the most suitable match
    int j = search(array1, array2);     
    if (j > max) {
      max = j;
      maxshift2 = (i + 1);
      }
    }
   
  array1 = shift2(array1, len_arr1, maxshift2);
  for (int l = 0; l < len_arr1 - 1; l++) {
    printf("%c", array1[l]); // write out the resulting value
  }
  printf("\n");
  free_memory(array1, array2);
  return 0;
}
 
char *shift(char *arr_shift, int size_arr_shift) 
{
  for (int i = 0; i < size_arr_shift; i++) {
    if (arr_shift[i] < Z && arr_shift[i] >= A) { // between A -Z
      arr_shift[i] = arr_shift[i] + 1;
    } else if (arr_shift[i] < SMALL_Z && arr_shift[i] >= SMALL_A) { // between a - z
      arr_shift[i] = arr_shift[i] + 1;
    } else if (arr_shift[i] == Z) {
      arr_shift[i] = SMALL_A;
    } else if (arr_shift[i] == SMALL_Z) {
      arr_shift[i] = A;
    }
  }
  return arr_shift;
}
 
char *shift2(char *arr_shift, int size_arr_shift,int shift2) 
{
  for (int i = 0; i < size_arr_shift; i++) {
    if (arr_shift[i] + shift2 <= Z && arr_shift[i] >= A) { // between A -Z
      arr_shift[i] = arr_shift[i] + shift2;
    } else if (arr_shift[i] + shift2 <= SMALL_Z && arr_shift[i] >= SMALL_A) { // between a - z
      arr_shift[i] = arr_shift[i] + shift2;
 
    } else if (arr_shift[i] + shift2 > SMALL_Z && arr_shift[i] >= SMALL_A) {
      int lastshift = shift2 + arr_shift[i] - SMALL_Z - 1;
      if (lastshift < ALPHABET) { // checks if there are more than 26 characters
        arr_shift[i] = A + lastshift;
      } else {
        arr_shift[i] = SMALL_A + lastshift % ALPHABET;
      }
    } else if (arr_shift[i] + shift2 > Z) {
      int lastshift = shift2 + arr_shift[i] - Z - 1;
      if (lastshift < ALPHABET) {
        arr_shift[i] = SMALL_A + lastshift;
      } else {
        arr_shift[i] = A + lastshift % 26;
      }
    } 
  }
  return arr_shift;
}
 
int search(char *array_test, char *array_control) 
{
  int count = 0;
  int index = 0;
  while (array_test[index] !='\0' && array_control[index] !='\0') { // Check to the end of one of the lines
    if (array_test[index] == array_control[index]) {
      count += 1;
    }
    index += 1;
  }
  return count;
}

int read_input(char *array, _Bool flag){
  char input;
  int len_arr = 0;
  do {
    len_arr += 1;
    array = realloc(array, sizeof(char) * len_arr);
    scanf("%c", &input);
    array[len_arr - 1] = input;    // subtract the last item because it is either "\ 0" or "\ n"
    if ((input != '\n' && flag == false) || (input != '\n' && input != '\0' && flag == true)) {
      if (input < A || (input > Z &&  input < SMALL_A) || input > SMALL_Z) {    // validating an array
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(ERROR_INPUT);
      }
    }
  } while ((input != '\n' && input != '\0') || input != '\n');
     // Execute until we reach the end of the line
  array[len_arr - 1]= '\0';
  
  if (flag == false){
    array1 = array;
  }else {
    array2 = array;
  }
  return len_arr;
}

void controll_malloc(char *array, int row){
  if (array == NULL){
    fprintf(stderr,"ERROR: maloc failed in file %s, on row %d", __FILE__, row);
    exit(ERROR_MALLOC);
  }
}

void free_memory(char *first_array, char *second_array){
  free(first_array);
  free(second_array);
}