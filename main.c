/*
 * Autor Santiago Reina
 */
#include "frdm_hardware.h"

#include "NVIC.h"
#include "MRT.h"
#include "DAC.h"
#include "RGB.h"
#include "GPIO.h"


int main(void)
{
    // Configurar LEDs y botones
    RGB_init();
    GPIO_config_SW();

    // Registrar callback y configurar MRT
    MRT_set_callback(DAC_muestra_callback);
    GPIO_register_callback(GPIO_SW_callback);

    MRT_config_Hz(1000U);

    while(1)
    {
        
    }

    return 0;
}
