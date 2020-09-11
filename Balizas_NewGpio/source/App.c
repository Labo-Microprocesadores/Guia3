/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define LED PORTNUM2PIN(PB,23) //PTA0
#define SW PORTNUM2PIN(PC,0)
#define DELAY 20
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t veces);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    gpioMode(SW, INPUT_PULLUP);
    gpioMode(LED, OUTPUT);
    gpioMode(PIN_LED_RED, OUTPUT);

    //gpioWrite(LED, HIGH);
    gpioWrite(PIN_LED_RED, HIGH);
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
	static bool press = false;
	static bool baliza = false;
	static uint32_t b_counter = DELAY;

	if (!gpioRead(SW) && !press)
	{
		press = true;
		baliza = !baliza;
		gpioToggle(PIN_LED_RED);
		if(baliza)
		{
			gpioWrite(LED, HIGH);
			b_counter = DELAY; //prendo la baliza
		}
		else
			gpioWrite(LED, LOW); // apago la baliza

	}
	else if(gpioRead(SW) && press)
	{
		press = false;
	}

	delayLoop(715000);

	if(baliza && (b_counter--)==0)
	{
		gpioToggle(LED);
		b_counter = DELAY;
	}


}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void delayLoop(volatile uint32_t veces)
{
    while (veces--);
}


/*******************************************************************************
 ******************************************************************************/
