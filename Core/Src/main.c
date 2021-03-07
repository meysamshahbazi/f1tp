/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1963_headerfile.h"
#include "tp.h"
#include "img1.h"
#include "gear.h"
#include <stdio.h>
#include "segoeui18.h"
#include "inc.h"
#include "dec.h"
#include "camera.h"
#include "iran.h"
#include "up.h"
#include "down.h"

#include "left.h"
#include "right.h"

#include "zoomin.h"
#include "zoomout.h"
#include "lightup.h"
#include "lightdown.h"

#include "fliphver.h"
#include "fliphor.h"

#include "foucosn.h"
#include "foucosp.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define GEAR_ID 		0x01
#define ZOOM_ID 		0x02
#define FOUCOS_ID 	0x03
#define POS_ID 			0x04
#define MOTOR_ID 		0x05
#define LIGHT_ID		0x06
#define FLIPH_ID		0x07
#define FLIPV_ID		0x08

#define GEAR_X 59
#define GEAR_Y 15
#define GEAR_DEC_X 15
#define GEAR_DEC_Y 165

#define GEAR_INC_X 175
#define GEAR_INC_Y 165
#define CAMERA_X 340
#define CAMERA_Y 90
#define LEFT_X 265
#define LEFT_Y 135

#define RIGHT_X 475
#define RIGHT_Y 135

#define UP_X 370
#define UP_Y 15

#define DOWN_X 370
#define DOWN_Y 225

#define ZOONOUT_X 160
#define ZOOMOUT_Y 265
#define ZOOMIN_X 20
#define ZOOMIN_Y 265

#define LIGHTUP_X 410
#define LIGHTUP_Y 325

#define LIGHTDOWN_X 260
#define LIGHTDOWN_Y 325

#define FLIPV_X 615
#define FLIPV_Y 15


#define FLIPH_X 615
#define FLIPH_Y 165

#define FOUCOSP_X 20
#define FOUCOSP_Y 385

#define FOUCOSN_X 160
#define FOUCOSN_Y 385

#define BUFF_SIZE 3


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;

SRAM_HandleTypeDef hsram1;

/* USER CODE BEGIN PV */
char str[80];
uint16_t x;
uint16_t y;

uint16_t gear_cnt = 0;
uint16_t zoom_cnt = 0;
uint16_t foucos_cnt = 0;
uint16_t light_cnt = 0;
uint16_t pos_cnt = 0;
uint16_t motor_cnt = 0;
uint16_t fliph_cnt = 0;
uint16_t flipv_cnt = 0;
uint8_t s = 0;
uint16_t xx =0;
uint8_t myTx[BUFF_SIZE] ;
uint8_t myRx[BUFF_SIZE] ;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_FSMC_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
uint8_t inRegion(uint16_t x,uint16_t y,uint16_t x0,uint16_t y0, uint16_t dx,uint16_t dy);
void sendCmd(uint8_t id,uint16_t val);
void drawMainMenu();
void handleTouch(uint16_t x,uint16_t y);
void putTexts();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_FSMC_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	SSD1963_Init();
	Init_TOUCH();
	SSD1963_ClearScreen(COLOR_TORGU);
	LCD_Show_Image(250,100,(uint16_t *) iran);

	sprintf(str,"Made in Iran");
	uint16_t x0 = 0;
	x0 = (TFT_WIDTH - str_whidth(str,segoe_ui) ) /2;
	lcd_put_str2( x0 ,420,str,WHITE,COLOR_TORGU,segoe_ui);

	HAL_Delay(1000);

	drawMainMenu();
  /* USER CODE END 2 */
	myTx[0] = 0x0b;
	myTx[1] = 0xc;
	myTx[2] = 0xd;
	HAL_UART_Receive_DMA(&huart1,myRx,BUFF_SIZE);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  //s =  Read_ADS2(&y,&x); //TODO: change x and y in func
  /*
	myTx[0] = myTx[0]*2  ;
	myTx[1] = myTx[1]*2 ;
	myTx[2] = myTx[2]*2;
	*/
	HAL_Delay(200);
	sprintf(str,"%02x,%02x,%02x",myTx[0],myTx[1],myTx[2]);
	lcd_put_str2(555,435,str,WHITE,BLACK,segoe_ui);
	HAL_UART_Transmit(&huart1,myTx,BUFF_SIZE,10);
	s =  tp_read3(&x,&y);
	if (s==1) {
		handleTouch(x,y);
		putTexts();

	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TP_CS_GPIO_Port, TP_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : TP_IRQ_Pin */
  GPIO_InitStruct.Pin = TP_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TP_IRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TP_CS_Pin */
  GPIO_InitStruct.Pin = TP_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TP_CS_GPIO_Port, &GPIO_InitStruct);

}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FSMC_NORSRAM_DEVICE;
  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FSMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 15;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 255;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
}

