#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
enum {ERROR = 100, ERROR_MALLOC = -100};

//In the function, we determine which operator we are working with and carry out multiplication, subtraction or addition
int **operation_exec(int **mat_1, int **mat_2, int size_r1, int size_c1, int size_r2, int size_c2, int **result, char oper);

//Read the data and write to the matrix, allocate memory for the matrix
int **read_matrix(int row, int col, _Bool flag);

void check_malloc(void* array_check, int row);

void free_memory(int** array_free, int count); 

int main(int argc, char *argv[])
{
  char oper; // operator
  int row1, col1; 
  int row2, col2;
  int **matrix1 = NULL;
  int **matrix2 = NULL;
  int **result = NULL;
  int result_r;
  int result_c;
   
  if (scanf("%d %d", &row1, &col1) == 2 && row1 >= 0 && col1 >= 0) { // matrix size check 

    matrix1 = read_matrix(row1, col1, true);

  } else {
    fprintf(stderr, "Error: Chybny vstup!\n");
    free_memory(matrix1, row1);
    
    return ERROR;
  }
  scanf("\n%c", &oper); // read the sign (+, -, *)
 
  if (scanf("%d %d", &row2, &col2) == 2 && row2 >= 0 && col2 >= 0) { 

    matrix2 = read_matrix(row2,col2, false);

  } else {

    fprintf(stderr, "Error: Chybny vstup!\n");

    free_memory(matrix2, row2);
    free_memory(matrix1, row1);
    return ERROR;
 
  }
 
  if (oper == '+' || oper == '-' || oper == '*') { // if our operator '+' is adding
    
    result = malloc(sizeof(int*) * row1);
    check_malloc(result, __LINE__);

    result_r = row1;
    if(oper != '*'){
      result_c = col1;
      
      for (int i = 0; i < row1; i++) {
        result[i] = malloc(sizeof(int) * col1);
        check_malloc(result[i], __LINE__);
      }
      
      result = operation_exec(matrix1, matrix2, row1, col1, row2, col2, result, oper);
    
    }else {
      result_c = col2;
      for (int i = 0; i < row1; i++) {
        result[i] = malloc(sizeof(int) * col2);
        check_malloc(result[i], __LINE__);
      }
      result = operation_exec(matrix1, matrix2, row1, col1, row2, col2, result, oper);
    }
     
  } else {
    fprintf(stderr, "Error: Chybny vstup!\n");
    free_memory(matrix2, row2);
    free_memory(matrix1, row1);
    free_memory(result, row1);

    return ERROR;
  }
 
  printf("%d %d\n",result_r, result_c);  // write out our size of our final matrix
  for (int i = 0; i < result_r; i++) {
    for (int j = 0; j < result_c; j++) {
      if (j != result_c - 1) {
      printf("%d ", result[i][j]);    // write out the value of the matrix except for the last value of the matrix
      } else {
        printf("%d", result[i][j]);  // write out the last value of the matrix
      }
    }
    printf("\n");
  }

  free_memory(matrix2, row2);
  free_memory(matrix1, row1);
  free_memory(result, result_r);

  return 0;
}

int **operation_exec(int **mat_1, int **mat_2, int size_r1, int size_c1, int size_r2, int size_c2, int **result, char oper)
{
  if (oper == '*' && size_c1 == size_r2){
    
    for (int i = 0; i < size_r1; i++) {
      for (int j = 0; j < size_c2; j++) {
        int sum = 0;
        for (int k = 0; k < size_r2; k++) {
          sum += mat_1[i][k] * mat_2[k][j];
        }
        result[i][j] = sum;  // we output our result into a new matrix
      }
    }
    
  } else if ((oper == '-' || oper == '+') && (size_r1 == size_r2 && size_c1 == size_c2)){
    
    for (int i = 0; i < size_r1; i++) {
      for (int j = 0; j < size_c1; j++) {
        if(oper == '+'){
          result[i][j] = mat_1[i][j] + mat_2[i][j];
        } else {
          result[i][j] = mat_1[i][j] - mat_2[i][j];
        }
      }
    }

  }else {
    fprintf(stderr, "Error: Chybny vstup!\n");
      free_memory(mat_1, size_r1);
      free_memory(result, size_r1);
      free_memory(mat_2, size_r2);
      exit(ERROR);  
  }
  return result;
}

int **read_matrix(int row, int col, _Bool flag){
  int** matrix;

  matrix = malloc(sizeof(int*) * row);
  check_malloc(matrix, __LINE__);

  for(int r_num = 0; r_num < row; r_num++){
    matrix[r_num] = malloc(sizeof(int) * col);
    check_malloc(matrix[r_num], __LINE__);

    for (int c_num = 0; c_num < col; c_num++) {
      int c = scanf("%d", &matrix[r_num][c_num]);  // write the matrix
      if (flag == true && c != 1) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        for (int i = 0; i <= r_num; i++) {
          free(matrix[i]);
        }
        free(matrix);
        exit(ERROR);
      }
    }
  }
  return matrix;
}

void check_malloc(void* array_check, int row){

  if (array_check == NULL){
    fprintf(stderr, "ERROR: malloc failed in file %s on row %d\n", __FILE__, row);
    exit(ERROR_MALLOC);
  }
}

void free_memory(int** array_free, int count){

  for(int i = 0; i < count; i++){
    free(array_free[i]);
  }
  free(array_free);

}