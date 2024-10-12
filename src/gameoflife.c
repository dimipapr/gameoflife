#include <stdio.h>
#include <stdlib.h>

#define WORLD_WIDTH     50
#define WORLD_HEIGHT    10

#define CELL_ALIVE      'o'
#define CELL_DEAD       '-'


void print_world(char **world);
char **init_world(void);

int main(void){
    
    char **world;
    world = init_world();
    world[7][3]=1;
    world[7][4]=1;
    world[7][5]=1;

    print_world(world);
    return 0;
}

void print_world(char **world)
{
    int x,y;

    for (y=0;y<WORLD_HEIGHT;y++){
        for(x=0;x<WORLD_WIDTH;x++){
            (world[x][y])?putchar(CELL_ALIVE):putchar(CELL_DEAD);
        }
        putchar('\n');
    }
}

char **init_world(void){
    char **p;
    p = (char **)malloc(WORLD_WIDTH*sizeof(char *));
    if (p==NULL){
        puts("Allocation error");
        exit(1);
    }
    for (int x=0;x<WORLD_WIDTH;x++){
        p[x] = (char*)malloc(WORLD_HEIGHT*sizeof(char));
        if (p[x]==NULL){
            puts("Allocation error");
            exit(1);
        } 
    }
    return p;
}