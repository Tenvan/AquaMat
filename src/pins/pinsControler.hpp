#include <Arduino.h>

#define A0 GPIO_NUM_2
#define A1 GPIO_NUM_4
#define A2 GPIO_NUM_35
#define A3 GPIO_NUM_34
#define A4 GPIO_NUM_36
#define A5 GPIO_NUM_39

#define D0 GPIO_NUM_2
#define D1 GPIO_NUM_1
#define D2 GPIO_NUM_26
#define D3 GPIO_NUM_25
#define D4 GPIO_NUM_17
#define D5 GPIO_NUM_16
#define D6 GPIO_NUM_27
#define D7 GPIO_NUM_14
#define D8 GPIO_NUM_12
#define D9 GPIO_NUM_13
#define D10 GPIO_NUM_5
#define D11 GPIO_NUM_23
#define D12 GPIO_NUM_19
#define D13 GPIO_NUM_18

void pinsSetup();

void pinsLoop();

int getPumpen();

double getTemperatur();
