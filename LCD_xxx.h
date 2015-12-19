#include <stdint.h>
//segment bit RAM map
#define S_1E 1
#define S_1G 2
#define S_1F 3
#define S_1D 4
#define S_1C 5
#define S_1B 6
#define S_1A 7


#define S_X8 ( 8*1 + 0 )
#define S_2E ( 8*1 + 1 )
#define S_2G ( 8*1 + 2 )
#define S_2F ( 8*1 + 3 )
#define S_2D ( 8*1 + 4 )
#define S_2C ( 8*1 + 5 )
#define S_2B ( 8*1 + 6 )
#define S_2A ( 8*1 + 7 )


#define S_COL ( 8*2 + 0 )
#define S_3E ( 8*2 + 1 )
#define S_3G ( 8*2 + 2 )
#define S_3F ( 8*2 + 3 )
#define S_3D ( 8*2 + 4 )
#define S_3C ( 8*2 + 5 )
#define S_3B ( 8*2 + 6 )
#define S_3A ( 8*2 + 7 )


#define S_X2 ( 8*3 + 0 )
#define S_X7 ( 8*3 + 1 )
#define S_X1 ( 8*3 + 2 )
#define S_XSTART ( 8*3 + 3 )
#define S_X3 ( 8*3 + 4 )
#define S_X4 ( 8*3 + 5 )
#define S_X5 ( 8*3 + 6 )
#define S_X6 ( 8*3 + 7 )


#define S_4D ( 8*4 + 0 )
#define S_4C ( 8*4 + 1 )
#define S_4B ( 8*4 + 2 )
#define S_4A ( 8*4 + 3 )
#define S_END ( 8*4 + 4 )
#define S_4E ( 8*4 + 5 )
#define S_4G ( 8*4 + 6 )
#define S_4F ( 8*4 + 7 )


#define S_TEMP ( 8*5 + 0 )
#define S_X9 ( 8*5 + 1 )
#define S_Y1 ( 8*5 + 2 )
#define S_Y5 ( 8*5 + 3 )
#define S_5F ( 8*5 + 4 )
#define S_5G ( 8*5 + 5 )
#define S_5E ( 8*5 + 6 )
#define S_Y2 ( 8*5 + 7 )


#define S_5A ( 8*6 + 0 )
#define S_5B ( 8*6 + 1 )
#define S_5C ( 8*6 + 2 )
#define S_5D ( 8*6 + 3 )
#define S_6F ( 8*6 + 4 )
#define S_6G ( 8*6 + 5 )
#define S_6E ( 8*6 + 6 )
#define S_Y3 ( 8*6 + 7 )

#define S_6A ( 8*7 + 0 )
#define S_6B ( 8*7 + 1 )
#define S_6C ( 8*7 + 2 )
#define S_6D ( 8*7 + 3 )
#define S_X10 ( 8*7 + 4 )
#define S_X11 ( 8*7 + 5 )
#define S_X12 ( 8*7 + 6 )
#define S_Y4 ( 8*7 + 7 )


#define S_OFF ( 8*8 + 0 )
#define S_Y7 ( 8*8 + 1 )
#define S_Y8 ( 8*8 + 2 )
#define S_Y9 ( 8*8 + 3 )


//7 seg led map data
uint8_t DISP_7SEG_1 [ ][ 7 ] = {
S_1A, S_1B, S_1C, S_1D, S_1E, S_1F, S_1E, //0
S_1B, S_1C, S_1B, S_1C, S_1B, S_1C, S_1B, //1
S_1A, S_1B, S_1G, S_1E, S_1D, S_1E, S_1G, //2
S_1A, S_1B, S_1C, S_1D, S_1G, S_1D, S_1C, //3
S_1F, S_1G, S_1B, S_1C, S_1B, S_1G, S_1F, //4
S_1A, S_1F, S_1G, S_1C, S_1D, S_1C, S_1G, //5
S_1C, S_1D, S_1E, S_1F, S_1G, S_1F, S_1E, //6
S_1A, S_1B, S_1C, S_1B, S_1A, S_1B, S_1C, //7
S_1A, S_1B, S_1C, S_1D, S_1E, S_1F, S_1G, //8, clear 7-seg
S_1A, S_1B, S_1C, S_1F, S_1G, S_1F, S_1C //9
};

uint8_t DISP_7SEG_2 [ ][ 7 ] = {
S_2A, S_2B, S_2C, S_2D, S_2E, S_2F, S_2E, //0
S_2B, S_2C, S_2B, S_2C, S_2B, S_2C, S_2B, //1
S_2A, S_2B, S_2G, S_2E, S_2D, S_2E, S_2G, //2
S_2A, S_2B, S_2C, S_2D, S_2G, S_2D, S_2C, //3
S_2F, S_2G, S_2B, S_2C, S_2B, S_2G, S_2F, //4
S_2A, S_2F, S_2G, S_2C, S_2D, S_2C, S_2G, //5
S_2C, S_2D, S_2E, S_2F, S_2G, S_2F, S_2E, //6
S_2A, S_2B, S_2C, S_2B, S_2A, S_2B, S_2C, //7
S_2A, S_2B, S_2C, S_2D, S_2E, S_2F, S_2G, //8, clear 7-seg
S_2A, S_2B, S_2C, S_2F, S_2G, S_2F, S_2C //9
};

