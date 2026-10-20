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

    // Configurar el MRT cada 1 ms
    MRT_config_Hz(1000U);

    // Inicializar la maquina de estados
    COOR_Inicio();

    // Habilitar las interrupciones GPIO
    NVIC_enable_interrupt_and_priotity(NVIC_GPIO00_IRQn, PRIORITY_4);

    while(1)
    {
        COOR_Procesar();
    }

    return 0;
}
