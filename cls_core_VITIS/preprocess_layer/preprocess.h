#ifndef _PREPROCESS_H
#define _PREPROCESS_H

#include<string>
#include<vector>
#include <stdio.h>
//#include <hls_math.h>
using namespace std;

void preprocess(float *mem, int input_offset, int output_offset, int NUM_LOD, int NUM_HID, int SIZE_SIGNAL, int SIZE_D1, int SIZE_D2, int SIZE_D3, int SIZE_D4, int SIZE_D5);

#endif