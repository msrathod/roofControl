
#include <O2gpio.h>

uint16_t ctrlOffset;
uint16_t dataOffset;
uint16_t dataSetOffset;
uint16_t dataClrOffset;

uint32_t *baseAddress;

static uint8_t dbgLevel = 0;

/* LOCAL FUNCTIONS*/
static int _SetupAddress(uint32_t blockBaseAddr)
{
	int  m_mfd;
	if ((m_mfd = open("/dev/mem", O_RDWR)) < 0){
		perror("Error: Failed to open /dev/mem");
		return EXIT_FAILURE;
	}
	baseAddress = (uint32_t *)mmap(0, 1024, PROT_READ | PROT_WRITE, 
											MAP_FILE | MAP_SHARED, 
											m_mfd, blockBaseAddr );
	close(m_mfd);
	if (baseAddress == MAP_FAILED){
		perror("Error: Memory map failed.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

static void _WriteReg(uint16_t registerOffset, uint32_t value)
{
	*(baseAddress + registerOffset) = value;
}

static uint32_t _ReadReg(uint16_t registerOffset)
{
	return *(baseAddress + registerOffset);
}

static void _GetOffset4pin(uint8_t gp_pin)
{
	switch (gp_pin/32){
		case 0:
		ctrlOffset		= REGISTER_CTRL0_OFFSET;
		dataOffset 		= REGISTER_DATA0_OFFSET;
		dataSetOffset 	= REGISTER_DSET0_OFFSET;
		dataClrOffset	= REGISTER_DCLR0_OFFSET;
		break;

		case 1:
		ctrlOffset		= REGISTER_CTRL1_OFFSET;
		dataOffset 		= REGISTER_DATA1_OFFSET;
		dataSetOffset 	= REGISTER_DSET1_OFFSET;
		dataClrOffset	= REGISTER_DCLR1_OFFSET;
		break;

		default:
		ctrlOffset		= REGISTER_CTRL2_OFFSET;
		dataOffset 		= REGISTER_DATA2_OFFSET;
		dataSetOffset 	= REGISTER_DSET2_OFFSET;
		dataClrOffset	= REGISTER_DCLR2_OFFSET;
	}

}

/* PUBLIC FUNCTIONS*/
int O2gpio_Init()
{
	uint8_t status = _SetupAddress(REG_BLOCK_ADDR);
	return(status);
}

int O2gpio_SetDir(uint8_t pinNum, uint8_t direction)
{
	_GetOffset4pin(pinNum);
	pinNum %= 32;

	// read the current input and output settings
	uint32_t regVal = _ReadReg(ctrlOffset);
	// set the OE for this pin
	switch (direction){
		case O2_INPUT:
		regVal &= ~((uint32_t) 0x1 <<  pinNum);
		break;
		default:
		regVal |= (uint32_t) 0x1 << pinNum;
		break;
	}
   	// write the new register value
	_WriteReg(ctrlOffset, regVal);

	return (EXIT_SUCCESS);
}

int O2gpio_GetDir(uint8_t pinNum, uint8_t* pdirection)
{
	_GetOffset4pin(pinNum);
	pinNum %= 32;

	//read the current input and output settings
	uint32_t regVal = _ReadReg(ctrlOffset);
	*pdirection = ((regVal >> pinNum) & 0x1);

	return (EXIT_SUCCESS);
}

int O2gpio_Write(uint8_t pinNum, uint8_t value)
{
	uint16_t regAddress;
	_GetOffset4pin(pinNum);
	pinNum %= 32;

	if (value) {
		// write to the set register
		regAddress 	= dataSetOffset;
	}
	else {
		// write to the clear register
		regAddress 	= dataClrOffset;
	}
	// put the desired pin value into the register 
	uint32_t regVal = ((uint32_t) 0x1 << pinNum);
	// write to the appropriate register
	_WriteReg(regAddress, regVal);

	return (EXIT_SUCCESS);
}

int O2gpio_Read(uint8_t pinNum, uint8_t* pvalue)
{
	_GetOffset4pin(pinNum);
	pinNum %= 32;
	// read the current value of all pins in the group
	uint32_t regVal = _ReadReg(dataOffset);
	// find the value of the specified pin
	*pvalue = (uint8_t)((regVal >> pinNum) & 0x1);

	return (EXIT_SUCCESS);
}