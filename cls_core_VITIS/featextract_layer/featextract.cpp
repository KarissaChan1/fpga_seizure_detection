#include <cmath>
#include <iostream>
#include "limits.h"
#include "featextract.h"

using namespace std;



void feature_extract(float *mem, int input_offset, int output_offset, int SIZE_SIGNAL, int SIZE_D3, int SIZE_D4, int SIZE_D5, int SIZE_A5) {
#pragma HLS INTERFACE m_axi port=mem depth=200000
#pragma HLS INTERFACE s_axilite port=input_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=output_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_SIGNAL bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_D3 bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_D4 bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_D5 bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=SIZE_A5 bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS

	//FEATURES: d3 rms	d3 std	d3 shannon entropy	d3 abs mean	rms	d5 skewness	a5 skewness	d5 kurtosis	d3 min	d3 max
	//d3 rms	d3 std	rms	d3 abs mean	d3 shannon entropy	a5 std	a5 rms	a5 skewness	d5 rms	d4 rms
	//d5 rms	d5 std	d5 abs mean	a5 std	d5 min	d5 max	rms	d3 rms	d3 std	d4 rms

	//d5 rms	d5 std	d5 abs mean	a5 std	d5 min	d5 max	d3 rms	d3 std	d4 max	d4 rms

	

//get shannon entropy (d3)
	/*float sum = 0;
	for (int i = 0; i < SIZE_D3; i++) {

		if (mem[input_offset / sizeof(float) + SIZE_SIGNAL +  i] != 0) {
			mem[input_offset / sizeof(float) + SIZE_SIGNAL +i] = mem[input_offset / sizeof(float) + SIZE_SIGNAL +i] * mem[input_offset / sizeof(float) + SIZE_SIGNAL  +i];

		}

		sum += mem[input_offset / sizeof(float) + SIZE_SIGNAL + i] * log(1.1921e-07 + mem[input_offset / sizeof(float) + SIZE_SIGNAL + i]);
	}

	float entrop_d3 = -1 * sum;*/


//get RMS (using time signal, D4, D5, D3)
	//float sum_squared_ts = 0;
	float sum_squared_d3 = 0;
	float sum_squared_d4 = 0;
	float sum_squared_d5 = 0;
	
	
	//float rms_ts;
float rms_d3, rms_d4, rms_d5;



	/*for (int i = 0; i < SIZE_SIGNAL; i++) {
		sum_squared_ts += mem[input_offset/sizeof(float)+i] * mem[input_offset/sizeof(float)+i];
	}

	rms_ts = sqrt(sum_squared_ts / SIZE_SIGNAL);*/
	

	for (int i = 0; i< SIZE_D3; i++){
		sum_squared_d3 += mem[input_offset/sizeof(float) + SIZE_SIGNAL +i] * mem[input_offset/sizeof(float) + SIZE_SIGNAL +i];
		
	}
	rms_d3 = sqrt(sum_squared_d3 / SIZE_D3);

	for (int i = 0; i < SIZE_D4; i++) {
		sum_squared_d4 += mem[input_offset / sizeof(float) + SIZE_SIGNAL +SIZE_D3+ i] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + i];

	}
	rms_d4 = sqrt(sum_squared_d4 / SIZE_D4);

	for (int i = 0; i < SIZE_D5; i++) {
		sum_squared_d5 += mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4+SIZE_A5+ i] * mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + SIZE_A5 + i];
		
	}
	rms_d5 = sqrt(sum_squared_d5 / SIZE_D5);
	
	
	//get abs mean (using D5)
	float sumD5 = 0;
float absavgD5;
	
for (int i = 0; i < SIZE_D5; i++) {
	sumD5 += abs(mem[input_offset / sizeof(float) + SIZE_SIGNAL +SIZE_D3+SIZE_D4+SIZE_A5+ i]);
}

	absavgD5 = sumD5 / SIZE_D5;
	


