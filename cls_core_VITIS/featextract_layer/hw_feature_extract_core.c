#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "hw_feature_extract_core.h"


volatile unsigned int * LED = (unsigned int *)0x40000000;
volatile unsigned int * DDRbase = (unsigned int *)0x90000000;


void write_reg(volatile void* map_base, int offset, int value)
{
  volatile void* virt_addr = (volatile void*)((char*)map_base + offset);
  *((uint32_t *) virt_addr) = value;
}

int read_reg(volatile void* map_base, int offset)
{
  volatile void* virt_addr = (volatile void*)((char*)map_base + offset); 
  return *((uint32_t *) virt_addr);
}

void start_layer(volatile void* map_base, int target, int ap_start_addr){
	write_reg(map_base, target + ap_start_addr, 0x1);
}

int poll_layer(volatile void* map_base, int target, int ap_status_addr) {
	int status = (read_reg(map_base, target+ ap_status_addr) & 0xe);
	return status;
}

void setup_feature_extract_layer( volatile void* map_base, int target, int input_offset, int output_offset, int SIZE_SIGNAL,  int SIZE_D3, int SIZE_D5, int SIZE_A5 )
{
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_INPUT_OFFSET_DATA, input_offset);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_OUTPUT_OFFSET_DATA, output_offset);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_SIZE_SIGNAL_DATA, SIZE_SIGNAL);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_SIZE_D3_DATA, SIZE_D3);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_SIZE_D5_DATA, SIZE_D5);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_SIZE_A5_DATA, SIZE_A5);
}

feature_extract_hw(int input_offset, int output_offset, int SIZE_SIGNAL,  int SIZE_D3, int SIZE_D5,int SIZE_A5)
{
	setup_feature_extract_layer_layer(0x00000000, HW_featextract_CTRL_ADDR, input_offset, output_offset, SIZE_SIGNAL, SIZE_D3, SIZE_D5, SIZE_A5);
	start_layer(0x0, HW_featextract_CTRL_ADDR, featextract_CTRL_BUS_ADDR_AP_CTRL);
	while (poll_layer(0x0, HW_featextract_CTRL_ADDR, featextract_CTRL_BUS_ADDR_AP_CTRL)==0)
	{
		printf("featextract processing \n");
	}
	
    printf("done featextract processing \n");
	
}



void write_to_ddr(float *ddrMemory)
{
	int size_signal = 256;
	int size_d3 = 32;
	int size_d5 = 8;

	int i = 0;
	int i_addr = 0;
	
	
	//writing output from previous layers (ADC SIGNAL)
	i_addr = FEATEXTRACT_INPUT_OFFSET;
	for (i = 0; i < size_signal; i_addr++, i++)
	{
		ddrMemory[i_addr] = adc_input[i];
		//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
	}
	printf("addr: %x , data: %f \n", &ddrMemory[FEATEXTRACT_INPUT_OFFSET] , ddrMemory[FEATEXTRACT_INPUT_OFFSET] );
	
	
	
	//writing D3 coeffs
	for (i = 0; i < size_d3; i_addr++, i++)
	{
		ddrMemory[i_addr] = d3_coeffs[i];
		//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
	}
	printf("addr: %x , data: %f \n", &ddrMemory[FEATEXTRACT_INPUT_OFFSET+size_signal] , ddrMemory[FEATEXTRACT_INPUT_OFFSET+size_signal] );

//writing D5 coeffs
	for (i = 0; i < size_d5; i_addr++, i++)
	{
		ddrMemory[i_addr] = d5_coeffs[i];
		//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
	}
	printf("addr: %x , data: %f \n", &ddrMemory[FEATEXTRACT_INPUT_OFFSET+size_signal+size_d3] , ddrMemory[FEATEXTRACT_INPUT_OFFSET+size_signal+size_d3] );

//writing A5 coeffs	
	for (i = 0; i<size_d5;i_addr++, i++){
	
			ddrMemory[i_addr] = a5_coeffs[i];
			//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
		}
	printf("addr: %x , data: %f \n", &ddrMemory[FEATEXTRACT_INPUT_OFFSET+size_signal+size_d3 +size_d5] , ddrMemory[FEATEXTRACT_INPUT_OFFSET+size_signal+size_d3+size_d5] );
	
	//read output
	printf("addr: %x , data: %f \n", &ddrMemory[FEATEXTRACT_OUTPUT_OFFSET] , ddrMemory[FEATEXTRACT_OUTPUT_OFFSET] );
}


int main()
{
	init_platform();
    print("Hello World\n\r");
    * DDRbase = 3;
    * LED = *DDRbase;
    write_to_ddr(DDRbase);
    
    
	feature_extract_hw(0x91000000, 0x92000000, 256, 32, 8, 8);
	
	
	
   
   cleanup_platform();
   return 0; 
}