uint8_t DISP_7SEG_3 [ ][ 7 ] = {
S_3A, S_3B, S_3C, S_3D, S_3E, S_3F, S_3E, //0
S_3B, S_3C, S_3B, S_3C, S_3B, S_3C, S_3B, //1
S_3A, S_3B, S_3G, S_3E, S_3D, S_3E, S_3G, //2
S_3A, S_3B, S_3C, S_3D, S_3G, S_3D, S_3C, //3
S_3F, S_3G, S_3B, S_3C, S_3B, S_3G, S_3F, //4
S_3A, S_3F, S_3G, S_3C, S_3D, S_3C, S_3G, //5
S_3C, S_3D, S_3E, S_3F, S_3G, S_3F, S_3E, //6
S_3A, S_3B, S_3C, S_3B, S_3A, S_3B, S_3C, //7
S_3A, S_3B, S_3C, S_3D, S_3E, S_3F, S_3G, //8, clear 7-seg
S_3A, S_3B, S_3C, S_3F, S_3G, S_3F, S_3C //9
};

uint8_t DISP_7SEG_4 [ ][ 7 ] = {
S_4A, S_4B, S_4C, S_4D, S_4E, S_4F, S_4E, //0
S_4B, S_4C, S_4B, S_4C, S_4B, S_4C, S_4B, //1
S_4A, S_4B, S_4G, S_4E, S_4D, S_4E, S_4G, //2
S_4A, S_4B, S_4C, S_4D, S_4G, S_4D, S_4C, //3
S_4F, S_4G, S_4B, S_4C, S_4B, S_4G, S_4F, //4
S_4A, S_4F, S_4G, S_4C, S_4D, S_4C, S_4G, //5
S_4C, S_4D, S_4E, S_4F, S_4G, S_4F, S_4E, //6
S_4A, S_4B, S_4C, S_4B, S_4A, S_4B, S_4C, //7
S_4A, S_4B, S_4C, S_4D, S_4E, S_4F, S_4G, //8, clear 7-seg
S_4A, S_4B, S_4C, S_4F, S_4G, S_4F, S_4C //9
};

#define Clear_7SEG 8
uint8_t DISP_7SEG_5 [ ][ 7 ] = {
S_5A, S_5B, S_5C, S_5D, S_5E, S_5F, S_5E, //0
S_5B, S_5C, S_5B, S_5C, S_5B, S_5C, S_5B, //1
S_5A, S_5B, S_5G, S_5E, S_5D, S_5E, S_5G, //2
S_5A, S_5B, S_5C, S_5D, S_5G, S_5D, S_5C, //3
S_5F, S_5G, S_5B, S_5C, S_5B, S_5G, S_5F, //4
S_5A, S_5F, S_5G, S_5C, S_5D, S_5C, S_5G, //5
S_5C, S_5D, S_5E, S_5F, S_5G, S_5F, S_5E, //6
S_5A, S_5B, S_5C, S_5B, S_5A, S_5B, S_5C, //7
S_5A, S_5B, S_5C, S_5D, S_5E, S_5F, S_5G, //8, clear 7-seg
S_5A, S_5B, S_5C, S_5F, S_5G, S_5F, S_5C //9
};

uint8_t DISP_7SEG_6 [ ][ 7 ] = {
S_6A, S_6B, S_6C, S_6D, S_6E, S_6F, S_6E, //0
S_6B, S_6C, S_6B, S_6C, S_6B, S_6C, S_6B, //1
S_6A, S_6B, S_6G, S_6E, S_6D, S_6E, S_6G, //2
S_6A, S_6B, S_6C, S_6D, S_6G, S_6D, S_6C, //3
S_6F, S_6G, S_6B, S_6C, S_6B, S_6G, S_6F, //4
S_6A, S_6F, S_6G, S_6C, S_6D, S_6C, S_6G, //5
S_6C, S_6D, S_6E, S_6F, S_6G, S_6F, S_6E, //6
S_6A, S_6B, S_6C, S_6B, S_6A, S_6B, S_6C, //7
S_6A, S_6B, S_6C, S_6D, S_6E, S_6F, S_6G, //8, clear 7-seg
S_6A, S_6B, S_6C, S_6F, S_6G, S_6F, S_6C //9
};

//regular segments map data
uint8_t DISP_regular [] = { S_X8, S_Y5, S_X10, S_X12, S_TEMP };  //clear

//battery power level indicator data with 6 levels
#define Clear_Bat_Level 5
uint8_t DISP_bat_level [][6] = {
S_X7, S_X7, S_X7, S_X7, S_X7, S_X7,  
S_X7, S_X6, S_X7, S_X6, S_X7, S_X6,
S_X7, S_X6, S_X5, S_X6, S_X7, S_X6,
S_X7, S_X6, S_X5, S_X4, S_X5, S_X6,
S_X7, S_X6, S_X5, S_X4, S_X3, S_X4,
S_X7, S_X6, S_X5, S_X4, S_X3, S_X2 //clear battery level
};

//water&seat&fan&spray temperature level indicator data
#define Clear_Misc_Level 4
uint8_t DISP_misc_level [][4] = {
S_OFF, S_OFF, S_OFF, S_OFF,
S_Y7, S_Y7, S_Y7, S_Y7,
S_Y7, S_Y8, S_Y7, S_Y8,
S_Y7, S_Y8, S_Y9, S_Y8,
S_OFF, S_Y7, S_Y8, S_Y9 //clear
};

#define Seat_Logo 0
#define Water_Tank_Temp_Logo 1
#define Clear_All_Logo 2
uint8_t DISP_mode_logo [][2] = {
S_Y3, S_Y3,
S_Y4, S_Y4,
S_Y3, S_Y4 //clear all logo
};

#define Spotlight_Logo 0
uint8_t DISP_misc_logo [] = {
    S_X9
};