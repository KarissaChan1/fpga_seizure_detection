#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include "math.h"
#include "hw_cls_core.h"

// write data to DDR
#include "params_preprocess.h"
#include "params_svm.h"


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

float read_data(volatile void* map_base, int offset)
{
  volatile void* virt_addr = (volatile void*)((char*)map_base + offset);
  return *((float *) virt_addr);
}

void start_layer(volatile void* map_base, int target, int ap_start_addr){
	write_reg(map_base, target + ap_start_addr, 0x1);
}

int poll_layer(volatile void* map_base, int target, int ap_status_addr) {
	int status = (read_reg(map_base, target+ ap_status_addr) & 0xe);
	return status;
}

//SET UP LAYERS
void setup_preprocess_layer( volatile void* map_base, int target, int input_offset, int output_offset,  int NUM_LOD, int NUM_HID, int SIZE_SIGNAL, int SIZE_D1, int SIZE_D2, int SIZE_D3, int SIZE_D4, int SIZE_D5)
{
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_INPUT_OFFSET_DATA, input_offset);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_OUTPUT_OFFSET_DATA, output_offset);
	
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_NUM_LOD_DATA, NUM_LOD);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_NUM_HID_DATA, NUM_HID);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_SIGNAL_DATA, SIZE_SIGNAL);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D1_DATA, SIZE_D1);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D2_DATA, SIZE_D2);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D3_DATA, SIZE_D3);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D4_DATA, SIZE_D4);
	  write_reg(map_base, target + preprocess_CTRL_BUS_ADDR_SIZE_D5_DATA, SIZE_D5);
}

void setup_feature_extract_layer( volatile void* map_base, int target, int input_offset, int output_offset, int SIZE_SIGNAL,  int SIZE_D3, int SIZE_D4,int SIZE_D5, int SIZE_A5 )
{
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_INPUT_OFFSET_DATA, input_offset);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_OUTPUT_OFFSET_DATA, output_offset);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_SIZE_SIGNAL_DATA, SIZE_SIGNAL);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_SIZE_D3_DATA, SIZE_D3);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_SIZE_D4_DATA, SIZE_D4);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_SIZE_D5_DATA, SIZE_D5);
	  write_reg(map_base, target + featextract_CTRL_BUS_ADDR_SIZE_A5_DATA, SIZE_A5);
}


void setup_classify_layer( volatile void* map_base, int target, int input_offset, int output_offset, int NUM_BETA,  float bias, float scale )
{
	  write_reg(map_base, target + classify_CTRL_BUS_ADDR_INPUT_OFFSET_DATA, input_offset);
	  write_reg(map_base, target + classify_CTRL_BUS_ADDR_OUTPUT_OFFSET_DATA, output_offset);
	  write_reg(map_base, target + classify_CTRL_BUS_ADDR_NUM_BETA_DATA, NUM_BETA);
	  write_reg(map_base, target + classify_CTRL_BUS_ADDR_BIAS_DATA, bias);
	  write_reg(map_base, target + classify_CTRL_BUS_ADDR_SCALE_DATA, scale);
}

void preprocess_hw(int input_offset, int output_offset, int NUM_LOD, int NUM_HID, int SIZE_SIGNAL, int SIZE_D1, int SIZE_D2, int SIZE_D3, int SIZE_D4, int SIZE_D5)
{
	setup_preprocess_layer(0x00000000, HW_preprocess_CTRL_ADDR, input_offset, output_offset, NUM_LOD, NUM_HID, SIZE_SIGNAL,SIZE_D1,SIZE_D2,SIZE_D3,SIZE_D4,SIZE_D5);
	start_layer(0x0, HW_preprocess_CTRL_ADDR, preprocess_CTRL_BUS_ADDR_AP_CTRL);
	while (poll_layer(0x0, HW_preprocess_CTRL_ADDR, preprocess_CTRL_BUS_ADDR_AP_CTRL)==0)
	{
		printf("preprocess layer processing \n");
	}
	
    printf("done preprocess layer processing \n");
	
}

void feature_extract_hw(int input_offset, int output_offset, int SIZE_SIGNAL,  int SIZE_D3, int SIZE_D4,int SIZE_D5,int SIZE_A5)
{
	setup_feature_extract_layer(0x00000000, HW_featextract_CTRL_ADDR, input_offset, output_offset, SIZE_SIGNAL, SIZE_D3, SIZE_D4, SIZE_D5, SIZE_A5);
	start_layer(0x0, HW_featextract_CTRL_ADDR, featextract_CTRL_BUS_ADDR_AP_CTRL);
	while (poll_layer(0x0, HW_featextract_CTRL_ADDR, featextract_CTRL_BUS_ADDR_AP_CTRL)==0)
	{
		printf("featextract processing \n");
	}
	
    printf("done featextract processing \n");
	
}

void classify_hw(int input_offset, int output_offset, int NUM_BETA, float bias, float scale)
{
	setup_classify_layer(0x00000000, HW_classify_CTRL_ADDR, input_offset, output_offset, NUM_BETA, bias, scale);
	start_layer(0x0, HW_classify_CTRL_ADDR, classify_CTRL_BUS_ADDR_AP_CTRL);
	while (poll_layer(0x0, HW_classify_CTRL_ADDR, classify_CTRL_BUS_ADDR_AP_CTRL)==0)
	{
		printf("classify processing \n");
	}
	
    printf("done classify processing \n");
}


