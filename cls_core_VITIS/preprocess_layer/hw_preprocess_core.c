#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "hw_preprocess_core.h"


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

void setup_preprocess_layer( volatile void* map_base, int target, int input_offset, int output_offset, int NUM_COEFFS, int NUM_LOD, int NUM_HID, int SIZE_SIGNAL, int SIZE_D1, int SIZE_D2, int SIZE_D3, int SIZE_D4, int SIZE_D5)
{
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_INPUT_OFFSET_DATA, input_offset);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_OUTPUT_OFFSET_DATA, output_offset);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_NUM_COEFFS_DATA, NUM_COEFFS);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_NUM_LOD_DATA, NUM_LOD);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_NUM_HID_DATA, NUM_HID);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_SIGNAL_DATA, SIZE_SIGNAL);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D1_DATA, SIZE_D1);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D2_DATA, SIZE_D2);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D3_DATA, SIZE_D3);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D4_DATA, SIZE_D4);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D5_DATA, SIZE_D5);
}

preprocess_hw(int input_offset, int output_offset, int NUM_COEFFS, int NUM_LOD, int NUM_HID, int SIZE_SIGNAL, int SIZE_D1, int SIZE_D2, int SIZE_D3, int SIZE_D4, int SIZE_D5)
{
	setup_preprocess_layer(0x00000000, HW_preprocess_CTRL_ADDR, input_offset, output_offset, NUM_COEFFS, NUM_LOD, NUM_HID, SIZE_SIGNAL,SIZE_D1,SIZE_D2,SIZE_D3,SIZE_D4,SIZE_D5);
	start_layer(0x0, HW_preprocess_CTRL_ADDR, preprocess_CTRL_BUS_ADDR_AP_CTRL);
	while (poll_layer(0x0, HW_preprocess_CTRL_ADDR, preprocess_CTRL_BUS_ADDR_AP_CTRL)==0)
	{
		printf("featextract processing \n");
	}
	
    printf("done featextract processing \n");
	
}



void write_to_ddr(float *ddrMemory)
{
	int size_signal = 256;
	int num_coeffs = 501;
	int num_lod = 8; //same for num_hid
	

	int i = 0;
	int i_addr = 0;
	
	
	//writing output ADC SIGNAL
	i_addr = preprocess_INPUT_OFFSET;
	for (i = 0; i < size_signal; i_addr++, i++)
	{
		ddrMemory[i_addr] = adc_input[i];
		//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
	}
	printf("addr: %x , data: %f \n", &ddrMemory[preprocess_INPUT_OFFSET] , ddrMemory[preprocess_INPUT_OFFSET] );
	
	
	
	//writing FIR coeffs
	for (i = 0; i < num_coeffs; i_addr++, i++)
	{
		ddrMemory[i_addr] = fir_coeffs[i];
		//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
	}
	printf("addr: %x , data: %f \n", &ddrMemory[preprocess_INPUT_OFFSET+size_signal] , ddrMemory[preprocess_INPUT_OFFSET+size_signal] );

//writing LoD coeffs
	for (i = 0; i < num_lod; i_addr++, i++)
	{
		ddrMemory[i_addr] = LoD[i];
		//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
	}
	printf("addr: %x , data: %f \n", &ddrMemory[preprocess_INPUT_OFFSET+size_signal+num_coeffs] , ddrMemory[preprocess_INPUT_OFFSET+size_signal+num_coeffs] );

//writing HiD coeffs	
	for (i = 0; i<num_lod;i_addr++, i++){
	
			ddrMemory[i_addr] = HiD[i];
			//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
		}
	printf("addr: %x , data: %f \n", &ddrMemory[preprocess_INPUT_OFFSET+size_signal+num_coeffs +num_lod] , ddrMemory[preprocess_INPUT_OFFSET+size_signal+num_coeffs+num_lod] );
	
	//read output
	printf("addr: %x , data: %f \n", &ddrMemory[preprocess_OUTPUT_OFFSET] , ddrMemory[preprocess_OUTPUT_OFFSET] );
}
float read_data(volatile void* map_base, int offset)
{
  volatile void* virt_addr = (volatile void*)((char*)map_base + offset);
  return *((float *) virt_addr);
}

int main()
{
	init_platform();
    print("Hello World\n\r");
    * DDRbase = 3;
    * LED = *DDRbase;
    write_to_ddr(DDRbase);
    
    
	preprocess_hw(0x90000000, 0x91000000, 501,8,8,256,128,64,32,16,8);
	float filtered[256];
	for (int i = 0; i<256; i++){
		filtered[i] = read_data(0x00000000,0x91000000 + i*4);
		printf("filtered: %f\n",filtered[i]);
	}
	float a1[128];
	    	    	for (int i =0; i<128;i++){
	    	    		a1[i] = read_data(0x00000000,0x91000000 + 256*4+i*4);
	    	    		printf("a1 outputs: %f\n",a1[i]);
	    	    	}

	    	    	float a2[64];
	    	    	    	for (int i =0; i<64;i++){
	    	    	    		a2[i] = read_data(0x00000000,0x91000000 +256*4+128*4+ i*4);
	    	    	    		printf("a2 outputs: %f\n",a2[i]);
	    	    	    	}

	    	  float a3[32];
	    	   	for (int i =0; i<32;i++){
	    	   		a3[i] = read_data(0x00000000,0x91000000 +256*4+128*4+64*4 +i*4);
	    	      		printf("a3 outputs: %f\n",a3[i]);
	    	   }


	    	   	float d3[32];
	    	   	    	   	for (int i =0; i<32;i++){
	    	   	    	   	d3[i] = read_data(0x00000000,0x91000000 +256*4+128*4+64*4 +32*4+i*4);
	    	   	    	      		printf("d3 outputs: %f\n",d3[i]);
	    	   	    	   }

	
   
   cleanup_platform();
   return 0; 
}
