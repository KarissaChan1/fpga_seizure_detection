#ifndef _FEATEXTRACT_H
#define _FEATEXTRACT_H

#include<string>
#include<vector>
#include <stdio.h>
//#include <hls_math.h>
using namespace std;

void feature_extract(float* mem, int input_offset, int output_offset, int SIZE_SIGNAL, int SIZE_D3, int SIZE_D4, int SIZE_D5, int SIZE_A5);

#endif
