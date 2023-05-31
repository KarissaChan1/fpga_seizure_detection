#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>
#include "classify.h"
using namespace std;

int sgn(float d) {
	if (d < 0) {
		return -1;
	}
	if (d > 0) {
		return 1;
	}
	return 0;
}

void classify(float* mem, int input_offset, int output_offset, int NUM_BETA, float bias, float scale) {
#pragma HLS INTERFACE m_axi port=mem depth=200000
#pragma HLS INTERFACE s_axilite port=input_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=output_offset bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=NUM_BETA bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=bias bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=scale bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS

	float D = 0;
	float F;
	int label;
	
	

	//compute distance
	for (int i = 0; i < NUM_BETA; i++) {					//feat[0]
		D += mem[input_offset / sizeof(float) +NUM_BETA+ i] * (mem[input_offset / sizeof(float) + i]/scale);

	}
	mem[output_offset / sizeof(float)] = D;
	cout << "Distance " << D << endl;

	F = D + bias;
	mem[output_offset / sizeof(float) + 1] = F;
	cout << "Function " << F << endl;

	label = sgn(F);
	if (label == -1)
	{
		label = 1;
	}
	else label = 0;



	mem[output_offset / sizeof(float) + 2] = label;
	cout << "Label:" << label<<endl;
}



// *mem -> 0 x 0000 0000 
// input_offset -> 0x90000000
// (0x90000000 -- 0x91000000) -> everything written to DDR
// output_offset -> 0x91000000 -> w from mem[output_offset/sizeof(float)] -- mem[output_offset/sizeof(float) + 9]; 0x91000040
//output_offset -> 0x91000040 = classification label


// 1. VITIS: Write the feat[SIZE_VEC] values to DDR (0x90000000).

//FEAT VALUES
// mem[input_offset/sizeof(float)+i]
// feat[0] = mem[input_offset/sizeof(float)]; //0x90000000
// feat[1] = mem[input_offset/sizeof(float) + 1]; //0x90000004
// ..... 
// .....
// feat[9] = mem[input_offset/sizeof(float) + 26]; //0x90000040

//ALPHA VALUES
// mem[input_offset/sizeof(float) + SIZE_VEC +i]
// alpha[0] = mem[input_offset/sizeof(float)]; //0x90000044
// alpha[1] = mem[input_offset/sizeof(float) + 1]; //0x90000048
// ..... 
// .....
// alpha[26] = mem[input_offset/sizeof(float) + 26]; //0x90000152

//LABEL VALUES
// mem[input_offset/sizeof(float)+ + SIZE_VEC + NUM_ALPHA1 + i] = labels
// labels[0] = mem[input_offset/sizeof(float) + 27]; //0x90000156
// labels[1] = mem[input_offset/sizeof(float) + 28]; //0x90000160
// ..... 
// .....
// labels[26] = mem[input_offset/sizeof(float) + 53]; //0x90000264

//SUPPORT VECTORS
//mem[input_offset/sizeof(float) + + SIZE_VEC + NUM_ALPHA + NUM_LABEL + i] = supportvec
//vector[0] = mem[input_offset/sizeof(float) + 54]; //0x90000268
//.....
//vector[269] = mem[input_offset/sizeof(float) + 54 + 269]; //0x90001348


