#define FEATEXTRACT_INPUT_OFFSET 0
#define FEATEXTRACT_OUTPUT_OFFSET 4194304 //0x92000000
#define FEATEXTRACT_OUTPUT_OFFSET 0x01000000
#define HW_featextract_CTRL_ADDR       				0x44A10000
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
#define featextract_CTRL_BUS_ADDR_SIZE_D5_DATA   		0x30
#define featextract_CTRL_BUS_BITS_SIZE_D5_DATA   		32
#define featextract_CTRL_BUS_ADDR_SIZE_A5_DATA        	0x38
#define featextract_CTRL_BUS_BITS_SIZE_A5_DATA          32

float adc_input[256] = {34.5787545787546,0.195360195360195,0.195360195360195,0.195360195360195,0.195360195360195,-1.75824175824176,-0.976800976800978,4.49328449328449,4.88400488400488,-3.71184371184371,-7.22832722832723,-3.71184371184371,-0.976800976800978,16.2148962148962,32.6251526251526,32.6251526251526,31.8437118437118,43.5653235653236,54.1147741147741,56.8498168498168,62.7106227106227,67.3992673992674,67.3992673992674,70.1343101343101,69.7435897435897,65.0549450549451,68.5714285714286,69.7435897435897,68.1807081807082,66.2271062271062,71.6971916971917,75.2136752136752,72.4786324786325,72.0879120879121,74.041514041514,78.3394383394383,77.1672771672772,75.2136752136752,74.041514041514,71.3064713064713,68.5714285714286,63.1013431013431,52.5518925518925,45.5189255189255,40.8302808302808,34.1880341880342,27.1550671550672,29.1086691086691,29.4993894993895,22.8571428571429,17.7777777777778,15.042735042735,10.7448107448107,6.83760683760684,5.27472527472527,1.36752136752137,-1.36752136752137,-4.88400488400488,-11.9169719169719,-19.3406593406593,-17.7777777777778,-18.5592185592186,-24.4200244200244,-29.4993894993895,-28.3272283272283,-25.5921855921856,-28.7179487179487,-29.1086691086691,-28.7179487179487,-29.8901098901099,-26.3736263736264,-23.2478632478632,-22.8571428571429,-20.1221001221001,-18.1684981684982,-17.7777777777778,-12.6984126984127,-2.14896214896215,7.61904761904762,12.6984126984127,16.6056166056166,27.9365079365079,38.8766788766789,41.2210012210012,43.1746031746032,45.9096459096459,46.3003663003663,49.035409035409,49.035409035409,48.2539682539683,49.8168498168498,49.4261294261294,50.2075702075702,51.7704517704518,52.5518925518925,53.3333333333333,48.6446886446886,40.8302808302808,40.8302808302808,37.7045177045177,30.6715506715507,23.2478632478632,19.3406593406593,14.6520146520147,7.61904761904762,1.75824175824176,-7.22832722832723,-12.3076923076923,-11.9169719169719,-17.3870573870574,-23.6385836385836,-25.2014652014652,-27.1550671550672,-38.8766788766789,-49.4261294261294,-50.2075702075702,-54.5054945054945,-56.8498168498169,-56.0683760683761,-60.3663003663004,-64.2735042735043,-63.4920634920635,-67.3992673992674,-70.5250305250305,-63.1013431013431,-54.8962148962149,-54.8962148962149,-52.1611721611722,-43.5653235653236,-38.0952380952381,-38.4859584859585,-38.4859584859585,-41.2210012210012,-43.1746031746032,-43.956043956044,-45.1282051282051,-49.035409035409,-50.2075702075702,-55.2869352869353,-60.7570207570208,-62.3199023199023,-62.3199023199023,-62.7106227106227,-67.3992673992674,-72.8693528693529,-70.1343101343101,-65.8363858363858,-68.5714285714286,-69.3528693528693,-69.3528693528693,-68.5714285714286,-68.5714285714286,-68.1807081807082,-69.7435897435897,-70.9157509157509,-69.7435897435897,-68.1807081807082,-67.3992673992674,-63.4920634920635,-61.1477411477412,-68.5714285714286,-78.3394383394383,-76.7765567765568,-74.8229548229548,-76.7765567765568,-73.6507936507936,-69.3528693528693,-64.6642246642247,-56.8498168498169,-49.035409035409,-46.6910866910867,-42.7838827838828,-30.6715506715507,-25.982905982906,-23.2478632478632,-15.4334554334554,-12.3076923076923,-18.5592185592186,-21.6849816849817,-18.5592185592186,-21.6849816849817,-26.3736263736264,-27.1550671550672,-29.8901098901099,-27.9365079365079,-21.2942612942613,-18.1684981684982,-14.2612942612943,-0.586080586080587,9.96336996336996,13.0891330891331,18.1684981684982,26.3736263736264,34.1880341880342,35.7509157509158,40.4395604395604,42.3931623931624,42.7838827838828,43.5653235653236,38.8766788766789,29.4993894993895,25.982905982906,18.1684981684982,11.5262515262515,11.1355311355311,15.8241758241758,18.949938949939,18.5592185592186,18.949938949939,21.2942612942613,27.5457875457875,27.5457875457875,27.5457875457875,31.0622710622711,34.969474969475,37.3137973137973,34.1880341880342,27.9365079365079,16.996336996337,9.57264957264957,4.88400488400488,-1.36752136752137,-0.586080586080587,-0.195360195360196,-8.4004884004884,-11.5262515262515,-5.27472527472528,-1.36752136752137,2.14896214896215,8.4004884004884,15.8241758241758,26.7643467643468,39.2673992673993,46.6910866910867,53.3333333333333,57.6312576312576,63.1013431013431,67.008547008547,67.7899877899878,72.4786324786325,72.0879120879121,62.3199023199023,51.7704517704518,46.6910866910867,40.04884004884,35.7509157509158,29.4993894993895,24.4200244200244,20.1221001221001,20.1221001221001,18.1684981684982,21.2942612942613,32.6251526251526,45.5189255189255,47.8632478632479,50.5982905982906};
float d3_coeffs[32] = {-9.07299e-06,6.54893e-06,-0.0645258,0.238568,-0.0761754,0.00746277,-0.00117661,0.00486347,-0.00892404,0.00947369,-0.0019565,0.00694501,0.0047597,-0.0200545,0.00350958,-0.00516447,0.0153687,0.00375241,0.0124908,-0.0259462,0.00394452,0.00992556,0.00200193,0.00359675,0.0044355,-0.0254981,0.0351643,-0.0266992,0.0141644,0.00818208,-0.0210497,0.0342846};
float d5_coeffs[8] = {-1.01944e-09,-0.000452804,-0.00569272,-0.329763,-0.1244,-0.147157,0.053616,0.320916};
float a5_coeffs[8] = {-4.69014e-11,-2.08314e-05,-0.000144418,-0.0140866,0.0776757,-0.262624,1.75816,-2.68106};