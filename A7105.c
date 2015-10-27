#include "A7105reg.h"
#include "define.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/pin_manager.h"
#include <xc.h>

const Uint8 ID_Tab[4] = {0x54, 0x75, 0xC5, 0x2A}; //ID code
const Uint16 A7105Config[]=
{
	0x00, //RESET register,		only reset, not use on config
	0x42, //MODE register,
	0x00, //CALIBRATION register,only read, not use on config
	0x7F, //FIFO1 register,     128 bytes
	0xC0, //FIFO2 register,     PFM[1:0]=[11]
	0x00, //FIFO register,		for fifo read/write
	0x00, //IDDATA register,	for idcode
	0x00, //RCOSC1 register,
	0x00, //RCOSC2 register,
	0x00, //RCOSC3 register,
	0x12, //CKO register,
	0x01, //GIO1 register
	0x21, //GIO2 register,
	0x05, //CLOCK register,
	0x09, //DATARATE register,  datarate=50Kbps
	0x50, //PLL1 register,
	0x9E, //PLL2 register, 		RFbase 2400MHz
	0x4B, //PLL3 register,
	0x00, //PLL4 register,
	0x02, //PLL5 register,
	0x16, //TX1 register,
	0x2B, //TX2 register,
	0x12, //DELAY1 register,
	0x00, //DELAY2 register,
	0x62, //RX register,
	0x80, //RXGAIN1 register,
	0x80, //RXGAIN2 register,
	0x00, //RXGAIN3 register,
	0x0A, //RXGAIN4 register,
	0x32, //RSSI register,
	0xC3, //ADC register,
	0x07, //CODE1 register,
	0x17, //CODE2 register,
	0x00, //CODE3 register,
	0x00, //IFCAL1 register,
	0x00, //IFCAL2 register,    only read
	0x00, //VCOCCAL register,
	0x00, //VCOCAL1 register,
	0x3B, //VCOCAL2 register,
	0x00, //BATTERY register,
	0x17, //TXTEST register,
	0x27, //RXDEM1 register,
	0x80, //RXDEM2 register,
	0x03, //CPC register,
	0x01, //CRYSTAL register,
	0x45, //PLLTEST register,
	0x18, //VCOTEST1 register,
	0x00, //VCOTEST2 register,
	0x01, //IFAT register,
	0x0F, //RSCALE register,
	0x00  //FILTERTEST
};

/************************************************************************
 **  A7105_WriteReg
 ************************************************************************/
void A7105_WriteReg(Uint8 addr, Uint8 dataByte) {
    uint8_t n_bytes;

    //NOP();
    MSPI_CS_SetLow();
    SPI_MOSI_buf [ 0 ] = addr;
    SPI_MOSI_buf [ 1 ] = dataByte;
    n_bytes = SPI1_Exchange8bitBuffer(SPI_MOSI_buf, 2, SPI_MISO_buf);
    MSPI_CS_SetHigh();
}

/************************************************************************
 **  Reset_RF
 ************************************************************************/
void A7105_Reset(void) {
    A7105_WriteReg(MODE_REG, 0x00); //reset RF chip
}

/************************************************************************
 **  ByteSend
 ************************************************************************/
void ByteSend(Uint8 src) {
    uint8_t n_bytes;

    MSPI_CS_SetLow();
    SPI_MOSI_buf [ 0 ] = src;
    n_bytes = SPI1_Exchange8bitBuffer(SPI_MOSI_buf, 1, NULL);
    MSPI_CS_SetHigh();
}

/************************************************************************
 **  ByteRead
 ************************************************************************/
Uint8 ByteRead(void) {
    Uint8 i, tmp;
    uint8_t n_bytes;

    MSPI_CS_SetLow();
    SPI_MOSI_buf [ 0 ] = DUMMY_DATA;
    n_bytes = SPI1_Exchange8bitBuffer(SPI_MOSI_buf, 1, SPI_MISO_buf);
    tmp = SPI_MISO_buf [ 0 ];
    MSPI_CS_SetHigh();
    return tmp;
}

/************************************************************************
**  A7105_ReadReg
************************************************************************/
Uint8 A7105_ReadReg(Uint8 addr)
{
    Uint8 i, tmp;
    uint8_t n_bytes;

    MSPI_CS_SetLow();
    SPI_MOSI_buf [ 0 ] = addr;
    n_bytes = SPI1_Exchange8bitBuffer(SPI_MOSI_buf, 1, SPI_MISO_buf);
    tmp = SPI_MISO_buf [ 0 ];
    MSPI_CS_SetHigh();
    return tmp;
}

/************************************************************************
 **  WriteID
 ************************************************************************/
