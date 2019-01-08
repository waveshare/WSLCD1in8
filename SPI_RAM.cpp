#include "SPI_RAM.h"
#include "mbed.h"
#include "MicroBitPin.h"

//SPI
SPI ram_spi(MOSI, MISO, SCK);
#define SPIRAM_SPI_Write_Byte(value) ram_spi.write(value)
#define SPIRAM_SPI_Read_Byte(value) ram_spi.write(value)

//SPIRAM
DigitalOut SPIRAM_CS(MICROBIT_PIN_P2);
#define SPIRAM_CS_0 SPIRAM_CS = 0
#define SPIRAM_CS_1 SPIRAM_CS = 1


/*********************************************
function:
    Initialization system
*********************************************/
void SPIRAM::SPIRAM_SPI_Init(void)
{
    ram_spi.format(8,0);
    ram_spi.frequency(9000000);
	SPIRAM_CS_1;
}


/*******************************************************************************
function:
        // Mode handling
*******************************************************************************/
void SPIRAM::SPIRAM_Set_Mode(BYTE mode)
{
    SPIRAM_CS_0;

    SPIRAM_SPI_Write_Byte(CMD_WRSR);
    SPIRAM_SPI_Write_Byte(mode);

    SPIRAM_CS_1;
}

/*******************************************************************************
function:
        // Write and read byte
*******************************************************************************/
BYTE SPIRAM::SPIRAM_RD_Byte(WORD Addr)
{
    BYTE RD_Byte;

    SPIRAM_CS_0;
    SPIRAM_SPI_Write_Byte(CMD_READ);

    SPIRAM_SPI_Write_Byte(0X00);
    SPIRAM_SPI_Write_Byte((BYTE)(Addr >> 8));
    SPIRAM_SPI_Write_Byte((BYTE)Addr);
    
    RD_Byte = SPIRAM_SPI_Read_Byte(0x00);
    SPIRAM_CS_1;

    return RD_Byte;
}

void SPIRAM::SPIRAM_WR_Byte(WORD Addr, const BYTE Data)
{
    // Write Addr,data
    SPIRAM_CS_0;

    SPIRAM_SPI_Write_Byte(CMD_WRITE);

    SPIRAM_SPI_Write_Byte(0X00);
    SPIRAM_SPI_Write_Byte((BYTE)(Addr >> 8));
    SPIRAM_SPI_Write_Byte((BYTE)Addr);
    
    SPIRAM_SPI_Write_Byte(Data);
    SPIRAM_CS_1;
}


/*******************************************************************************
function:
        // Page transfer functions. Bound to current page. Passing the boundary
        //  will wrap to the beginning
*******************************************************************************/
void SPIRAM::SPIRAM_RD_Page(WORD Addr, BYTE *pBuf)
{
    WORD i;

    // Write Addr, read data
    SPIRAM_CS_0;
    SPIRAM_SPI_Write_Byte(CMD_READ);
    
    SPIRAM_SPI_Write_Byte(0X00);
    SPIRAM_SPI_Write_Byte((BYTE)(Addr >> 8));
    SPIRAM_SPI_Write_Byte((BYTE)Addr);
    
    for (i = 0; i < 32; i++) {
        *pBuf = SPIRAM_SPI_Read_Byte(0x00);
        pBuf++;
    }
    SPIRAM_CS_1;
}

void SPIRAM::SPIRAM_WR_Page(WORD Addr, BYTE *pBuf)
{
    WORD i;

    // Write Addr, read data
    SPIRAM_CS_0;
    SPIRAM_SPI_Write_Byte(CMD_WRITE);
    
    SPIRAM_SPI_Write_Byte(0X00);
    SPIRAM_SPI_Write_Byte((BYTE)(Addr >> 8));
    SPIRAM_SPI_Write_Byte((BYTE)Addr);
    
    for (i = 0; i < 32; i++) {
        SPIRAM_SPI_Write_Byte(*pBuf);
        pBuf++;
    }
    SPIRAM_CS_1;
}

/*******************************************************************************
function:
        // Write and read Len
*******************************************************************************/
void SPIRAM::SPIRAM_RD_Stream(WORD Addr, BYTE *pBuf, unsigned long Len)
{
    WORD i;

    // Write Addr, read data
    SPIRAM_CS_0;
    SPIRAM_SPI_Write_Byte(CMD_READ);

    SPIRAM_SPI_Write_Byte(0X00);
    SPIRAM_SPI_Write_Byte((BYTE)(Addr >> 8));
    SPIRAM_SPI_Write_Byte((BYTE)Addr);
    
    for (i = 0; i < Len; i++) {
        *pBuf = SPIRAM_SPI_Read_Byte(0x00);
        pBuf++;
    }
    SPIRAM_CS_1;
}

void SPIRAM::SPIRAM_WR_Stream(WORD Addr, BYTE *pBuf, unsigned long Len)
{
    WORD i;

    // Write Addr, read data
    SPIRAM_CS_0;
    SPIRAM_SPI_Write_Byte(CMD_WRITE);
    
    SPIRAM_SPI_Write_Byte(0X00);
    SPIRAM_SPI_Write_Byte((BYTE)(Addr >> 8));
    SPIRAM_SPI_Write_Byte((BYTE)Addr);
    
    for (i = 0; i < Len; i++) {
        SPIRAM_SPI_Write_Byte(*pBuf);
        pBuf++;
    }
    SPIRAM_CS_1;
}
