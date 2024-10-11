#include <stdio.h>
#include <stdlib.h>

#define WORLD_HEIGHT    20
#define WORLD_WIDTH     60

//RULES
//alive cells with 2 or 3 alive neighbors stay alive
//alive cells with <2 or >3 alive neighbors dies
//dead cell with =3 alive neighbors gets reborn

void clean_up(void);

char **world_current_gen, **world_next_gen;


int main(void)
{
    //initialize world
    world_current_gen = (char**)malloc(WORLD_WIDTH*sizeof(char));
    world_next_gen = (char**)malloc(WORLD_WIDTH*sizeof(char));
    if (world_current_gen == NULL || world_next_gen == NULL){
        clean_up();
        exit(1);
    }
    
    for (int i=0;i<WORLD_WIDTH;i++){
        world_current_gen[i] = (char*)malloc(WORLD_HEIGHT*sizeof(char));
        world_next_gen[i] = (char*)malloc(WORLD_HEIGHT*sizeof(char));
        if (world_current_gen[i] == NULL || world_next_gen[i] == NULL){
            clean_up();
            exit(1);
        }
    }    
    //iterate through cells
    //calculate alive neighbors
    //get next gen value

    clean_up();
    return 0;
}

void clean_up(void){
    for (int i=0;i<WORLD_WIDTH;i++){
        free(world_current_gen[i]);
        free(world_next_gen[i]);
    }
    free(world_current_gen);
    free(world_next_gen);
}