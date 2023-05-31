#include <cmath>
#include <iostream>
#include <fstream>
#include "preprocess.h"

using namespace std;



void preprocess(float *mem, int input_offset, int output_offset, int NUM_LOD, int NUM_HID, int SIZE_SIGNAL, int SIZE_D1, int SIZE_D2, int SIZE_D3, int SIZE_D4, int SIZE_D5) {
#pragma HLS INTERFACE m_axi port=mem depth=200000
#pragma HLS INTERFACE s_axilite port=input_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=output_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=NUM_LOD bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=NUM_HID bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_SIGNAL bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_D1 bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_D2 bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_D3 bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_D4 bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_D5 bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS




//Normalize signal
	float range;
	float x_std[256];
	float x_norm[256];
	float scalemin = -1;
	float scalemax = 1;

    // ADC signal
	float max = mem[input_offset / sizeof(float)];
	for (int i = 0; i < SIZE_SIGNAL; i++) {
		if (mem[input_offset / sizeof(float)+ i] > max) {
			max = mem[input_offset / sizeof(float) + i];
		}
	}

	float min = mem[input_offset / sizeof(float)];
	for (int i = 0; i < SIZE_SIGNAL; i++) {
		if (mem[input_offset / sizeof(float) + i] < min) {
			min = mem[input_offset / sizeof(float) + i];
		}
	}


	range = max - min;

	for (int i = 0; i < SIZE_SIGNAL; i++) {
		x_std[i] = ((mem[input_offset / sizeof(float) + i] - min) / range);
		x_norm[i] = (x_std[i] * (scalemax - scalemin) + (scalemin));
        //cout << x_norm[i] << " ";
		mem[output_offset/sizeof(float) + i] = x_norm[i];
        cout << mem[output_offset / sizeof(float) + i] << " ";
	}

 


    //---------------------------LEVEL 1 DWT------------------------------------
//discrete wavelet transforms - DWT1
  //convfft with LoD
    int t = 0;

	float conv1[256] = {0};


    for (t = 0; t <SIZE_SIGNAL ; t++) {


        for (int k = 0; k < NUM_LOD; k++) {
        if (t - k < 0) {
            break;
        }
        conv1[t] += x_norm[t-k] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + k];

        }

    }
      
  // Downsampling by 2 gives cA
	float cA1[128] = {0};
    for (int i = 0; i < SIZE_D1; i++) {
        cA1[i] = conv1[i * 2];
        cout << "A1 " << cA1[i] << endl;
        
    }


    //conv with HiD
    float conv1_hi[256]= {0};


    for (t = 0; t < SIZE_SIGNAL; t++) {


        for (int k = 0; k < NUM_LOD; k++) {
            if (t - k < 0) {
                break;
            }
            conv1_hi[t] += x_norm[t - k] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + NUM_LOD + k];

        }

    }

    // Downsampling by 2 gives cD
    //ofstream myfile("D1.txt");
    float cD1[128] = { 0 };
    for (int i = 0; i < SIZE_D1; i++) {
        cD1[i] = conv1_hi[i * 2];
        //myfile << cD1[i] << "\n";
    }
   // myfile.close();
  
    
    //---------------------------LEVEL 2 DWT------------------------------------

//discrete wavelet transforms - DWT2
  //convfft with LoD

	float conv2[128]= {0};
    for (t = 0; t <SIZE_D1; t++) {


        for (int k = 0; k < NUM_LOD; k++) {
        if (t - k < 0) {
            break;
        }
        conv2[t] += cA1[t - k] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + k];

    }

    }
   
  // Downsampling by 2 gives cA
	float cA2[64]= {0};
    for (int i = 0; i < SIZE_D2; i++) {
    	cA2[i] = conv2[i * 2];

        cout << "A2 " << cA2[i] << endl;
        //mem[output_offset/sizeof(float) + SIZE_SIGNAL+SIZE_D1 + i] = cA2[i];
        //cout << "A2 " << mem[output_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D1+ i] << endl;

    }
   

    //---------------------------LEVEL 3 DWT------------------------------------
//discrete wavelet transforms - DWT3
  //convfft with LoD

	float conv3_lo[64]= {0};
    for (t = 0; t < SIZE_D2; t++) {


        for (int k = 0; k < NUM_LOD; k++) {
        if (t - k < 0) {
            break;
        }
        conv3_lo[t] += cA2[t - k] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + k];

    }

    }
  
  // Downsampling by 2 gives cA
	float cA3[32]= {0};
    for (int i = 0; i < SIZE_D3; i++) {
    	cA3[i] = conv3_lo[i * 2];

        
    }
  
//convfft with HiD

    float conv3_hi[64]= {0};
    for (t = 0; t <SIZE_D2; t++) {
        for (int k = 0; k < NUM_HID; k++) {
        if (t - k < 0) {
            break;
        }
        conv3_hi[t] += cA2[t - k] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + NUM_LOD + k];

    }

    }
	
     // Downsampling by 2 gives cD
	float cD3[32]= {0};
    for (int i = 0; i < SIZE_D3; i++) {
    	cD3[i]  = conv3_hi[i * 2];

        cout << "D3 " << cD3[i] << endl;
		mem[output_offset/sizeof(float) + SIZE_SIGNAL+i] = cD3[i]; //CD3 COEFFICIENTS OUTPUT AFTER FILTERED SIGNAL
        //cout << "D3 " << mem[output_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D1 + SIZE_D2 +SIZE_D3+ i] << endl;
		
    }
 

    //---------------------------LEVEL 4 DWT------------------------------------
