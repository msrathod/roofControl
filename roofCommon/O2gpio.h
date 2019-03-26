
#ifndef O2GPIO_H
#define O2GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum GpioPinDirection {
    O2_INPUT = 0,
    O2_OUTPUT = 1,
};

static const int REG_BLOCK_ADDR = 0x10000000;

//DIRECTION CONTROL REGISTERS
//GPIO_CTRL_0 10000600(Directions for GPIO0-GPIO31)
static const int REGISTER_CTRL0_OFFSET = 384;
//GPIO_CTRL_1 10000604(Directions for GPIO32-GPIO63)
static const int REGISTER_CTRL1_OFFSET = 385;
//GPIO_CTRL_2 10000608(Directions for GPIO64-GPIO95)
static const int REGISTER_CTRL2_OFFSET = 386;

//DATA REGISTERS: STATES OF GPIOS 
//GPIO_DATA_0 10000620(GPIO0-31)
static const int REGISTER_DATA0_OFFSET = 392;
//GPIO_DATA_1 10000624(GPIO32-63)
static const int REGISTER_DATA1_OFFSET = 393;
//GPIO_DATA_2 10000628(GPIO64-95)
static const int REGISTER_DATA2_OFFSET = 394;

//DATA SET REGISTERS: SET STATES OF GPIO_DATA_x registers
//GPIO_DSET_0 10000630(GPIO0-31)
static const int REGISTER_DSET0_OFFSET = 396;
//GPIO_DSET_1 10000634(GPIO32-63)
static const int REGISTER_DSET1_OFFSET = 397;
//GPIO_DSET_2 10000638(GPIO64-95)
static const int REGISTER_DSET2_OFFSET = 398;

//DATA CLEAR REGISTERS: CLEAR BITS OF GPIO_DATA_x registers
//GPIO_DCLR_0 10000640(GPIO0-31)
static const int REGISTER_DCLR0_OFFSET = 400;
//GPIO_DCLR_1 10000644(GPIO32-63)
static const int REGISTER_DCLR1_OFFSET = 401;
//GPIO_DCLR_2 10000648(GPIO64-95)
static const int REGISTER_DCLR2_OFFSET = 402;

static uint16_t ctrlOffset;
static uint16_t dataOffset;
static uint16_t dataSetOffset;
static uint16_t dataClrOffset;

static uint32_t *baseAddress;

/* LOCAL FUNCTIONS*/
static int _SetupAddress(uint32_t blockBaseAddr);
static void _WriteReg(uint16_t registerOffset, uint32_t value);
static uint32_t _ReadReg(uint16_t registerOffset);
static void _GetOffset4pin(uint8_t gp_pin);

/* PUBLIC FUNCTIONS */
int O2gpio_Init(void);
int O2gpio_SetDir(uint8_t pinNum, uint8_t dir);
int O2gpio_GetDir(uint8_t pinNum, uint8_t *dir);
int O2gpio_Write(uint8_t pinNum, uint8_t val);
int O2gpio_Read(uint8_t pinNum, uint8_t *val);

#ifdef __cplusplus
}
#endif
#endif //O2GPIO_H