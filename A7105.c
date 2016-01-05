#include "A7105reg.h"
#include "define.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/pin_manager.h"
#include <xc.h>
#include "mcc_generated_files/mcc.h"

/*********************************************************************
**  Global Variable Declaration
*********************************************************************/
Uint8 Seq = 0;
Uint16 RxCnt = 0;
Uint32 Err_ByteCnt = 0;
Uint32 Err_BitCnt = 0;
Uint8 Err_HopCnt = 0;
Uint16 AFCBuf [ 12 ];
volatile uint8_t A7105_timer;
Uint8 tmpbuf[256];

const Uint8 ID_Tab[4] = {0x54, 0x75, 0xC5, 0x2A}; //ID code
const Uint8 BitCount_Tab[16] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
const Uint8 PN9_Tab[]=
{   0xFF,0x83,0xDF,0x17,0x32,0x09,0x4E,0xD1,
    0xE7,0xCD,0x8A,0x91,0xC6,0xD5,0xC4,0xC4,
    0x40,0x21,0x18,0x4E,0x55,0x86,0xF4,0xDC,
    0x8A,0x15,0xA7,0xEC,0x92,0xDF,0x93,0x53,
    0x30,0x18,0xCA,0x34,0xBF,0xA2,0xC7,0x59,
    0x67,0x8F,0xBA,0x0D,0x6D,0xD8,0x2D,0x7D,
    0x54,0x0A,0x57,0x97,0x70,0x39,0xD2,0x7A,
    0xEA,0x24,0x33,0x85,0xED,0x9A,0x1D,0xE0
};	// This table are 64bytes PN9 pseudo random code.

const Uint8 HopTab [ ] =
{
	20, //2410
	40, //2420
	80, //2440
	120, //2460
	160, //2480
};

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

    //MSPI_CS_SetLow();
    SPI_MOSI_buf [ 0 ] = src;
    n_bytes = SPI1_Exchange8bitBuffer(SPI_MOSI_buf, 1, NULL);
    //MSPI_CS_SetHigh();
}

/************************************************************************
 **  ByteRead
 ************************************************************************/
Uint8 ByteRead(void) {
    Uint8 i, tmp;
    uint8_t n_bytes;

    //MSPI_CS_SetLow();
    SPI_MOSI_buf [ 0 ] = DUMMY_DATA;
    n_bytes = SPI1_Exchange8bitBuffer(SPI_MOSI_buf, 1, SPI_MISO_buf);
    tmp = SPI_MISO_buf [ 0 ];
    //MSPI_CS_SetHigh();
    return tmp;
}

/************************************************************************
**  A7105_ReadReg
************************************************************************/
Uint8 A7105_ReadReg(Uint8 addr)
{
    Uint8 tmp;
    uint8_t n_bytes;

    MSPI_CS_SetLow();
    SPI_MOSI_buf [ 0 ] = addr | 0x40;
    SPI_MOSI_buf [ 1 ] = DUMMY_DATA;
    n_bytes = SPI1_Exchange8bitBuffer(SPI_MOSI_buf, 2, SPI_MISO_buf);
    tmp = SPI_MISO_buf [ 1 ];
    MSPI_CS_SetHigh();
    return tmp;
}

/************************************************************************
 **  WriteID
 * return
 *   false: if check ID failed
 ************************************************************************/
