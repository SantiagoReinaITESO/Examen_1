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
    // Configurar el DAC
    DAC_config();

    // Configurar LEDs y botones
    RGB_init();
    GPIO_config_SW();

    // Seleccionar señal inicial
    DAC_senoidal_init();

    // Recorrer el arreglo de 1 en 1
    DAC_set_paso(1U);

    // Registrar callback y configurar MRT
    MRT_set_callback(DAC_muestra_callback);

    // Cambiar a cuadrada despues de 5000 interrupciones
    DAC_programar_cambio(5000U, SENAL_CUADRADA);

    MRT_config_Hz(1000U);

    while(1)
    {

    }

    return 0;
}
