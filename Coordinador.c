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
#include "Coordinador.h"
#include "MRT.h"



void COOR_Inicio(void)
{
    GPIO_SW_callback(GPIO_BUTTON_SW2);
}

void COOR_Procesar_sw2(uint32_t pin)
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

void COOR_PRocesar_sw3(uint16_t pin)
{
    
    uint16_t time = get_time();

    if (time >= 7)
    {
        uint16_t SW3_PUSH = GPIO_coun_SW3 (pin);
        switch (SW3_PUSH)
            {
            case 1:
                RGB_cyan();
                break;
            case 2:
                RGB_yellow();
                break;
            case 3:
                RGB_red();
                break;
            case 4:
                RGB_purple();
                break;
            case 5:
                RGB_blue();
                break;
            default:
                RGB_blue;
                break;
            }
    }
    
}