bool A7105_WriteID(void) {
    Uint8 i;
    Uint8 d1, d2, d3, d4;
    Uint8 addr;

    addr = IDCODE_REG; //send address 0x06, bit cmd=0, r/w=0
    MSPI_CS_SetLow();
    ByteSend(addr);
    for (i = 0; i < 4; i++)
        ByteSend(ID_Tab[i]);
    MSPI_CS_SetHigh();

    //for check
    addr = IDCODE_REG | 0x40; //send address 0x06, bit cmd=0, r/w=1
    MSPI_CS_SetLow();
    ByteSend(addr);
    d1 = d2 = d3 = d4 = 0;
    d1 = ByteRead();
    d2 = ByteRead();
    d3 = ByteRead();
    d4 = ByteRead();
    MSPI_CS_SetHigh();
    if ( d1 != ID_Tab[ 0 ]  || d2 != ID_Tab[ 1 ] || d3 != ID_Tab[ 2 ] || d4 != ID_Tab[ 3 ] )
        return false;
    return true;
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

/*********************************************************************
** Swap
*********************************************************************/
void Swap(Uint8 idx1, Uint8 idx2)
{
    Uint16 tmp;

    tmp= AFCBuf[idx1];
    AFCBuf[idx1] = AFCBuf[idx2];
    AFCBuf[idx2]= tmp;
}

/*********************************************************************
** FrequencyCal
*********************************************************************/
void FrequencyCal(void)
{
    Uint8 tmp_h, tmp_l;
    Uint32 tmp;
    Uint16 tmp1,tmp2;
	Uint8 i,j;
    Uint8 cnt;
    Uint8 flag_1n,flag_2n;
    Uint8 pll3,pll4,pll5;
    Uint16 offsetValue,pll;
    Uint8 sign;

    //Step1. enable AFC bit
    A7105_WriteReg(RX_REG, 0x72);

    //Step2. receive data with sync
    cnt=0;
    while(1)
    {
        StrobeCmd(CMD_RX);
        while(GPIO1);

        cnt++;
        if (cnt>3)//ignore AFCcnt 1~3
        {
            tmp_h = A7105_ReadReg(PLL4_REG) & 0x7F;
            tmp_l = A7105_ReadReg(PLL5_REG);
            tmp1 = (Uint16)tmp_h * 256 + (Uint16)tmp_l;
            AFCBuf[cnt-4]=tmp1;
        }

        if (cnt>=15)
            break;

        __delay_ms (1);
    }

    //Step3. bubble sort
    for(i = 0; i < 12-1; i++)
    {
        for(j = i+1; j < 12; j++)
        {
            if(AFCBuf[i] & 0x4000)
            {
                flag_1n=1;
                tmp1= ~AFCBuf[i] & 0x7FFF;
            }
            else
            {
                flag_1n=0;
                tmp1= AFCBuf[i];
            }

            if(AFCBuf[j] & 0x4000)
            {
                flag_2n=1;
                tmp2= ~AFCBuf[j] & 0x7FFF;
            }
            else
            {
                flag_2n=0;
                tmp2= AFCBuf[j];
            }

            if (flag_1n==0 && flag_2n==0)
            {
                if (tmp1 > tmp2)
                    Swap(i, j);
            }

            if(flag_1n==1 && flag_2n==1)
            {
                if (tmp1 < tmp2)
                    Swap(i, j);
            }

            if (flag_1n==0 && flag_2n==1)
                Swap(i, j);
        }
    }

    //Step4. ignore AFCBuf[0~1], AFCBuf[10~11], average AFCBuf[2~9]
    //Plus, sign operation
    tmp=0;
    for(i=2; i<=9; i++)
    {
        if (AFCBuf[i] & 0x4000)
            tmp = tmp + (AFCBuf[i] & 0x3FFF);
        else
            tmp = tmp + AFCBuf[i] + 0x4000;
    }

    tmp = tmp /8;
    if (tmp & 0x4000)
        offsetValue = tmp & 0x3FFF;
    else
        offsetValue = tmp | 0x4000;

    //Step5. disable AFC bit
    A7105_WriteReg(RX_REG, 0x62);

    //Step6. update PLL register
    pll3 = A7105Config[PLL3_REG];
    pll4 = A7105Config[PLL4_REG];
    pll5 = A7105Config[PLL5_REG];

    pll = (Uint16)pll4*8 + (Uint16)pll5;

    if (offsetValue & 0x4000)
    {
        sign=1;
        offsetValue = (~offsetValue + 1) & 0x7FFF;
    }
    else
    {
        sign=0;
    }

    if (sign)
    {
    	pll = pll - offsetValue;
    	if (STATUSbits.C)
    	    A7105_WriteReg(PLL3_REG, pll3-1);

        A7105_WriteReg(PLL4_REG, pll>>8);
        A7105_WriteReg(PLL5_REG, pll);
    }
    else
    {
        pll = pll + offsetValue;
    	if (STATUSbits.C)
            A7105_WriteReg(PLL3_REG, pll3+1);

        A7105_WriteReg(PLL4_REG, pll>>8);
        A7105_WriteReg(PLL5_REG, pll);
    }
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
** A7105_WriteFIFO
*********************************************************************/
void A7105_WriteFIFO(void)
{
	Uint8 i;
	Uint8 cmd;

	cmd = FIFO_REG; //send address 0x05, bit cmd=0, r/w=0
    MSPI_CS_SetLow ( );
	ByteSend(cmd);
	for(i=0; i <64; i++)
		ByteSend(PN9_Tab[i]);
	MSPI_CS_SetHigh ( );
}

/*********************************************************************
** RxPacket
*********************************************************************/
void RxPacket(void)
{
    Uint8 i;
    Uint8 recv;
    Uint8 tmp;
	Uint8 cmd;

	RxCnt++;
	cmd = FIFO_REG | 0x40; //address 0x05, bit cmd=0 r/w=1

	MSPI_CS_SetLow ( );
	ByteSend ( cmd );
	for(i=0; i <64; i++)
	{
		tmpbuf [ i ] = recv = ByteRead ( );
		if((recv ^ PN9_Tab[i])!=0)
        {
            tmp = recv ^ PN9_Tab[i];
            Err_BitCnt += (BitCount_Tab[tmp>>4] + BitCount_Tab[tmp & 0x0F]);
        }
    }
	MSPI_CS_SetHigh ( );

	/*report error bits every received 500 packets*/
	if ( ! ( RxCnt % 500 ) ) {
		RxCnt = RxCnt;
		Err_BitCnt = Err_BitCnt;
	}
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

	//Seq = 0;
}

bool A7105_SpiTest ( void )
{
    bool SpiRW_test_status = false;
    Uint8 tmp;
    Uint8 d1, d2, d3, d4;
    Uint8 addr;
#if 0
    A7105_Reset(); //reset A7105 RF chip
    //spi 3-wire configure R8/NC, R9/0ohm; 4-wire configure R8/0ohm, R9/NC
//#ifdef SPI_4_WIRE
    A7105_WriteReg ( GPIO1_REG, 0x11 );
//#endif
    if ( A7105_WriteID ( ))
       SpiRW_test_status = true; 
#else
    A7105_Reset();
	tmp = A7105_ReadReg ( RSCALE_REG );
    A7105_WriteReg ( RSCALE_REG, 0x11 );
    tmp = A7105_ReadReg ( RSCALE_REG );
    
    addr = IDCODE_REG | 0x40; //send address 0x06, bit cmd=0, r/w=1
    MSPI_CS_SetLow();
    ByteSend(addr);
    d1 = d2 = d3 = d4 = 0;
    d1 = ByteRead();
    d2 = ByteRead();
    d3 = ByteRead();
    d4 = ByteRead();
    MSPI_CS_SetHigh();
    
    addr = GPIO1_REG;
    MSPI_CS_SetLow();
    ByteSend(addr);
    ByteSend(0x11);
    MSPI_CS_SetHigh();
    
    addr = GPIO1_REG | 0x40; //send address 0x06, bit cmd=0, r/w=1
    MSPI_CS_SetLow();
    ByteSend(addr);
    d1 = d2 = d3 = d4 = 0;
    d1 = ByteRead();
    //d2 = ByteRead();
    //d3 = ByteRead();
    //d4 = ByteRead();
    MSPI_CS_SetHigh();
#endif
}

void A7105_transmit_master ( void )
{
	initRF ( );
	StrobeCmd ( CMD_STBY );
	A7105_WriteFIFO ( ); //write data to fifo

	while ( 1 ) {
	//Tx time-slot
	A7105_timer = 0;
	while ( A7105_timer <= 2 ); //wait until timer = 2
	SetCH ( HopTab [ Seq ] );
	StrobeCmd ( CMD_TX ); //entry tx & transmit
	while ( GPIO1 ); //wait transmit completed

	//Rx time-slot
	while ( A7105_timer  <= 12 ); //wait until timer = 12
	SetCH ( HopTab [ Seq ] - 1 );
	StrobeCmd ( CMD_RX );
	while ( GPIO1 && A7105_timer  <= 14 );

	if ( A7105_timer > 14 ) {
		//timeout
		StrobeCmd ( CMD_PLL );
	}
	else {
		//data procedure
		RxPacket ( );
	}

	Seq++;
	if ( Seq > 4 )
		Seq = 0;
	}
}

void A7105_transmit_slave ( void )
{
	initRF ( );

	//clear variable
	RxCnt = 0;
	Err_ByteCnt = 0;
	Err_BitCnt = 0;
	Err_HopCnt = 0;

	//Frequency calibration with sync data
	//at default link channel
	SetCH ( HopTab [ 2 ] - 1 );
	FrequencyCal ( );
	StrobeCmd ( CMD_STBY );

	while ( 1 ) {
	//Rx time-slot
	A7105_timer = 0;
	while ( A7105_timer > 0 );
	SetCH ( HopTab [ Seq ] - 1 );
	StrobeCmd ( CMD_RX );
	while ( GPIO1 && A7105_timer <= 3 ); // wait receive complete
	if ( A7105_timer > 3 )
	{
		StrobeCmd ( CMD_PLL );

		Seq++;
		if ( Seq > 4 )
			Seq = 0;

		Err_HopCnt++;
		if ( Err_HopCnt > 5 )
		{
			Seq = 0;
			Err_HopCnt = 0;

			SetCH ( HopTab [ Seq ] - 1 );
			StrobeCmd ( CMD_RX );

			while ( 1 )
			{
				if ( GPIO1 == 0)
					break;
			}
		}
		else
			continue;
	}

	RxPacket ( );

	A7105_timer = 2; //reSync
	//Tx time-slot
	while ( A7105_timer <= 12 );
	SetCH ( HopTab [ Seq ] );
	StrobeCmd ( CMD_TX );
	while ( GPIO1 );

	Seq++;
	if ( Seq > 4 )
		Seq = 0;
	}
}