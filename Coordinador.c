/*
 * Coordinador.c
 *
 *  Created on: 19 oct. 2026
 *      Author: Santiago Queen ✨
 */

#include <stdint.h>
#include "GPIO.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "frdm_hardware.h"
#include "RGB.h"



void COOR_Inicio(void)
{
    GPIO_SW_callback(GPIO_BUTTON_SW2);
}

void COOR_Procesar(uint32_t pin)
{
    if (pin == GPIO_BUTTON_SW2)
    {
        RGB_green(); // Encender todos
        mrt_delay_ms(1000); // Esperar 1 segundo
        RGB_off(); // Apagar todos los LEDs
    }
    else if (pin == GPIO_BUTTON_SW3)
    {
        RGB_off(); // Apagar todos los LEDs
    }
}