//discrete wavelet transforms - DWT4
  //convfft with LoD

	float conv4_lo[32]= {0};
    for (t = 0; t <SIZE_D3; t++) {


    for (int k = 0; k < NUM_LOD; k++) {
        if (t - k < 0) {
            break;
        }
        conv4_lo[t] += cA3[t - k] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + k];

    }

    }
 
  // Downsampling by 2 gives cA
	float cA4[16]= {0};
    for (int i = 0; i < SIZE_D4; i++) {
    	cA4[i] = conv4_lo[i * 2];

    }


//convfft with HiD

    float conv4_hi[32]= {0};
    for (t = 0; t <SIZE_D3; t++) {
        for (int k = 0; k < NUM_HID; k++) {
        if (t - k < 0) {
            break;
        }
        conv4_hi[t]  += cA3[t - k] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + NUM_LOD + k];

    }
  ;
    }
	
     // Downsampling by 2 gives cD
	float cD4[16]= {0};
    for (int i = 0; i < SIZE_D4; i++) {
    	cD4[i] = conv4_hi[i * 2];

        cout << "D4 " << cD4[i] << endl;
        mem[output_offset / sizeof(float) + SIZE_SIGNAL +SIZE_D3+ i] = cD4[i];
    }
	


     //---------------------------LEVEL 5 DWT------------------------------------
	//discrete wavelet transforms - DWT5
  //convfft with LoD

	float conv5_lo[16]= {0};
    for (t = 0; t <SIZE_D4; t++) {


        for (int k = 0; k < NUM_LOD; k++) {
        if (t - k < 0) {
            break;
        }
        conv5_lo[t] += cA4[t - k] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + k];

    }

    }
  
  // Downsampling by 2 gives cA
   // ofstream myfile1("A5.txt");
	float cA5[8]= {0};
    for (int i = 0; i < SIZE_D5; i++) {
    	 cA5[i] = conv5_lo[i * 2];

        cout << "A5 " << cA5[i] << endl;
        //myfile1 << cA5[i] << "\n";

		mem[output_offset/sizeof(float) + SIZE_SIGNAL+SIZE_D3+SIZE_D4+i] = cA5[i]; //A5 COEFF OUTPUT AFTER D3
    }
   // myfile1.close();
  
    //convfft with HiD

    float conv5_hi[16]= {0};
    for (t = 0; t <SIZE_D4; t++) {
        for (int k = 0; k < NUM_HID; k++) {
        if (t - k < 0) {
            break;
        }
        conv5_hi[t] += cA4[t - k] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + NUM_LOD + k];

    }

    }

     // Downsampling by 2 gives cD
	float cD5[8]= {0};
    for (int i = 0; i < SIZE_D5; i++) {
    	cD5[i] = conv5_hi[i * 2];

        cout << "D5 " << cD5[i] << endl;
        mem[output_offset / sizeof(float) + SIZE_SIGNAL +SIZE_D3 + SIZE_D4+ SIZE_D5+ i] = cD5[i]; //A5 COEFF OUTPUT AFTER D3

    }
   


}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//array = adc input_iterator - SIZE_SIGNAL = 256
//fin coeffs - NUM_COEFFS = 501
//LoD coeffs = NUM_LOD = 8
//HiD coeffs = NUM_HID = 8
//outputs = filtered sig, d3,d4,a5, d5 - 256, 32,16, 8, 8

// *mem -> 0 x 0000 0000 
// input_offset -> 0x90000000
// (0x91000000 -- 0x91000000) -> everything written to DDR
// output_offset -> 0x91000000 
//FILTERED SIGNAL mem[output_offset/sizeof(float) + i]
//D3 mem[output_offset/sizeof(float) + SIZE_SIGNAL +i]
//D5 mem[output_offset/sizeof(float) + SIZE_SIGNAL+SIZE_D3 +i]
//A5 mem[output_offset/sizeof(float) + SIZE_SIGNAL +SIZE_D3+SIZE_D5+i]


//d3 = mem[output_offset/sizeof(float) + SIZE_SIGNAL + i] 


//SIGNAL FROM ADC VALUES - sampling rate of 256Hz, 16-bit samples
// mem[input_offset/sizeof(float)+i]
// adc_in[0] = mem[input_offset/sizeof(float)]; //0x91000000
// adc_in[1] = mem[input_offset/sizeof(float) + 1]; //0x91000004
// ..... 
// .....
//adc_in[255] = mem[input_offset/sizeof(float)+255]; //0x910003FC



//WAVELET FILTER COEFFICIENTS
//mem[input_offset/sizeof(float)+ SIZE_SIGNAL + NUM_COEFFS + i]
//LoD[0] 
//....
//LoD[7]

//mem[input_offset/sizeof(float)+ SIZE_SIGNAL + NUM_COEFFS + NUM_LOD + i]
//HiD[0]