void A7105_WriteID(void) {
    Uint8 i;
    Uint8 d1, d2, d3, d4;
    Uint8 addr;

    addr = IDCODE_REG; //send address 0x06, bit cmd=0, r/w=0
    ByteSend(addr);
    for (i = 0; i < 4; i++)
        ByteSend(ID_Tab[i]);

    //for check
    addr = IDCODE_REG | 0x40; //send address 0x06, bit cmd=0, r/w=1
    ByteSend(addr);
    d1 = d2 = d3 = d4 = 0;
    d1 = ByteRead();
    d2 = ByteRead();
    d3 = ByteRead();
    d4 = ByteRead();
}

/*********************************************************************
** A7105_Config
*********************************************************************/
void A7105_Config(void)
{
	Uint8 i;

    //0x00 mode register, for reset
    //0x05 fifo data register
    //0x06 id code register
    //0x23 IF calibration II, only read
    //0x32 filter test register

    for (i=0x01; i<=0x04; i++)
	    A7105_WriteReg(i, A7105Config[i]);

	for (i=0x07; i<=0x22; i++)
		A7105_WriteReg(i, A7105Config[i]);

	for (i=0x24; i<=0x31; i++)
		A7105_WriteReg(i, A7105Config[i]);
}

/************************************************************************
**  WaitBit_0
************************************************************************/
void WaitBit_0(Uint8 reg, Uint8 nbit)
{
    do {
    } while(A7105_ReadReg(reg) & nbit);
}

/*********************************************************************
** Err_State
*********************************************************************/
void Err_State(void)
{
    //ERR display
    //Error Proc...
    //...
}

/*********************************************************************
** SetCH
*********************************************************************/
void SetCH(Uint8 ch)
{
    //RF freq = RFbase + (CH_Step * ch)
	A7105_WriteReg(PLL1_REG, ch);
} 

/*********************************************************************
** SelVCOBand
*********************************************************************/
void SelVCOBand(Uint8 vb1, Uint8 vb2)
{
    Uint8 diff1,diff2;

	if (vb1>=4)
	    diff1 = vb1-4;
	else
	    diff1 = 4-vb1;

    if (vb2>=4)
        diff2 = vb2-4;
    else
        diff2 = 4-vb2;

    if (diff1 == diff2 || diff1 > diff2)
        A7105_WriteReg(VCOCAL1_REG, (vb1 | 0x08));//manual setting vb1 value
    else
        A7105_WriteReg(VCOCAL1_REG, (vb2 | 0x08));//manual setting vb2 value
}

/*********************************************************************
** calibration
*********************************************************************/
void A7105_Cal(void)
{
	Uint8 tmp;
	Uint8 fb,fbcf;
	Uint8 vb1,vbcf1,dvt1;
	Uint8 vb2,vbcf2,dvt2;

    StrobeCmd(CMD_STBY); //calibration @STB state

	//calibration IF procedure
	A7105_WriteReg(CALIBRATION_REG, 0x01);
	WaitBit_0(CALIBRATION_REG, 0x01);

	//for check
	tmp = A7105_ReadReg(IFCAL1_REG);
	fb = tmp & 0x0F;
	fbcf = (tmp >>4) & 0x01;

	if (fbcf ==1)
	{
	    Err_State();
	    while(1);
	}

	//calibration vco procedure
	A7105_WriteReg(VCOCCAL_REG, 0x13); //manual VCOC=3
	A7105_WriteReg(VCOCAL2_REG, 0x3B); //VTL=3, VTH=7

	SetCH(0); //setting 2400MHz
	A7105_WriteReg(CALIBRATION_REG, 0x02);
    WaitBit_0(CALIBRATION_REG, 0x02);

	tmp = A7105_ReadReg(VCOCAL1_REG);
	vb1 = tmp & 0x07;
	vbcf1 = (tmp >> 3) & 0x01;
	dvt1 = (tmp >> 4) & 0x03;

	SetCH(160); //setting 2480MHz
	A7105_WriteReg(CALIBRATION_REG, 0x02);
    WaitBit_0(CALIBRATION_REG, 0x02);

	tmp = A7105_ReadReg(VCOCAL1_REG);
	vb2 = tmp & 0x07;
	vbcf2 = (tmp >> 3) & 0x01;
	dvt2 = (tmp >> 4) & 0x03;

    SelVCOBand(vb1, vb2);

    if (vbcf1==1 && vbcf2==1)
    {
        Err_State();
	    while(1);
	}
}

/*********************************************************************
 ** initRF
 *********************************************************************/
void initRF(void) {
    //init io pin
    /*SCS = 1;
    SCK = 0;
    SDIO = 1;
    CKO = 1;
    GIO1 = 1;
    GIO2 = 1;

    A7105_Reset(); //reset A7105 RF chip
    A7105_WriteID(); //write ID code
    A7105_Config(); //config A7105 chip
    A7105_Cal(); //calibration IF,vco, */
    //uint8_t SPI1_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut);
    A7105_Reset(); //reset A7105 RF chip
    A7105_WriteID(); //write ID code
    A7105_Config(); //config A7105 chip
    A7105_Cal(); //calibration IF,vco
}