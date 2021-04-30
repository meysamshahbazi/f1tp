#include "stm32f1xx_hal.h"
#define ERR_RANGE 100 //��Χ  // 50
#define READ_TIMES 16 //��ȡ���� // 15
#define LOST_VAL 4	  //����ֵ
#define NUM_READ 16
#define CMD_RDX 	0xD0
#define CMD_RDY		0x90
#define CMD_RDZ1	0xB0	
#define CMD_RDZ2	0xF0

#define  tp_pres_thr 1000

#define tp_x_min			108
#define tp_x_max			1951
#define tp_y_min			154
#define tp_y_max			1821

#define TP_CS_GPIO_Port GPIOD
#define TP_CS_Pin GPIO_PIN_13

uint8_t Read_ADS2(uint16_t *x,uint16_t *y);
uint8_t Read_ADS(uint16_t *x,uint16_t *y);
uint16_t ADS_Read_XY(uint8_t xy);
uint16_t ADS_Read_AD(uint8_t CMD);



extern SPI_HandleTypeDef hspi2;
void Init_TOUCH(void);
uint8_t tp_read(uint16_t *x,uint16_t *y);


uint8_t tp_read2(uint16_t *x,uint16_t *y);


uint8_t tp_read3(uint16_t *x,uint16_t *y);

