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

#include "ssd1306.h"
#include "image.h"
#include "fonts.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

RNG_HandleTypeDef hrng;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RNG_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
uint8_t skill=0;
uint8_t force=0;
uint8_t mind=0;
char* skill_c = NULL;
char* force_c = NULL;
char* mind_c = NULL;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t arr_led_pin[9]  = {LED1_Pin, LED2_Pin, LED3_Pin,
			LED4_Pin, LED5_Pin, LED6_Pin,
			LED7_Pin, LED8_Pin, LED9_Pin};

	GPIO_TypeDef * arr_led_port[9] = {LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port,
			LED4_GPIO_Port, LED5_GPIO_Port, LED6_GPIO_Port,
			LED7_GPIO_Port, LED8_GPIO_Port, LED9_GPIO_Port};

	uint16_t arr_but_pin[9]  = {BUT1_Pin, BUT2_Pin, BUT3_Pin,
			BUT4_Pin, BUT5_Pin, BUT6_Pin,
			BUT7_Pin, BUT8_Pin, BUT9_Pin};

	GPIO_TypeDef * arr_but_port[9] = {BUT1_GPIO_Port, BUT2_GPIO_Port, BUT3_GPIO_Port,
			BUT4_GPIO_Port, BUT5_GPIO_Port, BUT6_GPIO_Port,
			BUT7_GPIO_Port, BUT8_GPIO_Port, BUT9_GPIO_Port};
	uint32_t rand_num;