void hw_hls_core_processing (int preprocess_input_offset)
{
	printf("start hls core processing \n");
	//layer 1 - preprocess
	   preprocess_hw(preprocess_input_offset, 0x91000000, 8,8,256,128,64,32,16,8);     // input offset 0x90000000 (from ADC), output offset 0x91000000
	//layer 2 -feature extraction
	feature_extract_hw(0x91000000, 0x92000000, 256, 32, 16, 8, 8);    // input (output from previous layer) offset 0x91000000 , output offset 0x92000000
	//layer 3 - classification
	   classify_hw(0x92000000, 0x93000000, 10, 2.572385, 1);     // input offset 0x92000000 , output offset 0x93000000
	
	printf("done hls core processing \n");
}


void write_to_ddr(float *ddrMemory)
{
	
	int size_signal = 256; //ADC output written to 0x90000000
	//parameters to write to DDR for pre-processing
	int num_lod = 8; 
	int num_hid = 8;
	
	//parameters to write to DDR for SVM model
	int size_beta_svm = 10;
	
		

	int i = 0;
	int i_addr = 0;
	
	
	//WRITING DATA FOR PREPROCESS LAYER INPUT
	//writing output ADC SIGNAL
	i_addr = preprocess_INPUT_OFFSET;
	for (i = 0; i < size_signal*30; i_addr++, i++)
	{
		ddrMemory[i_addr] = adc_input[i];
		//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
	}
	printf("addr: %x , data: %f \n", &ddrMemory[preprocess_INPUT_OFFSET] , ddrMemory[preprocess_INPUT_OFFSET] );
	
	//writing LoD coeffs
	for (i = 0; i < num_lod; i_addr++, i++)
	{
		ddrMemory[i_addr] = LoD[i];
		//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
	}
	printf("addr: %x , data: %f \n", &ddrMemory[preprocess_INPUT_OFFSET+size_signal*30] , ddrMemory[preprocess_INPUT_OFFSET+size_signal*30] );

//writing HiD coeffs	
	for (i = 0; i<num_lod;i_addr++, i++){
	
			ddrMemory[i_addr] = HiD[i];
			//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
		}
	printf("addr: %x , data: %f \n", &ddrMemory[preprocess_INPUT_OFFSET+size_signal*30+num_lod] , ddrMemory[preprocess_INPUT_OFFSET+size_signal*30+num_lod] );


	
	//WRITING DATA FOR CLASSIFY LAYER
	i_addr = classify_INPUT_OFFSET + 10; //svm parameters stored after feature vector
	
	//writing SVM Layer parameters (alpha,bias,labels,support vectors)
	for (i = 0; i < size_beta_svm; i_addr++, i++)
	{
		ddrMemory[i_addr] = svm_beta[i];
		//printf("addr: %x , data: %f \n", &ddrMemory[i_addr] , ddrMemory[i_addr] );
	}
	printf("addr: %x , data: %f \n", &ddrMemory[classify_INPUT_OFFSET+size_beta_svm] , ddrMemory[classify_INPUT_OFFSET+size_beta_svm] );

	
}

volatile unsigned int * LED = (unsigned int *)0x40000000;
volatile unsigned int * DDRbase = (unsigned int *)0x90000000;

int main(){
	
	init_platform();
    print("Hello World\n\r");
    * DDRbase = 3;
    * LED = *DDRbase;
    write_to_ddr(DDRbase);
    float class_in[10];
    float class_out[3];

    /*for (int i = 0; i<30;i++){
		
		hw_hls_core_processing(0x90000000 + i*256*4);
		for (int i = 0; i<3;i++){
			class_out[i] = read_data(0x00000000,0x93000000+i*4);
					printf("classify outputs: %f\n",class_out[i]);
		}

	}*/

   hw_hls_core_processing(0x90000000);

   float filtered[256];
       for (int i = 0; i<256;i++){
       	filtered[i] = read_data(0x00000000,0x91000000 + i*4);
       	printf("filtered: %f\n", filtered[i]);
       }
       float d3[32];
           for (int i = 0; i<32;i++){
           	d3[i] = read_data(0x00000000,0x91000000 + (256+i)*4);
           	printf("d3: %f\n", d3[i]);

           }
   		 float d4[16];
           for (int i = 0; i<16;i++){
           	d4[i] = read_data(0x00000000,0x91000000 + (256+32+i)*4);
           	printf("d4: %f\n", d4[i]);

           }
           float a5[8];
               for (int i = 0; i<8;i++){
               	a5[i] = read_data(0x00000000,0x91000000 + (256+32+16+i)*4);
               	printf("a5: %f\n", a5[i]);

               }
               float d5[8];
                   for (int i = 0; i<8;i++){
                   	d5[i] = read_data(0x00000000,0x91000000 + (256+32+16+8+i)*4);
                   	printf("d5: %f\n", d5[i]);

                   }


   for (int i = 0; i<20;i++){
   			class_in[i] = read_data(0x00000000,0x92000000+i*4);
   					printf("classify inputs: %f\n",class_in[i]);
   		}
	
	
   for (int i = 0; i<3;i++){
   			class_out[i] = read_data(0x00000000,0x93000000+i*4);
   					printf("classify outputs: %f\n",class_out[i]);
   		}

	
   
   cleanup_platform();
   return 0; 
	
	
	
	
}