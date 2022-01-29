#include <stdint.h>
#include <stdbool.h>
//#include "resource_table_empty.h"
#include <pru_cfg.h>
#include "prugpio.h"
#include "main.h"
#include "transfer.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

#define PRU0_DRAM       0x00000         // Offset to DRAM
volatile uint8_t *pru0_dram = (uint8_t*) (PRU0_DRAM + 0x200);
volatile uint32_t *shared_mem = (uint32_t*) 0x00010000;

extern my_delay_cycles(uint32_t);
void spi_ads8343(volatile uint8_t *in,volatile uint8_t *out,uint8_t size,volatile uint32_t *shm);

static inline void set_mosi(uint8_t val){
    if (val & 0x80)
        mosi_high();
    else
        mosi_low();

}

void __spi_ads8343(volatile uint8_t *dout,uint8_t *din,uint32_t size){
    uint8_t bytecount = 0;
    cs_low(ADC);
    while (bytecount < size)
       {
           uint8_t bitcount;
           uint8_t byte = dout[bytecount];
           sck_low();
           my_delay_cycles(10);
           for (bitcount = 0; bitcount < 8; bitcount++, byte <<= 1)
           {
               set_mosi(byte);
               my_delay_cycles(10);
               sck_high();
               my_delay_cycles(20);
               sck_low();
               my_delay_cycles(10);
           }
           mosi_low();
           __delay_cycles(40);
           bytecount++;

       }

    cs_high(ADC);
}

void spi_dac8564(volatile uint8_t *dout,uint8_t *din,uint32_t size){


}

void xfer(volatile uint8_t *dout,uint8_t *din,uint32_t size,uint8_t mode){
    uint8_t bytecount = 0;

    cs_low(ADC);

    while (bytecount < size)
    {
        uint8_t bitcount;
        uint8_t byte = dout[bytecount];
        if(CPOL(mode) == 1)
            sck_high();
        else
            sck_low();

        my_delay_cycles(10);

        for (bitcount = 0; bitcount < 8; bitcount++, byte <<= 1)
        {
            if(CPHA(mode) == 0)
                set_mosi(byte);
            if(CPOL(mode) == 1)
                sck_low();
            else
                sck_high();
            my_delay_cycles(15);
            if(CPHA(mode) == 1)
                set_mosi(byte);
            if(CPOL(mode) == 1)
                sck_high();
            else
                sck_low();
            my_delay_cycles(2);

        }


        my_delay_cycles(10);
        bytecount++;

    }

    cs_high(ADC);

}

void spi_ads8343(volatile uint8_t *in,volatile uint8_t *out,uint8_t size,volatile uint32_t *shared_mem){
    uint8_t i = 0;
    while(i < size){
        int32_t bits = 7;
        uint8_t c = in[i];
        out[i] = 0;
        //while(shared_mem[1]);

        shared_mem[0] = 1;
        while(bits >= 0){
            if(c & 0x80)
                __R30 |= MOSI;
            else
                __R30 &= ~MOSI;
            c <<= 1;
            while(!shared_mem[1]);
            while(shared_mem[1]);
            bits--;
            out[i] |= ((__R30 & MISO)) << bits;

        }
        shared_mem[0] = 0;
        __R30 &= ~MOSI;
        i++;
    }


}

inline void read8bit(){
    uint8_t SPICount;                               // Counter used to clock out the data
    uint8_t SPIData = 0x00;        // Define a data structure for the SPI data.

          __R30 |= ADCCS;                                       // Make sure we start with /CS high
          __R30 &= ~SCK;                                        // and CK low
          __R30 &= ~ADCCS;                                     // Set /CS low to start the SPI cycle 25nS
                                                                // Although SPIData could be implemented as an "int", resulting in one
                                                                // loop, the routines run faster when two loops are implemented with
                                                                // SPIData implemented as two "char"s.

          for (SPICount = 0; SPICount < 8; SPICount++)          // Prepare to clock out the Address byte
          {
            my_delay_cycles(5);
            if (SPIData & 0x80)                                 // Check for a 1
              __R30 |= MOSI;                                     // and set the MOSI line appropriately
            else
              __R30 &= ~MOSI;
            __R30 |= SCK;                                         // Toggle the clock line
            my_delay_cycles(25);
            __R30 &= ~SCK;
            my_delay_cycles(20);
            SPIData <<= 1;                                      // Rotate to get the next bit

          }                                                     // and loop back to send the next bit
                                                                // Repeat for the Data byte
    //      SPIData = regData;                                    // Preload the data to be sent with Data
    //      for (SPICount = 0; SPICount < 8; SPICount++)          // Prepare to clock out the Data
    //      {
    //        if (SPIData & 0x80)
    //          SPI_MOSI = 1;
    //        else
    //          SPI_MOSI = 0;
    //        SPI_CK = 1;
    //        SPI_CK = 0;
    //        SPIData <<= 1;
    //      }
          __R30 |= ADCCS;
          __R30 &= ~MOSI;


}