void rand_comb(uint8_t round, uint8_t* combination)
{
	HAL_RNG_GenerateRandomNumber(&hrng, &rand_num);
	srand(rand_num);
	for (uint8_t i = 0; i < round; i++)
	{
		uint8_t x = rand()%9;
//			uint8_t x = ((uint8_t)rand_num)%9;
		combination[i] = x;
		HAL_GPIO_WritePin(arr_led_port[x], arr_led_pin[x], 1);
		HAL_Delay(500);
		HAL_GPIO_WritePin(arr_led_port[x], arr_led_pin[x], 0);
		HAL_Delay(500);
	}
}
void conv_dec_to_char( uint8_t value,// значення, яке будемо рзбивати на цифри
					  char *chars, // вказівник на масив цифр в двійковій формі
					  uint8_t N) // довжина масиву цифр
{
	uint8_t digits_array[2] = {0};

	for(int i = N - 1; (i > 0) && (value != 0); i--)
	{
		digits_array[i] = value % 10;
		value = value / 10;
		chars[i] = '0' + digits_array[i];
	}
}
void rep_comb(uint8_t round, uint8_t* my_combination)
{
	uint8_t num_press = 0;

		for (uint8_t x = 0; x < 9; x++)
		{
			if(HAL_GPIO_ReadPin(arr_but_port[x], arr_but_pin[x]) == 0)
			{
				HAL_GPIO_WritePin(arr_led_port[x], arr_led_pin[x], 1);
				my_combination[num_press] = x ;
				num_press ++;
				HAL_Delay(500);
				HAL_GPIO_WritePin(arr_led_port[x], arr_led_pin[x], 0);
			}
			else
			{
				HAL_GPIO_WritePin(arr_led_port[x], arr_led_pin[x], 0);
				//HAL_Delay(200);

			}
			if(x == 8)
			{
				x = 255;
			}
			if(num_press == round)
			{
				x = 9;
			}
		}

}
int	 examination(uint8_t round, uint8_t* combination, uint8_t* my_combination)
{
	uint8_t result = 0;
	for (uint8_t i = 0; i < round; i++)
	{
		if(combination[i] != my_combination[i])
		{
			result = 0;
			i = round;
		}
		else
		{
			result = 1;
		}
	}
	return result;
}
void lose()
{
	for(uint8_t x = 0; x < 9; x++)
	{
		HAL_GPIO_WritePin(arr_led_port[x], arr_led_pin[x], 0);
	}
	for(uint8_t x = 0; x < 9; x++)
	{
		HAL_GPIO_WritePin(arr_led_port[x], arr_led_pin[x], 1);
		HAL_Delay(200);
		HAL_GPIO_WritePin(arr_led_port[x], arr_led_pin[x], 0);
	}
}
void clear_screen()
{
	SSD1306_DrawFilledRectangle(0, 0, 128, 64, 0);
}


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
  MX_RNG_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  	  SSD1306_Init();
  	clear_screen();




	SSD1306_DrawFilledRectangle(0, 0, 128, 64, 0);
	SSD1306_DrawBitmap(0, 0, logo_nasa, 128, 64, 1);
	SSD1306_UpdateScreen();
	HAL_Delay(2000);
	uint8_t combination[20]    = {0};
	uint8_t my_combination[20] = {0};
	uint8_t pos_cosm = 0, is_up = 1;
 // 7x10
	skill_c = (char *) malloc(2);
	force_c = (char *) malloc(2);
	mind_c =  (char *) malloc(2);
	skill_c[0] = '0';
	skill_c[1] = '0';
	force_c[0] = '0';
	force_c[1] = '0';
	mind_c[0] = '0';
	mind_c[1] = '0';
	/* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		if(pos_cosm == 10) is_up = 0;
		if(pos_cosm == 0) is_up = 1;
		if(is_up == 1) pos_cosm++;
			else pos_cosm--;
		SSD1306_DrawFilledRectangle(0, 0, 128, 64, 0);
		SSD1306_DrawBitmap(0, 0, move_cosmo[pos_cosm], 128, 64, 1);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(HAL_GPIO_ReadPin(GPIOC,  GPIO_PIN_13) == 1)
		{
			uint8_t round = 1;
			uint8_t score_now = 0;
			char score_now_c [2] = {'0', '0'};
			while(round!=0)
			{
				conv_dec_to_char(score_now, score_now_c, 2);
				SSD1306_DrawFilledRectangle(110, 14, 18, 13, 0);
				SSD1306_GotoXY(110, 14);

				SSD1306_Puts(score_now_c, &Font_7x10, 1);
				SSD1306_UpdateScreen();
				score_now++;
				if(round == 1)
				{
					SSD1306_DrawFilledRectangle(0, 0, 128, 64, 0);
					SSD1306_DrawBitmap(0, 0, lamp[0], 128, 64, 1);
					SSD1306_GotoXY(110, 14);
					SSD1306_Puts(score_now_c, &Font_7x10, 1);
					SSD1306_UpdateScreen();

				}
				if(round == 2)
				{
					SSD1306_DrawFilledRectangle(0, 0, 128, 64, 0);
					SSD1306_DrawBitmap(0, 0, lamp[1], 128, 64, 1);
					SSD1306_GotoXY(110, 14);
					SSD1306_Puts(score_now_c, &Font_7x10, 1);
					SSD1306_UpdateScreen();
				}
				if(round == 4)
				{
					SSD1306_DrawFilledRectangle(0, 0, 128, 64, 0);
					SSD1306_DrawBitmap(0, 0, lamp[2], 128, 64, 1);
					SSD1306_GotoXY(110, 14);
					SSD1306_Puts(score_now_c, &Font_7x10, 1);
					SSD1306_UpdateScreen();
				}
				uint8_t result = 0;
				rand_comb(round, combination);
				rep_comb(round,  my_combination);
				result = examination(round, combination, my_combination);
				if(result == 0)
				{

					SSD1306_DrawFilledRectangle(0, 0, 128, 64, 0);
					SSD1306_DrawBitmap(0, 0, damage_lamp, 128, 64, 1);
					SSD1306_GotoXY(110, 14);
					SSD1306_Puts(score_now_c, &Font_7x10, 1);
					SSD1306_UpdateScreen();
					mind+=round-1;
					round = 0;
					lose();

				}
				else round ++;
			}
			SSD1306_DrawFilledRectangle(0, 0, 128, 64, 0);
			SSD1306_DrawBitmap(0, 0, move_cosmo[pos_cosm], 128, 64, 1);
			SSD1306_UpdateScreen();
		}
		SSD1306_DrawFilledRectangle(108, 0, 20, 38, 0);

		conv_dec_to_char(force,  force_c, 2);
		conv_dec_to_char(skill,  skill_c, 2);
		conv_dec_to_char(mind,  mind_c, 2);
		/*for(int j = 0; j<2; j++)
		{
			SSD1306_GotoXY( 110+j*8, 2);
			SSD1306_Putc(force_c[j], &Font_7x10, 1);
		}*/
		SSD1306_GotoXY(110, 2);
		SSD1306_Puts(force_c, &Font_7x10, 1);
		//SSD1306_UpdateScreen();
		/*for(int j = 0; j<2; j++)
		{
			SSD1306_GotoXY(110+j*8, 14);
			SSD1306_Putc(skill_c[j], &Font_7x10, 1);
		}*/
		SSD1306_GotoXY(110, 14);
		SSD1306_Puts(skill_c, &Font_7x10, 1);
		//SSD1306_UpdateScreen();
		/*for(int j = 0; j<2; j++)
		{
			SSD1306_GotoXY(110+j*8,26 );
			SSD1306_Putc(mind_c[j], &Font_7x10, 1);
		}*/
		//SSD1306_UpdateScreen();
		SSD1306_GotoXY(110, 26);
		SSD1306_Puts(mind_c, &Font_7x10, 1);
		SSD1306_UpdateScreen();
		HAL_Delay(100);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED7_Pin|LED8_Pin|LED6_Pin|LED5_Pin
                          |LED4_Pin|LED3_Pin|LED10_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED2_Pin|LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED9_GPIO_Port, LED9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BUT8_Pin BUT7_Pin BUT4_Pin BUT2_Pin */
  GPIO_InitStruct.Pin = BUT8_Pin|BUT7_Pin|BUT4_Pin|BUT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : LED7_Pin LED8_Pin LED6_Pin LED5_Pin
                           LED4_Pin LED3_Pin LED10_Pin */
  GPIO_InitStruct.Pin = LED7_Pin|LED8_Pin|LED6_Pin|LED5_Pin
                          |LED4_Pin|LED3_Pin|LED10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : BUT6_Pin BUT5_Pin BUT3_Pin */
  GPIO_InitStruct.Pin = BUT6_Pin|BUT5_Pin|BUT3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LED2_Pin LED1_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BUT9_Pin */
  GPIO_InitStruct.Pin = BUT9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUT9_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED9_Pin */
  GPIO_InitStruct.Pin = LED9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED9_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUT1_Pin */
  GPIO_InitStruct.Pin = BUT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUT1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
