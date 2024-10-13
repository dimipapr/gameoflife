#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WORLD_WIDTH     50
#define WORLD_HEIGHT    10

#define CELL_ALIVE      'o'
#define CELL_DEAD       '-'


void print_world(char **world);
char **init_world(void);
void wait_for(unsigned int seconds);

int main(void){
    
    char **world;
    char **neighbor_count;

    world = init_world();
    neighbor_count = init_world();

    //crawler
    world[2][1]=1;
    world[2][3]=1;
    world[3][2]=1;
    world[3][3]=1;
    world[4][2]=1;

    // world[2][1]=1;
    // world[2][2]=1;
    // world[2][3]=1;
    
    print_world(world);
    putc('\n',stdout);
    // printf("(1+10)%%10=%d\n",(1+10)%10);
    // printf("(-1+10)%%10=%d\n",(-1+10)%10);
    while(1){
        //game loop

        //loop through internal cells
        for(int x=0;x<WORLD_WIDTH;x++)
        {
            for (int y=0;y<WORLD_HEIGHT;y++)
            {
                //get neighbor count
                switch (world[x][y])
                {
                case 1://alive
                    //vote to neighbors
                    int x_minus, x_pluss, y_minus, y_pluss;
                    x_minus = (x-1+WORLD_WIDTH)%WORLD_WIDTH;
                    x_pluss = (x+1)%WORLD_WIDTH;
                    y_minus = (y-1+WORLD_HEIGHT)%WORLD_HEIGHT;
                    y_pluss = (y+1)%WORLD_HEIGHT;


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
        
        //decide for each cell
        for (int y=0;y<WORLD_HEIGHT;y++){
            for(int x=0;x<WORLD_WIDTH;x++){
                if(world[x][y]==1){
                    //alive_cell case
                    if( !(neighbor_count[x][y]==2 || neighbor_count[x][y]==3) )
                        world[x][y]=0;

                }else{
                    //dead cell
                    if(neighbor_count[x][y] == 3)
                        world[x][y]=1;
                }
            }
        }
        //print world
        print_world(world);
        //reinitialize neighbor count
        for (int y=0;y<WORLD_HEIGHT;y++){
            for(int x=0;x<WORLD_WIDTH;x++){
                neighbor_count[x][y]=0;
            }
        }
        wait_for(1);
        
        puts("\n");
    }
    return 0;
}

void print_world(char **world)
{
    int x,y;
    //system("clear");
    for (y=0;y<WORLD_HEIGHT;y++){
        for(x=0;x<WORLD_WIDTH;x++){
            (world[x][y]==1)?putchar(CELL_ALIVE):putchar(CELL_DEAD);
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
void wait_for(unsigned int seconds)
{
    long int retTime = time(0) + seconds;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}