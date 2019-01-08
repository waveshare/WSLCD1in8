#ifndef __SPI_RAM_H_
#define __SPI_RAM_H_

//data
#define BYTE   unsigned char
#define WORD   unsigned short

// SRAM opcodes
#define CMD_WREN  0x06
#define CMD_WRDI  0x04
#define CMD_RDSR  0x05
#define CMD_WRSR  0x01
#define CMD_READ  0x03
#define CMD_WRITE 0x02

// SRAM modes
#define BYTE_MODE   0x00
#define PAGE_MODE   0x80
#define STREAM_MODE 0x40


class SPIRAM{
public:    
    void SPIRAM_SPI_Init(void);
    
    void SPIRAM_Set_Mode(BYTE mode);

    BYTE SPIRAM_RD_Byte(WORD Addr);
    void SPIRAM_WR_Byte(WORD Addr, BYTE Data);
    void SPIRAM_RD_Page(WORD Addr, BYTE *pBuf);
    void SPIRAM_WR_Page(WORD Addr, BYTE *pBuf);
    void SPIRAM_RD_Stream(WORD Addr, BYTE *pBuf, unsigned long Len);
    void SPIRAM_WR_Stream(WORD Addr, BYTE *pBuf, unsigned long Len);
};
#endif
