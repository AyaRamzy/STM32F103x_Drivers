#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"

#include "LEDMRX_interface.h"
#include "LEDMRX_private.h"
#include "LEDMRX_config.h"

u8 rows[16] = {LEDMRX_ROW0, LEDMRX_ROW1, LEDMRX_ROW2, LEDMRX_ROW3, LEDMRX_ROW4,
			LEDMRX_ROW5, LEDMRX_ROW6, LEDMRX_ROW7};
u8 cols[16] = {LEDMRX_COL0, LEDMRX_COL1, LEDMRX_COL2, LEDMRX_COL3, LEDMRX_COL4,
			LEDMRX_COL5, LEDMRX_COL6, LEDMRX_COL7};

volatile u8 No_Animating 	= 0;
volatile u8 Waiting			= 10;

void HLEDMRX_voidInit(void)
{
	for(u8 i =0; i <= 7; i++)
	{
		MGPIO_voidSetPinDirection(rows[i*2], rows[i*2 + 1], OUTPUT_SPEED_2MHZ_PP);
		MGPIO_voidSetPinDirection(cols[i*2], cols[i*2 + 1], OUTPUT_SPEED_2MHZ_PP);
	}
}

void HLEDMRX_voidDisplay(u8 *Copy_u8Data)
{
	u8 Local_u8BIT;
	for(u8 fbs =0; fbs < 50; fbs++)
	{
		for(u8 i =0; i <= 7; i++)
		{
			for(u8 j =0; j <= 7; j++)
			{
				MGPIO_voidSetPinValue(cols[j*2], cols[j*2 + 1], HIGH);
			}
			for(u8 k =0; k <= 7; k++)
			{
				Local_u8BIT = GET_BIT(Copy_u8Data[i], k);
				MGPIO_voidSetPinValue(rows[k*2], rows[k*2 + 1], Local_u8BIT);
			}
			MGPIO_voidSetPinValue(cols[i*2], cols[i*2 + 1], LOW);
			MSTK_voidSetBusyWait(2.5);
		}
	}
}

void HLEDMRX_voidAnimation(u8 *Copy_u8Data)
{
	u8  Local_u8BIT;
	while(1)
	{

		for (u8 m = 0; m < 30; m++)
		{
			while(No_Animating);
			u8 Local_temp_data [8] = {Copy_u8Data[m], Copy_u8Data[m + 1],Copy_u8Data[m + 2],Copy_u8Data[m + 3],Copy_u8Data[m + 4],Copy_u8Data[m + 5],Copy_u8Data[m + 6],Copy_u8Data[m + 7]};
			for(u8 l = 0; l < Waiting; l++)
			{
				for(u8 i =0; i <= 7; i++){
					for(u8 j =0; j <= 7; j++)
					{
						MGPIO_voidSetPinValue(cols[j*2], cols[j*2 + 1], HIGH);
					}
					for(u8 k =0; k <= 7; k++)
					{
						Local_u8BIT = GET_BIT(Local_temp_data[i], k);
						MGPIO_voidSetPinValue(rows[k*2], rows[k*2 + 1], Local_u8BIT);
					}
					MGPIO_voidSetPinValue(cols[i*2], cols[i*2 + 1], LOW);
					delay_ms(2);
				}
			}
		}
	}
}

void HLEDMRX_voidAnimateFrames(u8 Copy_u8FramesVal[][8], u8 Copy_u8FramesNum)
{
	for(u8 frame = 0; frame < Copy_u8FramesNum; frame++)
	{
		u8 Local_u8BIT;
		for(u8 fbs =0; fbs < 50; fbs++)
		{
			for(u8 i =0; i <= 7; i++)
			{
				for(u8 j =0; j <= 7; j++)
				{
					MGPIO_voidSetPinValue(cols[j*2], cols[j*2 + 1], HIGH);
				}
				for(u8 k =0; k <= 7; k++)
				{
					Local_u8BIT = GET_BIT(Copy_u8FramesVal[frame][i], k);
					MGPIO_voidSetPinValue(rows[k*2], rows[k*2 + 1], Local_u8BIT);
				}
				MGPIO_voidSetPinValue(cols[i*2], cols[i*2 + 1], LOW);
				MSTK_voidSetBusyWait(2.5);
			}
		}
	}
}


void HLEDMRX_voidPauseAnimating(void)
{
	No_Animating = 1;
}

void HLEDMRX_voidResumeAnimating(void)
{
	No_Animating = 0;
}

void HLEDMRX_voidSpeedDown(void)
{
	Waiting += 2;
}

void HLEDMRX_voidSpeedUp(void)
{
	Waiting -= 2;
}