#include <stdio.h>
#include <stdlib.h>

#define WORLD_WIDTH     50
#define WORLD_HEIGHT    10

#define CELL_ALIVE      'o'
#define CELL_DEAD       '-'


void print_world(char world[WORLD_WIDTH][WORLD_HEIGHT]);
void init_world(char world[WORLD_WIDTH][WORLD_HEIGHT]);

int main(void){
    
    char world[50][10];
    init_world(world);
    world[7][3]=1;
    world[7][4]=1;
    world[7][5]=1;

    print_world(world);
    return 0;
}

void print_world(char world[WORLD_WIDTH][WORLD_HEIGHT])
{
    int x,y;

    for (y=0;y<WORLD_HEIGHT;y++){
        for(x=0;x<WORLD_WIDTH;x++){
            (world[x][y])?putchar(CELL_ALIVE):putchar(CELL_DEAD);
        }
        putchar('\n');
    }
}

void init_world(char world[WORLD_WIDTH][WORLD_HEIGHT]){
    int x,y;
    for (y=0;y<WORLD_HEIGHT;y++){
        for(x=0;x<WORLD_WIDTH;x++){
            world[x][y]=0;
        }
    }
}