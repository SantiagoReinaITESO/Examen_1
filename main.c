/*
 * Autor Santiago Reina
 */
#include "frdm_hardware.h"

#include "NVIC.h"
#include "MRT.h"
#include "RGB.h"
#include "GPIO.h"
#include "Coordinador.h"


int main(void)
{
    // Configurar LEDs y botones
    RGB_init();
    GPIO_config_SW();

    // Registrar callback y configurar MRT
    GPIO_register_callback(GPIO_SW_callback);

    MRT_config_Hz(1000U);

    while(1)
    {
        COOR_Inicio();
        COOR_Procesar(SW2_PIN);
        COOR_PRocesar_sw3(SW3_PIN);
    }

    return 0;
}
