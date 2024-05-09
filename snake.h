#ifndef _SNAKE_H_ 
#define _SNAKE_H_ 

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <termios.h> 
#include <fcntl.h> 
#include <time.h>

#define MAX_X_SIZE_TABLE            40 
#define MAX_Y_SIZE_TABLE            20

#define SNAKE_X_INIT            (u8)5 
#define SNAKE_Y_INIT            (u8)5 
#define SNAKE_MAX_SIZE          (u8)10 
#define SNAKE_HEAD              (u8)0 
#define SNAKE_TAIL              get_snake_tail() 

#define TABLE_SCREEN            (char)'.' 
#define SNAKE_SYMBOL            (char)'#' 
#define FOOD_SYMBOL             (char)'@' 
#define REFRESH_RATE            150000 

#define RET_OK                  0 
#define RET_NOT_OK              1 

#define MV_RGHT                 1 
#define MV_LFT                  2 
#define MV_UP                   3 
#define MV_DWN                  4 

#define u8                  unsigned char 
#define u16                 unsigned short 

typedef struct 
{ 
    u8 x,y; 
    u8 mv_state; 
}snake_st; 

typedef struct 
{ 
    u8 x,y; 
}food_st; 

/*Snake functions*/ 
extern int snake_display(void); 
extern int usr_navigation(void); 
extern int snake_move(void); 
extern unsigned char get_snake_tail(void); 

/*Food functions*/ 
extern int food_gen(void); 
extern int food_display(void); 
extern int init_table(void); 
extern int print_table(void); 
extern int clear_table(void); 
extern void clear_screen(void); 
extern int kbhit(void); 
extern unsigned int rand_num(int upper, int lower); 

#endif /*_SNAKE_H_*/