/* USER CODE BEGIN 4 */

uint8_t inRegion(uint16_t x,uint16_t y,uint16_t x0,uint16_t y0, uint16_t dx,uint16_t dy) {
	// if x,y is in region of x0,y0 -> x0+dx,y0+dy return 1 oth. return 0
	if (x> x0 && x<x0+dx && y > y0 && y<y0+dy)
		return 1;
	else
		return 0;
}

void sendCmd(uint8_t id,uint16_t val){
	myTx[0] = id;
	myTx[1] = val/16;
	myTx[2] = val%16;
	HAL_UART_Transmit(&huart1,myTx,BUFF_SIZE,10);
	sprintf(str,"%02x,%02x,%02x",myTx[0],myTx[1],myTx[2]);
	lcd_put_str2(555,435,str,WHITE,BLACK,segoe_ui);
}

void drawMainMenu() {
	SSD1963_ClearScreen(COLOR_BLACK);

	LCD_Show_Image(GEAR_X,GEAR_Y,(uint16_t *) gear);

	LCD_Show_Image(GEAR_DEC_X,GEAR_DEC_Y,(uint16_t *) dec);
	LCD_Show_Image(GEAR_INC_X,GEAR_INC_Y,(uint16_t *) inc);



	LCD_Show_Image(CAMERA_X,CAMERA_Y,(uint16_t *) camera);
	LCD_Show_Image(LEFT_X,LEFT_Y,(uint16_t *) left);
	LCD_Show_Image(RIGHT_X,RIGHT_Y,(uint16_t *) right);
	LCD_Show_Image(UP_X,UP_Y,(uint16_t *) up);
	LCD_Show_Image(DOWN_X,DOWN_Y,(uint16_t *) down);


	LCD_Show_Image(ZOOMIN_X,ZOOMIN_Y,(uint16_t *) zoomin);
	LCD_Show_Image(ZOONOUT_X,ZOOMOUT_Y,(uint16_t *) zoomout);

	LCD_Show_Image(LIGHTUP_X,LIGHTUP_Y,(uint16_t *) lightup);
	LCD_Show_Image(LIGHTDOWN_X,LIGHTDOWN_Y,(uint16_t *) lightdown);

	LCD_Show_Image(FLIPH_X,FLIPH_Y,(uint16_t *) fliphor);

	LCD_Show_Image(FLIPV_X,FLIPV_Y,(uint16_t *) flipver);

	LCD_Show_Image(FOUCOSN_X,FOUCOSN_Y,(uint16_t *) foucosn);
	LCD_Show_Image(FOUCOSP_X,FOUCOSP_Y,(uint16_t *) foucosp);

	lcd_draw_vertical_line(250,1,480,1,WHITE);
	lcd_draw_vertical_line(550,1,480,1,WHITE);

	lcd_draw_horizental_line(1,240,250,1,WHITE);

	lcd_draw_horizental_line(1,360,250,1,WHITE);

	lcd_draw_horizental_line(250,300,550,1,WHITE);

	lcd_draw_horizental_line(550,150,250,1,WHITE);

}

