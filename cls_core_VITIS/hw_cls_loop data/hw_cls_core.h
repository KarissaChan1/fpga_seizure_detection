//------------------------Address Info-------------------
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of input_offset
//        bit 31~0 - input_offset[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of output_offset
//        bit 31~0 - output_offset[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of NUM_LOD
//        bit 31~0 - NUM_LOD[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of NUM_HID
//        bit 31~0 - NUM_HID[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of SIZE_SIGNAL
//        bit 31~0 - SIZE_SIGNAL[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of SIZE_D1
//        bit 31~0 - SIZE_D1[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of SIZE_D2
//        bit 31~0 - SIZE_D2[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of SIZE_D3
//        bit 31~0 - SIZE_D3[31:0] (Read/Write)
// 0x4c : reserved
// 0x50 : Data signal of SIZE_D4
//        bit 31~0 - SIZE_D4[31:0] (Read/Write)
// 0x54 : reserved
// 0x58 : Data signal of SIZE_D5
//        bit 31~0 - SIZE_D5[31:0] (Read/Write)
// 0x5c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define preprocess_INPUT_OFFSET 0 //ADC output, FIR coeffs, DWT LoD, DWT HiD
#define preprocess_OUTPUT_OFFSET 4194304 //0x91000000 = filtered sig, D3,D5,A5
#define HW_preprocess_CTRL_ADDR                           0x44A00000
#define preprocess_CTRL_BUS_ADDR_AP_CTRL                0x00
#define preprocess_CTRL_BUS_ADDR_GIE                    0x04
#define preprocess_CTRL_BUS_ADDR_IER                    0x08
#define preprocess_CTRL_BUS_ADDR_ISR                    0x0c
#define preprocess_CTRL_BUS_ADDR_INPUT_OFFSET_DATA      0x10
#define preprocess_CTRL_BUS_BITS_INPUT_OFFSET_DATA      32
#define preprocess_CTRL_BUS_ADDR_OUTPUT_OFFSET_DATA     0x18
#define preprocess_CTRL_BUS_BITS_OUTPUT_OFFSET_DATA     32
#define preprocess_CTRL_BUS_ADDR_NUM_LOD_DATA            0x20
#define preprocess_CTRL_BUS_BITS_NUM_LOD_DATA            32
#define preprocess_CTRL_BUS_ADDR_NUM_HID_DATA           0x28
#define preprocess_CTRL_BUS_BITS_NUM_HID_DATA           32
#define preprocess_CTRL_BUS_ADDR_SIZE_SIGNAL_DATA       0x30
#define preprocess_CTRL_BUS_BITS_SIZE_SIGNAL_DATA       32
#define preprocess_CTRL_BUS_ADDR_SIZE_D1_DATA              0X38
#define preprocess_CTRL_BUS_BITS_SIZE_D1_DATA              32
#define preprocess_CTRL_BUS_ADDR_SIZE_D2_DATA           0X40
#define preprocess_CTRL_BUS_BITS_SIZE_D2_DATA           32
#define preprocess_CTRL_BUS_ADDR_SIZE_D3_DATA           0X48
#define preprocess_CTRL_BUS_BITS_SIZE_D3_DATA           32
#define preprocess_CTRL_BUS_ADDR_SIZE_D4_DATA           0X50
#define preprocess_CTRL_BUS_BITS_SIZE_D4_DATA           32
#define preprocess_CTRL_BUS_ADDR_SIZE_D5_DATA           0X58
#define preprocess_CTRL_BUS_BITS_SIZE_D5_DATA           32

//------------------------Address Info-------------------
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of input_offset
//        bit 31~0 - input_offset[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of output_offset
//        bit 31~0 - output_offset[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of SIZE_SIGNAL
//        bit 31~0 - SIZE_SIGNAL[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of SIZE_D3
//        bit 31~0 - SIZE_D3[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of SIZE_D4
//        bit 31~0 - SIZE_D4[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of SIZE_D5
//        bit 31~0 - SIZE_D5[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of SIZE_A5
//        bit 31~0 - SIZE_A5[31:0] (Read/Write)
// 0x44 : reserved

