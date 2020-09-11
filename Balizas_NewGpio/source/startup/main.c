/***************************************************************************//**
  @file     main.c
  @brief    FW main
  @author   Nicolás Magliola
 ******************************************************************************/

#include "hardware.h"

void App_Init (void);
bool App_Run (bool);



int main (void)
{

    hw_Init();
    hw_DisableInterrupts();
    App_Init(); /* Program-specific setup */
    hw_EnableInterrupts();
    bool press = false;
    __FOREVER__
        press = App_Run(press); /* Program-specific loop  */
}