void handleTouch(uint16_t x,uint16_t y) {
		if ( inRegion(x,y,GEAR_INC_X,GEAR_INC_Y,60,60) ){
			gear_cnt ++;
			sendCmd(GEAR_ID,gear_cnt);
		}
		else if ( inRegion(x,y,GEAR_DEC_X,GEAR_DEC_Y,60,60) ){
			if (gear_cnt >0 ) {
				gear_cnt --;
				sendCmd(GEAR_ID,gear_cnt);
			}
		}
		else if ( inRegion(x,y,ZOOMIN_X,ZOOMIN_Y,70,70) ) {
			zoom_cnt ++;
			sendCmd(ZOOM_ID,zoom_cnt);
		}
		else if ( inRegion(x,y,ZOONOUT_X,ZOOMOUT_Y,70,70) ){
			if (zoom_cnt >0) {
				zoom_cnt --;
				sendCmd(ZOOM_ID,zoom_cnt);
			}
		}
		else if ( inRegion(x,y,FOUCOSP_X,FOUCOSP_Y,70,70) ){
			foucos_cnt ++;
			sendCmd(FOUCOS_ID,foucos_cnt);
		}
		else if ( inRegion(x,y,FOUCOSN_X,FOUCOSN_Y,70,70) ){
			if ( foucos_cnt >0) {
				foucos_cnt --;
				sendCmd(FOUCOS_ID,foucos_cnt);
			}
		}

		else if ( inRegion(x,y,LIGHTUP_X,LIGHTUP_Y,130,130) ){
			light_cnt ++;
			sendCmd(LIGHT_ID,light_cnt);
		}
		else if ( inRegion(x,y,LIGHTDOWN_X,LIGHTDOWN_Y,130,130) ) {
			if (light_cnt >0) {
				light_cnt --;
				sendCmd(LIGHT_ID,light_cnt);
			}
		}

		else if ( inRegion(x,y,RIGHT_X,RIGHT_Y,60,60) ){
			motor_cnt ++;
			sendCmd(MOTOR_ID,motor_cnt);

		}
		else if ( inRegion(x,y,LEFT_X,LEFT_Y,60,60) ){
			if (motor_cnt >0) {
				motor_cnt --;
				sendCmd(MOTOR_ID,motor_cnt);
			}
		}

		else if ( inRegion(x,y,UP_X,UP_Y,60,60) ){
			pos_cnt ++;
			sendCmd(POS_ID,pos_cnt);
		}
		else if ( inRegion(x,y,DOWN_X,DOWN_Y,60,60) ){
			if (pos_cnt > 0) {
				pos_cnt --;
				sendCmd(POS_ID,pos_cnt);
			}
		}

		else if ( inRegion(x,y,FLIPH_X,FLIPH_Y,120,120) ){
			if (fliph_cnt ==0) fliph_cnt = 1;
			else fliph_cnt = 0;
			sendCmd(FLIPH_ID,fliph_cnt);
		}
		else if ( inRegion(x,y,FLIPV_X,FLIPV_Y,120,120) ){
			if (flipv_cnt ==0) flipv_cnt = 1;
			else flipv_cnt = 0;
			sendCmd(FLIPV_ID,flipv_cnt);
		}


}

void putTexts() {
		sprintf(str,"%5u",gear_cnt);
		lcd_put_str2(90,175,str,WHITE,BLACK,segoe_ui);

		sprintf(str,"%5u",zoom_cnt);
		lcd_put_str2(90,300,str,WHITE,BLACK,segoe_ui);

		sprintf(str,"%5u",foucos_cnt);
		lcd_put_str2(90,425,str,WHITE,BLACK,segoe_ui);
		sprintf(str,"%5u",light_cnt);
		lcd_put_str2(420,460,str,WHITE,BLACK,segoe_ui);
		sprintf(str,"%5u",motor_cnt);
		lcd_put_str2(250,5,str,WHITE,BLACK,segoe_ui);
		sprintf(str,"%5u",pos_cnt);
		lcd_put_str2(490,270,str,WHITE,BLACK,segoe_ui);

		sprintf(str,"x: %6u",x);
		lcd_put_str2(605,310,str,WHITE,BLACK,segoe_ui);
		sprintf(str,"y: %6u",y);
		lcd_put_str2(605,342,str,WHITE,BLACK,segoe_ui);

		sprintf(str,"Meysam Shahbazi");
		lcd_put_str2(555,380,str,WHITE,BLACK,segoe_ui);

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

xx++;

	//lcd_put_str2(555,380,(char *) myRx,WHITE,BLACK,segoe_ui);

}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
