#ifndef _SNAKE_H_ 
#define _SNAKE_H_ 

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <termios.h> 
#include <fcntl.h> 
#include <time.h>
#include <string.h>
#include <signal.h>

#define MAX_X_SIZE_TABLE            50 
#define MAX_Y_SIZE_TABLE            25

#define SNAKE_X_INIT            (u8)5 
#define SNAKE_Y_INIT            (u8)5 
#define SNAKE_INIT_SIZE         (u8)2
#define SNAKE_HEAD              (u8)0 
#define SNAKE_TAIL              get_snake_tail() 

#define TABLE_SCREEN            (char)'.'
#define TABLE_BORDER            (char)'*'
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

u16 snake_size;
u16 user_point = 0;

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
int snake_display(void); 
int snake_move(void);
int snake_grow(void);
unsigned char get_snake_tail(void);
int init_play_table(void); 
int print_play_table(void); 
int clear_table(void); 
void clear_screen(void); 
int kbhit(void); 
unsigned int rand_num(int upper, int lower);
/*Player functions*/
int usr_navigation(void);
int player_info(void);
int hit_wall_check(void);

/*Food functions*/ 
int food_gen(void); 
int food_display(void); 

/*System supported functions*/
int init_play_table(void); 
int print_play_table(void); 
int clear_table(void); 
void clear_screen(void); 
int kbhit(void); 
unsigned int rand_num(int upper, int lower);

/*Signal handler*/
void signal_handler(int sig);

#endif /*_SNAKE_H_*/