//get STD (using D3,D5, A5)
float sumD3 = 0;
float temp = 0;
float std_d3;


	for (int i = 0; i < SIZE_D3; i++) {
		temp += mem[input_offset/sizeof(float) + SIZE_SIGNAL + i]; 
		sumD3 += (mem[input_offset/sizeof(float) + SIZE_SIGNAL+  i] - (temp/SIZE_D3)) * (mem[input_offset/sizeof(float) + SIZE_SIGNAL+  i] - (temp/SIZE_D3));
	}
	std_d3 = sqrt(sumD3 / (SIZE_D3 - 1));

	//get std for D5, A5 for skewness
	sumD5 = 0;
	float sumA5 = 0;
	float tempd5 = 0;
	float tempa5 = 0;
	float std_d5, std_a5;

	for (int i = 0; i < SIZE_D5; i++) {
		tempd5 += mem[input_offset / sizeof(float) + SIZE_SIGNAL +SIZE_D3+SIZE_D4+SIZE_A5+ i];
		sumD5 += (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + SIZE_A5 + i] - (tempd5 / SIZE_D5)) * (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + i] - (tempd5 / SIZE_D5));
		tempa5 += mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4  + i];
		sumA5 += (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4  + i] - (tempa5 / SIZE_D5)) * (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4+ i] - (tempa5 / SIZE_D5));
	}
	std_d5 = sqrt(sumD5 / (SIZE_D5 - 1));
	std_a5 = sqrt(sumA5 / (SIZE_D5 - 1));

	//get min max for D4, D5
	float minD5 = mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + SIZE_A5];
	float maxD5 = mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + SIZE_A5];

	for (int i = 0; i < SIZE_D5; i++) {
		if (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + SIZE_A5 + i] > maxD5) {
			maxD5 = mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + SIZE_A5 + i];
		}
		if (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + SIZE_A5 + i] < minD5) {
			minD5 = mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + SIZE_A5 + i];
		}
	}

	float maxD4 = mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3];
	for (int i = 0; i < SIZE_D4; i++) {
		if (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + i] > maxD4) {
			maxD5 = mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + i];
		}
	}

	//get skewness for  A5
	/*float m3_a5 = 0;
	float avga5 = 0;

	for (int i = 0; i < SIZE_D5; i++) {
		tempa5 += mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + i];
	}
	avga5 = tempa5 / SIZE_D5;

	for (int i = 0; i < SIZE_D5; i++) {
		tempa5 += (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4  + i] - avga5) * (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4  + i] - avga5) * (mem[input_offset / sizeof(float) + SIZE_SIGNAL + SIZE_D3 + SIZE_D4 + i] - avga5);
	}
	m3_a5 = tempa5 / SIZE_D5;

	float skewa5 = 0;
	skewa5 = m3_a5 / (std_a5 * std_a5 * std_a5);
*/

	

	//write feature vector to memory at output offset

////d5 rms	d5 std	d5 abs mean	a5 std	d5 min	d5 max	d3 rms	d3 std	d4 max	d4 rms
	mem[output_offset/sizeof(float)] = rms_d5;  //0x92000000
	mem[output_offset / sizeof(float) + 1] = std_d5; 
	mem[output_offset / sizeof(float) + 2] = absavgD5;
	mem[output_offset / sizeof(float) + 3] = std_a5;
	mem[output_offset / sizeof(float) + 4] = minD5;
	mem[output_offset / sizeof(float) + 5] = maxD5;
	mem[output_offset / sizeof(float) + 6] = rms_d3;
	mem[output_offset / sizeof(float) + 7] = std_d3;
	mem[output_offset / sizeof(float) + 8] = maxD4;
	mem[output_offset / sizeof(float) + 9] = rms_d4;
	//
	//for (int i = 0; i < 10; i++) {
	//	cout << mem[output_offset / sizeof(float) + i];
	//}
	
}


	





// *mem -> 0 x 0000 0000 
// input_offset -> 0x91000000
// (0x91000000 -- 0x92000000) -> everything written to DDR
// output_offset -> 0x92000000 -> rms = mem[output_offset/sizeof(float)] 
//output_offset -> 0x92000004 -> 


// 1. VITIS: Write the feat[SIZE_VEC] values to DDR (0x90000000).

//SIGNAL FROM ADC VALUES - sampling rate of 256Hz, 16-bit samples = 2 byte samples
// mem[input_offset/sizeof(float)+i]
// adc_in[0] = mem[input_offset/sizeof(float)]; //0x91000000
// adc_in[1] = mem[input_offset/sizeof(float) + 1]; //0x91000002
// ..... 
// .....
//adc_in[255] = mem[input_offset/sizeof(float)+255]; //0x91000200

//D3 VALUES (size 32)
// mem[input_offset/sizeof(float) + SIZE_SIGNAL +i]
// alpha[0] = mem[input_offset/sizeof(float)]; //0x91000202
// alpha[1] = mem[input_offset/sizeof(float) + 1]; //0x91000206
// ..... 
// .....
// alpha[31] = mem[input_offset/sizeof(float) + 26]; //0x91000282

//D4 VALUES (size 16)
// mem[input_offset/sizeof(float) + SIZE_SIGNAL + SIZE_D3 + i]
// labels[0] = mem[input_offset/sizeof(float) + 27]; //0x91000284
// labels[1] = mem[input_offset/sizeof(float) + 28]; //0x91000288
// ..... 
// .....
// labels[7] = mem[input_offset/sizeof(float) + 53]; //0x910002AC (312)

//A5 VALUES (size 8)
//mem[input_offset/sizeof(float)+ SIZE_SIGNAL + SIZE_D3 + SIZE_D5 + i] 
//vector[0] = mem[input_offset/sizeof(float) + 54]; //0x910002B0
//.....
//vector[269] = mem[input_offset/sizeof(float) + 269]; //0x90001348

//D5 VALUES (size 8)