inline void write8bit(){
    uint8_t SPICount;                               // Counter used to clock out the data
    uint8_t SPIData = SBIT | PD1 | A0 | SGL;        // Define a data structure for the SPI data.

      __R30 |= ADCCS;                                       // Make sure we start with /CS high
      __R30 &= ~SCK;                                        // and CK low
      __R30 &= ~ADCCS;                                     // Set /CS low to start the SPI cycle 25nS
                                                            // Although SPIData could be implemented as an "int", resulting in one
                                                            // loop, the routines run faster when two loops are implemented with
                                                            // SPIData implemented as two "char"s.
      for (SPICount = 0; SPICount < 8; SPICount++)          // Prepare to clock out the Address byte
      {
        my_delay_cycles(5);
        if (SPIData & 0x80)                                 // Check for a 1
          __R30 |= MOSI;                                     // and set the MOSI line appropriately
        else
          __R30 &= ~MOSI;
        __R30 |= SCK;                                         // Toggle the clock line
        my_delay_cycles(25);
        __R30 &= ~SCK;
        my_delay_cycles(20);
        SPIData <<= 1;                                      // Rotate to get the next bit

      }                                                     // and loop back to send the next bit
                                                            // Repeat for the Data byte
//      SPIData = regData;                                    // Preload the data to be sent with Data
//      for (SPICount = 0; SPICount < 8; SPICount++)          // Prepare to clock out the Data
//      {
//        if (SPIData & 0x80)
//          SPI_MOSI = 1;
//        else
//          SPI_MOSI = 0;
//        SPI_CK = 1;
//        SPI_CK = 0;
//        SPIData <<= 1;
//      }
      __R30 |= ADCCS;
      __R30 &= ~MOSI;
}

inline void read16bit(){
    uint8_t SPICount;                               // Counter used to clock out the data
    uint8_t SPIData = SBIT | PD1 | A0 | SGL;

      __R30 |= ADCCS;
      __R30 &= ~SCK;
      __R30 &= ~ADCCS;
      my_delay_cycles(20);
      for (SPICount = 0; SPICount < 8; SPICount++)
      {
          if (SPIData & 0x80)
            __R30 |= MOSI;
          else
            __R30 &= ~MOSI;
          __R30 |= SCK;
          my_delay_cycles(20);
          __R30 &= ~SCK;
          my_delay_cycles(20);
          SPIData <<= 1;
      }
      __R30 |= ADCCS;
      __R30 &= ~MOSI;
      //my_delay_cycles(40);
      SPIData = 0;
      while((__R30 & ADCBUSY));
      __R30 |= ADCCS;
     __R30 &= ~SCK;
     __R30 &= ~ADCCS;
      my_delay_cycles(20);
      for (SPICount = 0; SPICount < 16; SPICount++)
      {
        SPIData <<=1;
        __R30 |= SCK;
        my_delay_cycles(20);
        SPIData += SPI_MISO;
        __R30 &= ~SCK;
        my_delay_cycles(20);
      }

      __R30 |= ADCCS;
      __R30 &= ~MOSI;
      my_delay_cycles(20);

}

int __main(void)
{
    uint8_t i = 0;
    pru0_dram[0] = 'a';
    pru0_dram[1] = 'b';
    pru0_dram[2] = 'c';
    pru0_dram[3] = 'd';

    pru0_dram[4] = 0;

    // MOSI | MISO | SCK | CS;
    __R30 = 0x00000000;
    __R31 = 0x00000000;
    //Set the CFG Register to direct output instead of serial output
    CT_CFG.GPCFG0 = 0;
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

//    while(i < 4){
//        int32_t bits = 7;
//        uint8_t c = pru0_dram[i];
//        pru0_dram[i + 4] = 0;
//        //while(shared_mem[1]);
//        __R30 &= ~ADCCS;
//       shared_mem[0] = 1;
//        while(bits >= 0){
//            if(c & 0x80)
//                __R30 |= MOSI;
//            else
//                __R30 &= ~MOSI;
//            c <<= 1;
//            while(!shared_mem[1]);
//            while(shared_mem[1]);
//            bits--;
//            pru0_dram[i + 4] |= ((__R30 & MISO)) << bits;
//
//        }
//        shared_mem[0] = 0;
//        __R30 &= ~MOSI;
//        __R30 |= ADCCS;
//        i++;
//        if(i == 4)
//            i = 0;
//    }
   pru0_dram[0] = SBIT | PD1 | A0 | SGL;
   pru0_dram[1] = 0x00;
   pru0_dram[2] = 0xFF;
   pru0_dram[3] = 0xFF;
   shared_mem[0] = 0;
    while (1)
    {
      __spi_ads8343(&pru0_dram[0],&pru0_dram[1],1);
      while(__R30 & ADCBUSY);
      __spi_ads8343(&pru0_dram[2],&pru0_dram[4],2);
    }

    return 0;

}