#define FEATEXTRACT_INPUT_OFFSET 4194304  //filtered sig, D3,D4,D5,A5
#define FEATEXTRACT_OUTPUT_OFFSET 8388608 //0x92000000 = feature vector
#define HW_featextract_CTRL_ADDR       				0x44A40000
#define featextract_CTRL_BUS_ADDR_AP_CTRL            	0x00
#define featextract_CTRL_BUS_ADDR_GIE                	0x04
#define featextract_CTRL_BUS_ADDR_IER                	0x08
#define featextract_CTRL_BUS_ADDR_ISR                	0x0c
#define featextract_CTRL_BUS_ADDR_INPUT_OFFSET_DATA  	0x10
#define featextract_CTRL_BUS_BITS_INPUT_OFFSET_DATA  	32
#define featextract_CTRL_BUS_ADDR_OUTPUT_OFFSET_DATA 	0x18
#define featextract_CTRL_BUS_BITS_OUTPUT_OFFSET_DATA 	32
#define featextract_CTRL_BUS_ADDR_SIZE_SIGNAL_DATA		0x20
#define featextract_CTRL_BUS_BITS_SIZE_SIGNAL_DATA    	32
#define featextract_CTRL_BUS_ADDR_SIZE_D3_DATA    		0x28
#define featextract_CTRL_BUS_BITS_SIZE_D3_DATA    		32
#define featextract_CTRL_BUS_ADDR_SIZE_D4_DATA   		0x30
#define featextract_CTRL_BUS_BITS_SIZE_D4_DATA 			32
#define featextract_CTRL_BUS_ADDR_SIZE_D5_DATA   		0x38
#define featextract_CTRL_BUS_BITS_SIZE_D5_DATA   		32
#define featextract_CTRL_BUS_ADDR_SIZE_A5_DATA        	0x40
#define featextract_CTRL_BUS_BITS_SIZE_A5_DATA          32

//------------------------Address Info-------------------
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of input_offset
//        bit 31~0 - input_offset[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of output_offset
//        bit 31~0 - output_offset[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of NUM_BETA
//        bit 31~0 - NUM_BETA[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of bias
//        bit 31~0 - bias[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of scale
//        bit 31~0 - scale[31:0] (Read/Write)
// 0x34 : reserved

#define classify_INPUT_OFFSET 8388608 //feature vector, SVM params: beta
#define classify_OUTPUT_OFFSET 12582912 //0X93000000 
#define HW_classify_CTRL_ADDR       				0x44A80000
#define classify_CTRL_BUS_ADDR_AP_CTRL            	0x00
#define classify_CTRL_BUS_ADDR_GIE                	0x04
#define classify_CTRL_BUS_ADDR_IER                	0x08
#define classify_CTRL_BUS_ADDR_ISR                	0x0c
#define classify_CTRL_BUS_ADDR_INPUT_OFFSET_DATA  	0x10
#define classify_CTRL_BUS_BITS_INPUT_OFFSET_DATA  	32
#define classify_CTRL_BUS_ADDR_OUTPUT_OFFSET_DATA 	0x18
#define classify_CTRL_BUS_BITS_OUTPUT_OFFSET_DATA 	32
#define classify_CTRL_BUS_ADDR_NUM_BETA_DATA		0x20
#define classify_CTRL_BUS_BITS_NUM_BETA_DATA    	32
#define classify_CTRL_BUS_ADDR_BIAS_DATA        	0x28
#define classify_CTRL_BUS_BITS_BIAS_DATA          	32
#define classify_CTRL_BUS_ADDR_SCALE_DATA        	0x30
#define classify_CTRL_BUS_BITS_SCALE_DATA          	32



//common HLS functions

int   read_reg(volatile void* map_base, int offset);
void  write_reg(volatile void* map_base, int offset, int value);
void  start_layer(volatile void* map_base, int target, int ap_start_addr);
int   poll_layer(volatile void* map_base, int target, int ap_status_addr);

void setup_preprocess_layer( volatile void* map_base, int target, int input_offset, int output_offset, int NUM_LOD, int NUM_HID, int SIZE_SIGNAL, int SIZE_D1, int SIZE_D2, int SIZE_D3, int SIZE_D4, int SIZE_D5);
void setup_feature_extract_layer( volatile void* map_base, int target, int input_offset, int output_offset, int SIZE_SIGNAL,  int SIZE_D3, int SIZE_D4,int SIZE_D5, int SIZE_A5 );
void setup_classify_layer( volatile void* map_base, int target, int input_offset, int output_offset, int NUM_BETA,  float bias, float scale );
void preprocess_hw(int input_offset, int output_offset, int NUM_LOD, int NUM_HID, int SIZE_SIGNAL, int SIZE_D1, int SIZE_D2, int SIZE_D3, int SIZE_D4, int SIZE_D5);
void feature_extract_hw(int input_offset, int output_offset, int SIZE_SIGNAL,  int SIZE_D3, int SIZE_D4,int SIZE_D5,int SIZE_A5);
void classify_hw(int input_offset, int output_offset, int NUM_BETA, float bias, float scale);


void hw_hls_core_processing ();

void write_to_ddr(float *ddrMemory);










