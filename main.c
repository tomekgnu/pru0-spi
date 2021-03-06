#include <stdint.h>
#include <stdbool.h>
#include "resource_table_empty.h"
#include <pru_cfg.h>
#include "prugpio.h"
#include "main.h"
#define ADC_SAMPLE     shared_mem[0]
#define DAC_SAMPLE     shared_mem[1]

volatile register uint32_t __R30;
volatile register uint32_t __R31;

volatile int16_t *shared_mem = (int16_t *) 0x00010000;
volatile uint16_t *info = (uint16_t *)(0x00010000 + 2);

extern my_delay_cycles(uint32_t);


inline uint8_t send8bit(uint8_t data){
    uint8_t i;
    uint8_t out = 0;


    mosi_low();

    for(i = 0; i < 8; i++){
        set_mosi(data << i);
        my_delay_cycles(6);
        sck_high();
        my_delay_cycles(12);
        sck_low();
        out += (__R31 & MISO);
        out <<= 1;
        my_delay_cycles(6);
    }

    mosi_low();


    return out;

}

inline int16_t readADC(){
    uint16_t result;
        uint8_t ADCData[3] = {0,0,0};

        cs_low(ADC);
        my_delay_cycles(4);
        ADCData[0] = send8bit(0);
        ADCData[1] = send8bit(0);
        ADCData[2] = send8bit(0x96);
        my_delay_cycles(4);
        cs_high(ADC);
        my_delay_cycles(4);


        ADCData[0] <<= 1;
        if(ADCData[1] & 0x80)
            ADCData[0] |= 0x01;
        ADCData[1] <<= 1;
        if(ADCData[2] & 0x80)
            ADCData[1] |= 0x01;

        result = ADCData[0];
        result <<= 8;
        result += ADCData[1];

        return result;
}

inline void writeDAC(int16_t result){
    uint8_t DACData[3] = {0x10,0,0};

    if((int16_t)result < 0)
        result &= 0x7FFF;
    else
        result |= 0x8000;

    dacld_low();

    DACData[1] = (uint8_t)(result >> 8);
    DACData[2] = (uint8_t)(result & 0x00FF);

    cs_low(DAC);

    my_delay_cycles(1);
    send8bit(0x10);
    send8bit(DACData[1]);
    send8bit(DACData[2]);

    cs_high(DAC);

}

int main(void){

    int16_t sample;
    info[3] = 0;

    while(1){

            if(info[AUDIO_CLOCK_STATE] == 1 /*info[AUDIO_CLOCK_STATE] == 1*/){
                ADC_SAMPLE = readADC();
                while(info[AUDIO_CLOCK_STATE] == 1)
                    continue;
            }
            else {
                ADC_SAMPLE = readADC();
                while(info[AUDIO_CLOCK_STATE] == 0)
                   continue;

            }

            if(info[DAC_SAMPLE_READY] == 1)
                writeDAC(DAC_SAMPLE);

    }

    return 0;

}
