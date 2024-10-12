#include <stdio.h>
#include <stdlib.h>

#define WORLD_HEIGHT    7
#define WORLD_WIDTH     50

#define ALIVE_CELL      'o'
#define DEAD_CELL       '-'

//RULES
//alive cells with 2 or 3 alive neighbors stay alive
//alive cells with <2 or >3 alive neighbors dies
//dead cell with =3 alive neighbors gets reborn

void print_world(char world[WORLD_HEIGHT][WORLD_WIDTH]);
void clean_up(void);

char world_current_gen[WORLD_HEIGHT][WORLD_WIDTH];
char world_next_gen[WORLD_HEIGHT][WORLD_WIDTH];


int main(void)
{
    //initialize world
    // world_current_gen = (char**)malloc(WORLD_WIDTH*sizeof(char));
    // world_next_gen = (char**)malloc(WORLD_WIDTH*sizeof(char));
    // if (world_current_gen == NULL || world_next_gen == NULL){
    //     clean_up();
    //     exit(1);
    // }
    
    // for (int x=0;x<WORLD_WIDTH;x++){
    //     world_current_gen[x] = (char*)malloc(WORLD_HEIGHT*sizeof(char));
    //     world_next_gen[x] = (char*)malloc(WORLD_HEIGHT*sizeof(char));
    //     if (world_current_gen[x] == NULL || world_next_gen[x] == NULL){
    //         clean_up();
    //         exit(1);
    //     }
    // }

    for (int x=0;x<WORLD_WIDTH;x++){
        for(int y=0;y<WORLD_HEIGHT;y++){
            world_current_gen[x][y]=0;
        }
    }    
    world_current_gen[3][3] = 1;
    world_current_gen[3][4] = 1;
    world_current_gen[3][5] = 1;
    print_world(world_current_gen);
    //iterate through cells
    //calculate alive neighbors
    //get next gen value

    clean_up();
    return 0;
}

void clean_up(void){
    // for (int i=0;i<WORLD_WIDTH;i++){
    //     free(*(world_current_gen+i));
    //     free(*(world_next_gen+i));
    // }
    // free(world_current_gen);
    // free(world_next_gen);
}

void print_world(char world[WORLD_HEIGHT][WORLD_WIDTH]){
    for(int y=0;y<WORLD_HEIGHT;y++){
        for(int x=0;x<WORLD_WIDTH;x++){
            (world[y][x])?putchar(ALIVE_CELL):putchar(DEAD_CELL);
        }
        putchar('\n');
    }
}