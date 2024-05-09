#include "snake.h" 

char table[MAX_Y_SIZE_TABLE][MAX_X_SIZE_TABLE] = {0}; 
snake_st mysnake[SNAKE_MAX_SIZE] = {0}; 
food_st myfood; int main(int agrc, char *agrv[]) 
{ 
    init_table(); 
    print_table(); 
    while(1) 
    { 
        snake_display(); 
        food_display(); 
        // Print the table with the updated snake and food position 
        print_table(); 
        usleep(REFRESH_RATE); 
    } 
    return RET_OK; 
} 

/*----------- Function Initalization -----------*/ 

int init_table() 
{   
    for(u8 i=0; i<MAX_Y_SIZE_TABLE; i++) 
    { 
        for(u8 j=0; j<MAX_X_SIZE_TABLE; j++) 
        {
            if((i==0) || (i==(MAX_Y_SIZE_TABLE-1)) || (j==0) || (j==(MAX_X_SIZE_TABLE-1)))
            {
                table[i][j] = TABLE_BORDER;    
            }
            else
            {
                table[i][j] = TABLE_SCREEN;
            }
        } 
    } 
    
    //snake init position 
    mysnake[SNAKE_HEAD].x = rand_num(MAX_Y_SIZE_TABLE-1, 1); 
    mysnake[SNAKE_HEAD].y = rand_num(MAX_Y_SIZE_TABLE-1, 1); 
    
    //food init position 
    myfood.x = rand_num(MAX_Y_SIZE_TABLE-1, 1); 
    myfood.y = rand_num(MAX_Y_SIZE_TABLE-1, 1); 
    
    return RET_OK; 
} 

int print_table(void) 
{ 
    clear_screen(); 
    for(u8 i=0; i<MAX_Y_SIZE_TABLE; i++) 
    { 
        for(u8 j=0; j<MAX_X_SIZE_TABLE; j++) 
        { 
            printf("%c", table[i][j]); 
        } printf("\n"); 
    } 
    
    return RET_OK; 
} 

int snake_display(void) 
{ 
    // Clear the snake's previous position 
    table[mysnake[SNAKE_TAIL].y][mysnake[SNAKE_TAIL].x] = TABLE_SCREEN; 
    
    //user navigation 
    usr_navigation(); 
    
    //update snake moving and body inheritance 
    snake_move(); 
    
    // Update the snake's position in the table 
    for(unsigned int i=SNAKE_HEAD; i<=get_snake_tail(); i++) 
    { 
        table[mysnake[i].y][mysnake[i].x] = SNAKE_SYMBOL; 
    } 
    
    return RET_OK; 
}

int usr_navigation(void) 
{ 
    //Update the snake's position 
    if (kbhit()) 
    { 
        //Read the input character 
        char ch = getchar(); 
        switch (ch) 
        { 
            case 'w': // Up 
            if(mysnake[SNAKE_HEAD].mv_state != MV_DWN) 
            { 
                mysnake[SNAKE_HEAD].mv_state = MV_UP; 
            } 
            break; 
            
            case 's': // Down 
            if(mysnake[SNAKE_HEAD].mv_state != MV_UP) 
            { 
                mysnake[SNAKE_HEAD].mv_state = MV_DWN; 
            } 
            break; 
            
            case 'a': // Left 
            if(mysnake[SNAKE_HEAD].mv_state != MV_RGHT) 
            { 
                mysnake[SNAKE_HEAD].mv_state = MV_LFT; 
            } 
            break; 
            
            case 'd': // Right 
            if(mysnake[SNAKE_HEAD].mv_state != MV_LFT) 
            { 
                mysnake[SNAKE_HEAD].mv_state = MV_RGHT; 
            } 
            break; 
            
            default: 
            break; 
        } 
    } 
    
    return RET_OK; 
} 

