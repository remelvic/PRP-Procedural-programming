#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INPUT 69
#define MIN_INPUT 3

#define ERROR_INPUT 100
#define ERROR_INTERVAL 101
#define ERROR_WIDTH_INVALID 102
#define ERROR_PLOT_SIZE 103

void draw_small_house(int width, int height, int count, int count2, int ref);
void roof(int width, int count, int count2, int ref);
void base(int width, int height, bool config, int plot);
void draw_big_house(int width, 
                    int height, 
                    int count, 
                    int count2, 
                    int ref, 
                    int plot);


int main(int argc, char *argv[])
{
  
  int width, height, width_height;
  int second_input;
  int count = 1;

  int input = scanf("%d %d", &width, &height);
  
  //work with big house
  if (input == 2 && width == height){ 
    second_input = scanf("%d", &width_height);
    if(width_height > width && second_input == 1){

       fprintf(stderr,"Error: Neplatna velikost plotu!\n");
       return ERROR_PLOT_SIZE;

    }else{
      draw_big_house(width,height, count, width / 2, width / 2, width_height);
    }
  //work with small house
  }else if (input == 2 && width != height){
    
    if ((width >= 3 && width <= 69) && (height >= 3 && width <= 69)){
      
      if (width % 2 == 1){
        draw_small_house(width, height, count, width / 2, width / 2);

      }else {
        fprintf(stderr,"Error: Sirka neni liche cislo!\n");
        return ERROR_WIDTH_INVALID;
      }


    } else {
      fprintf(stderr, "Error: Vstup je mimo interval!\n");
      return ERROR_INTERVAL;
    }

  } else {
    fprintf(stderr, "ERROR: Chybny vstup!\n");
    return ERROR_INPUT;
  } 
  
  return 0;
}

//We build the roof of the house
void roof(int width, int count, int count2, int ref){
  for(int i = 0; i <  width / 2; ++i){
    count++;
    count2--;
    for(int j = 0; j < width; ++j){
      
      (j == width - count2 - 2 || j == ref - count + 2 ) ? 
      printf("X") :
      printf(" ");

    }
    printf("\n");
  }
}
//We build the foundation of the house
void base(int width, int height, bool config, int plot){
  int space = height - plot;
  int count = 1;
  int count_plot = 1;
  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      if (config){
        (i == 0 || j == 0 || j == width - 1 || i == height - 1) ? 
        printf("X") :
        printf(" ");
      }else{
        if (i == 0 || j == 0 || j == width - 1 || i == height - 1){
          printf("X");
        }else{
          (count % 2 == 1) ? printf("o") : printf("*");
        }
        
        count++;
      }
    }
    while(count_plot != plot + 1){
      if(space < i+1  && count_plot % 2 == 1 && (space == i || height - 1 == i)){
        printf("-");
      }else if (space < i+1 && count_plot % 2 == 1){
        printf(" ");
      }else if (space < i + 1){
        printf("|");
      }
      count_plot++;
    }
    count_plot = 1;
    printf("\n");
  }
}

void draw_small_house(int width, int height, int count, int count2, int ref){
  
  roof(width, count, count2, ref);
  
  base(width, height, true, 0);
}

void draw_big_house(int width, 
                    int height, 
                    int count, 
                    int count2, 
                    int ref, 
                    int plot){

  roof(width, count, count2, ref);

  base (width, height, false, plot);


}