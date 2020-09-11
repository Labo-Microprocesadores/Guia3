
#include "SysTick.h"
#include "startup/hardware.h"

static void (*callbackFun)(void);

bool SysTick_Init (void (*funcallback)(void))
{
	SysTick->CTRL = 0x00;
	SysTick->LOAD = 50000000U - 1; // 500ms @ 100MHz
	SysTick->VAL = 0x00;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |	SysTick_CTRL_ENABLE_Msk;


	callbackFun = funcallback;
	return true;
}

__ISR__ SysTick_Handler (void)
{
	(*callbackFun)();
}