int snake_move() 
{ 
    //update HEAD position 
    if(mysnake[SNAKE_HEAD].mv_state == MV_RGHT) 
    { 
        if(mysnake[SNAKE_HEAD].x < MAX_X_SIZE_TABLE - 1) 
        { 
            mysnake[SNAKE_HEAD].x++; 
        } 
    } 
    else if(mysnake[SNAKE_HEAD].mv_state == MV_LFT) 
    { 
        if(mysnake[SNAKE_HEAD].x > 0) 
        { 
            mysnake[SNAKE_HEAD].x--; 
        } 
    } 
    else if(mysnake[SNAKE_HEAD].mv_state == MV_UP) 
    { 
        if(mysnake[SNAKE_HEAD].y > 0) 
        { 
            mysnake[SNAKE_HEAD].y--; 
        } 
    } 
    else if(mysnake[SNAKE_HEAD].mv_state == MV_DWN) 
    { 
        if(mysnake[SNAKE_HEAD].y < MAX_Y_SIZE_TABLE - 1) 
        { 
            mysnake[SNAKE_HEAD].y++; 
        } 
    } 
    else 
    { 

    } 
    //Body position inheritance 
    if(get_snake_tail()>0) 
    { 
        for(unsigned int i=get_snake_tail(); i>SNAKE_HEAD; i--) 
        { 
            mysnake[i].x = mysnake[i-1].x; 
            mysnake[i].y = mysnake[i-1].y; 
        } 
    } 
    
    return RET_OK; 
} 

unsigned char get_snake_tail() 
{ 
    unsigned char arr_size = (sizeof(mysnake)/3); 
    unsigned char snake_tail = arr_size - 1; 
    
    // printf("array size: %d | snake tail: %d \n", arr_size, snake_tail); 
    return snake_tail; 
} 

int clear_table(void) 
{ 
    for(u8 i=0; i<MAX_Y_SIZE_TABLE; i++) 
    { 
        for(u8 j=0; j<MAX_X_SIZE_TABLE; j++) 
        { 
            table[i][j] = TABLE_SCREEN; 
        } 
    } 
    return RET_OK; 
} 

void clear_screen() 
{ 
    // Clear the screen 
    printf("\033[H\033[J");
    // Make sure to flush stdout 
    fflush(stdout); 
} 

int kbhit(void) 
{ 
    struct termios oldt, newt; 
    int ch; 
    int oldf; 
    
    tcgetattr(STDIN_FILENO, &oldt); 
    newt = oldt; newt.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0); 
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); 
    
    ch = getchar(); 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
    fcntl(STDIN_FILENO, F_SETFL, oldf); 
    
    if(ch != EOF) 
    { 
        ungetc(ch, stdin); 
        return 1; 
    } 
    return 0; 
} 

unsigned int rand_num(int upper, int lower) 
{ 
    static unsigned long int seed = 0; 
    unsigned int gen_num; 
    if(upper > lower) 
    { 
        if (seed == 0) 
        { 
            seed = time(NULL); 
        } 
        seed = seed * 1103515245 + 12345; 
        gen_num = (unsigned int)(seed / 65536) % 32768; 
        gen_num = lower + gen_num % (upper - lower); 
    } 
    else 
    { 

    } 
    return gen_num; 
} 

int food_gen(void) 
{ 
    myfood.x = rand_num(MAX_Y_SIZE_TABLE-1, 1); 
    myfood.y = rand_num(MAX_Y_SIZE_TABLE-1, 1); 
    
    return RET_OK; 
} 

int food_display(void) 
{ 
    table[myfood.y][myfood.x] = FOOD_SYMBOL; 
    if((mysnake[SNAKE_HEAD].x == myfood.x) && 
        (mysnake[SNAKE_HEAD].y == myfood.y)) 
    { 
        //reset old food 
        table[myfood.y][myfood.x] = SNAKE_SYMBOL; 
        
        //gen new food 
        food_gen(); 
        table[myfood.y][myfood.x] = FOOD_SYMBOL; 
    } return 
    RET_OK; 
}
