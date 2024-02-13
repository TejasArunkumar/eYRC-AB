#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {

    #define START_POINT         (* (volatile uint8_t * ) 0x02000000)
    #define END_POINT           (* (volatile uint8_t * ) 0x02000004)
    #define NODE_POINT          (* (volatile uint8_t * ) 0x02000008)
    #define CPU_DONE            (* (volatile uint8_t * ) 0x0200000c)
    #define NEXT_DIRECTION      (* (volatile uint8_t * ) 0x02000010)    // 0: Straight, 1: Right, 2: left, 3: back 
    #define NODE_REACHED        (* (volatile uint8_t * ) 0x02000014)   
    while(NODE_REACHED == 1){
    NEXT_DIRECTION =  rand() % 4;
    NODE_REACHED = 0;
    if(rand() % 10 == 1){
        break;
    }
    }
    CPU_DONE = 1;
    return 0;
}
