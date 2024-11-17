#pragma GCC diagnostic ignored "-Wunused-result"

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "config.h"

void print_world(unsigned char **world,size_t height, size_t width);
unsigned char **init_world(size_t height, size_t width);
void wait_for(unsigned int seconds);
void world_randomize(unsigned char width, unsigned char height,unsigned char **world);
unsigned short rand_bool(void);
void get_neighbor_count(unsigned char **world, unsigned char **neighbor_count,size_t height, size_t width);
void get_next_gen(unsigned char **out_world, unsigned char **neighbor_count, size_t height, size_t width);
void game_loop(unsigned char **world, unsigned char **neighbor_count);


int main(void){
    
    unsigned char **world;
    unsigned char **neighbor_count;
    srand((unsigned int)time(0));

    world = init_world(WORLD_HEIGHT, WORLD_WIDTH);
    neighbor_count = init_world(WORLD_HEIGHT, WORLD_WIDTH);
    world_randomize(WORLD_WIDTH, WORLD_HEIGHT,world);
    
    print_world(world, WORLD_HEIGHT, WORLD_WIDTH);
    putc('\n',stdout);
    usleep(1000*1000);

    while(1){
        //game loop
        game_loop(world,neighbor_count);

        
        
        // puts("\n");
    }
    return 0;
}

void game_loop(unsigned char **world, unsigned char **neighbor_count){
    get_neighbor_count(world,neighbor_count,WORLD_HEIGHT,WORLD_WIDTH);
        get_next_gen(world,neighbor_count,WORLD_HEIGHT,WORLD_WIDTH);
        print_world(world, WORLD_HEIGHT, WORLD_WIDTH);
        //reinitialize neighbor count
        for (int y=0;y<WORLD_HEIGHT;y++){
            for(int x=0;x<WORLD_WIDTH;x++){
                neighbor_count[x][y]=0;
            }
        }
        //wait_for(1);
        usleep(LOOP_DELAY_MS*1000);
}

void get_next_gen(unsigned char **out_world, unsigned char **neighbor_count, size_t height, size_t width)
{
    for (size_t y=0;y<height;y++){
        for(size_t x=0;x<width;x++){
            if(out_world[x][y]==1){
                //alive_cell case
                if( !(neighbor_count[x][y]==2 || neighbor_count[x][y]==3) )
                    out_world[x][y]=0;

            }else{
                //dead cell
                if(neighbor_count[x][y] == 3)
                    out_world[x][y]=1;
            }
        }
    }
}

void get_neighbor_count(
    unsigned char **world,
    unsigned char **neighbor_count,
    size_t height,
    size_t width)
{
    for(size_t x=0;x<width;x++)
        {
            for (size_t y=0;y<height;y++)
            {
                //get neighbor count
                switch (world[x][y])
                {
                case 1://alive
                    //vote to neighbors
                    size_t x_minus, x_pluss, y_minus, y_pluss;
                    x_minus = (x-1+width)%width;
                    x_pluss = (x+1)%width;
                    y_minus = (y-1+height)%height;
                    y_pluss = (y+1)%height;


                    neighbor_count[x_minus][y_minus]+=1;
                    neighbor_count[x][y_minus]+=1;
                    neighbor_count[x_pluss][y_minus]+=1;
                    neighbor_count[x_minus][y]+=1;
                    neighbor_count[x_pluss][y]+=1;
                    neighbor_count[x_minus][y_pluss]+=1;
                    neighbor_count[x][y_pluss]+=1;
                    neighbor_count[x_pluss][y_pluss]+=1;
                    break;
                
                default:
                    break;
                }
            }
        }
}

void print_world(unsigned char **world, size_t height, size_t width)
{
    size_t x,y;
    system("clear");
    for (y=0;y<height;y++){
        for(x=0;x<width;x++){
            (world[x][y]==1)?putchar(CELL_ALIVE):putchar(CELL_DEAD);
        }
        putchar('\n');
    }
}

unsigned char **init_world(size_t height, size_t width){
    unsigned char **p;
    p = (unsigned char **)malloc(width*sizeof(unsigned char *));
    if (p==NULL){
        puts("Allocation error");
        exit(1);
    }
    for (size_t x=0;x<width;x++){
        p[x] = (unsigned char*)malloc(height*sizeof(unsigned char));
        if (p[x]==NULL){
            puts("Allocation error");
            exit(1);
        } 
    }
    return p;
}
void wait_for(unsigned int seconds)
{
    long int retTime = time(0) + seconds;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
void world_randomize(unsigned char width, unsigned char height, unsigned char **world){
    for (size_t x = 0; x < width; x++)
    {
        for (size_t y = 0; y < height; y++)
        {
            world[x][y] = (unsigned char)rand_bool();
        }
        
    }
    
}

unsigned short rand_bool(void){
    if(rand()<RAND_MAX/2)return 0;else return 1;
}