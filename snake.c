#include "snake.h" 

char table[MAX_Y_SIZE_TABLE][MAX_X_SIZE_TABLE] = {0}; 
// snake_st mysnake[SNAKE_INIT_SIZE] = {0};
snake_st *mysnake = NULL;
food_st myfood; 

int main(int agrc, char *agrv[]) 
{
    // Register the SIGINT signal handler
    signal(SIGINT, sigint_handler);

    mysnake = (snake_st *)malloc(SNAKE_INIT_SIZE * sizeof(snake_st));
    snake_size = SNAKE_INIT_SIZE;

    init_play_table(); 
    print_play_table(); 
    while(1) 
    { 
        snake_display(); 
        food_display(); 
        // Print the table with the updated snake and food position 
        print_play_table(); 
        usleep(REFRESH_RATE); 
    } 
    return RET_OK; 
} 

/*----------- Function Initalization -----------*/ 

int init_play_table() 
{
    //play table array init   
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

int print_play_table(void) 
{
    // clear screen table and print new screen table
    clear_screen(); 
    for(u8 i=0; i<MAX_Y_SIZE_TABLE; i++) 
    { 
        for(u8 j=0; j<MAX_X_SIZE_TABLE; j++) 
        { 
            printf("%c", table[i][j]); 
        } printf("\n"); 
    } 
    
    //print player info
    player_info();

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
    unsigned char snake_tail = snake_size - 1;
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
    //eat food
    if((mysnake[SNAKE_HEAD].x == myfood.x) && 
        (mysnake[SNAKE_HEAD].y == myfood.y)) 
    {
        //increase point
        user_point++;

        //snake grow up
        snake_grow();

        //reset old food 
        table[myfood.y][myfood.x] = SNAKE_SYMBOL; 
        
        //gen new food 
        food_gen(); 
        table[myfood.y][myfood.x] = FOOD_SYMBOL; 
    } 
    
    return RET_OK; 
}

int player_info()
{
    printf("Welcome player: N/A\n");
    // printf("Snake tail: %d\n", get_snake_tail());
    printf("Snake size: %d\n", get_snake_tail());
    printf("Your score is: %d\n", user_point);
    return RET_OK;
}

int snake_grow(void)
{
    snake_size++;
    snake_st *new_mysnake = (snake_st *)malloc((snake_size) * sizeof(snake_st));

    // Copy the old array to the new array
    memcpy(new_mysnake, mysnake, (snake_size - 1) * sizeof(snake_st));

    // Free the old array
    free(mysnake);

    // Update the pointer to point to the new array
    mysnake = new_mysnake;

    return RET_OK;
}

void sigint_handler(int sig) 
{
    printf("Caught SIGINT: %d\n", sig);
    printf("Clear resource\n");
    free(mysnake);
    printf("Exit game...\n");
    exit(0);
}