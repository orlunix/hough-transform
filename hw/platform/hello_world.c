/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */
#include <stdio.h>
#include "sdram_master.h"
#include "system.h"
#include "io.h"

int main()
{
    unsigned char i,j;
    int temp;
    for(i=0;i<100;i++)
        IOWR_8DIRECT(SDRAM_U1_BASE,i,i);
    
    IOWR(SDRAM_MASTER_INST_BASE,S_ADDR,SDRAM_U1_BASE);
    IOWR(SDRAM_MASTER_INST_BASE,D_ADDR,SDRAM_U2_BASE);
    IOWR(SDRAM_MASTER_INST_BASE,LONGTH,100);
    IOWR(SDRAM_MASTER_INST_BASE,START_ADDR,1);
    
    temp=IORD(SDRAM_MASTER_INST_BASE,S_ADDR);
    printf("S_ADDR:w,r==%d,%d\n",SDRAM_U1_BASE,temp);
    temp=IORD(SDRAM_MASTER_INST_BASE,D_ADDR);
    printf("D_ADDR:w,r==%d,%d\n",SDRAM_U2_BASE,temp);    
    temp=IORD(SDRAM_MASTER_INST_BASE,LONGTH);
    printf("LONGTH:w,r==%d,%d\n",100,temp);    
    
    while(IORD(SDRAM_MASTER_INST_BASE,STATUS_ADDR)!=1){
    printf("waiting...!\n");
    //break;
    };
    
    for(i=0;i<100;i++){
        j=IORD_8DIRECT(SDRAM_U1_BASE,i);
        printf("SDRAM_U1:i,j == %d, %d\n",i,j);
    }
    for(i=0;i<100;i++){
        j=IORD_8DIRECT(SDRAM_U2_BASE,i);
        printf("SDRAM_U2:i,j == %d, %d\n",i,j);
    }    
        
    
  printf("Hello from Nios II!\n");

  return 0;
}
