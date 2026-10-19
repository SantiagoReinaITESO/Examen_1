/*
 * Generador.c
 *
 *  Created on: 27 sep. 2026
 *      Author: Santiago Reina
 */

/*
 * agregue dac_set_paso para recorrer las tablas de 1, 2 o 5 muestras, y asi
 * alcanzar las frecuencias altas sin que el mrt interrumpa demasiado rapido.
 * funciona asi: cada senal esta en una tabla de 100 muestras. el callback del mrt
 * levanta una bandera y dac_draw escribe la siguiente muestra de la senal activa.
 * dac_cambiar_senal avanza la secuencia off, senoidal, cuadrada, triangular.
 */

#include "DAC.h"
#include "frdm_hardware.h"

#include "fsl_dac.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_common.h"


// Indice de señal dentro del arreglo de señales
static dac_signal_t senal_actual = SENAL_OFF;
// Get para el futuro cntrolar los leds dependiendo señal
dac_signal_t DAC_get_signal(void)
{
    return senal_actual;
}

//Indicice que recorre los arreglos
static uint16_t indice_muestra = 0U;
//Indicador para pasos de el arreglo
static uint16_t paso_muestra = 1U;

// Contar las interrupciones del MRT
static uint32_t contador_mrt = 0U;

// Cantidad de interrupciones antes de cambiar
static uint32_t limite_mrt = 0U;

// Señal que queremos mostrar despues
static dac_signal_t siguiente_senal = SENAL_OFF;

// Tablas de señales
// Crear Señal Cuadrada
static const uint16_t senal_cuadrada[NUMERO_MUESTRAS] =
{
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,

    4095U, 4095U, 4095U, 4095U, 4095U,
    4095U, 4095U, 4095U, 4095U, 4095U,
    4095U, 4095U, 4095U, 4095U, 4095U,
    4095U, 4095U, 4095U, 4095U, 4095U,
    4095U, 4095U, 4095U, 4095U, 4095U,
    4095U, 4095U, 4095U, 4095U, 4095U,
    4095U, 4095U, 4095U, 4095U, 4095U,
    4095U, 4095U, 4095U, 4095U, 4095U,
    4095U, 4095U, 4095U, 4095U, 4095U,
    4095U, 4095U, 4095U, 4095U, 4095U
};
//Crear Señal Triangular
static const uint16_t senal_triangular[NUMERO_MUESTRAS] =
{
    0U,    83U,   167U,  250U,  334U,
    417U,  501U,  585U,  668U,  752U,
    835U,  919U,  1002U, 1086U, 1170U,
    1253U, 1337U, 1420U, 1504U, 1587U,
    1671U, 1755U, 1838U, 1922U, 2005U,
    2089U, 2172U, 2256U, 2340U, 2423U,
    2507U, 2590U, 2674U, 2757U, 2841U,
    2925U, 3008U, 3092U, 3175U, 3259U,
    3342U, 3426U, 3510U, 3593U, 3677U,
    3760U, 3844U, 3927U, 4011U, 4095U,

    4095U, 4011U, 3927U, 3844U, 3760U,
    3677U, 3593U, 3510U, 3426U, 3342U,
    3259U, 3175U, 3092U, 3008U, 2925U,
    2841U, 2757U, 2674U, 2590U, 2507U,
    2423U, 2340U, 2256U, 2172U, 2089U,
    2005U, 1922U, 1838U, 1755U, 1671U,
    1587U, 1504U, 1420U, 1337U, 1253U,
    1170U, 1086U, 1002U, 919U,  835U,
    752U,  668U,  585U,  501U,  417U,
    334U,  250U,  167U,  83U,   0U
};
//Crear Señal Senoidal
static const uint16_t senal_senoidal[NUMERO_MUESTRAS] =
{
    2048U, 2176U, 2304U, 2431U, 2557U,
    2680U, 2801U, 2919U, 3034U, 3145U,
    3251U, 3353U, 3449U, 3540U, 3625U,
    3704U, 3776U, 3842U, 3900U, 3951U,
    3995U, 4031U, 4059U, 4079U, 4091U,

    4095U,

    4091U, 4079U, 4059U, 4031U, 3995U,
    3951U, 3900U, 3842U, 3776U, 3704U,
    3625U, 3540U, 3449U, 3353U, 3251U,
    3145U, 3034U, 2919U, 2801U, 2680U,
    2557U, 2431U, 2304U, 2176U,

    2048U,

    1919U, 1791U, 1664U, 1538U, 1415U,
    1294U, 1176U, 1061U, 950U,  844U,
    742U,  646U,  555U,  470U,  391U,
    319U,  253U,  195U,  144U,  100U,
    64U,   36U,   16U,   4U,

    0U,

    4U,    16U,   36U,   64U,   100U,
    144U,  195U,  253U,  319U,  391U,
    470U,  555U,  646U,  742U,  844U,
    950U,  1061U, 1176U, 1294U, 1415U,
    1538U, 1664U, 1791U, 1919U
};

//Funciones para inicializar las señales son las que se comunican en el main
//Funcion OFF
void DAC_off_init(void)
{
    indice_muestra = 0U;

    senal_actual = SENAL_OFF;

    DAC_write(DAC_LOW);
}
//Funcion Incializar señal Senoidal--
void DAC_senoidal_init(void)
{
    indice_muestra = 0U;

    senal_actual = SENAL_SENOIDAL;

    DAC_write(senal_senoidal[indice_muestra]);
}
void DAC_senoidal_sig_muestra(void)
{
    indice_muestra += paso_muestra ;

    if(indice_muestra >= NUMERO_MUESTRAS)
    {
        indice_muestra = 0U;
    }

    DAC_write(senal_senoidal[indice_muestra]);
}
//Funcion Inicilaizar Señal Cuadrada---
void DAC_cuadrada_init(void)
{
    indice_muestra = 0U;
    senal_actual = SENAL_CUADRADA;

    DAC_write(senal_cuadrada[indice_muestra]);
}
void DAC_cuadrada_sig_muestra(void)
{
    indice_muestra += paso_muestra;

    if(indice_muestra >= NUMERO_MUESTRAS)
    {
        indice_muestra = 0U;
    }

    DAC_write(senal_cuadrada[indice_muestra]);
}
//Funcion Inicilaizar Señal Triangular---
void DAC_triangular_init(void)
{
    indice_muestra = 0U;
    senal_actual = SENAL_TRIANGULAR;

    DAC_write(senal_triangular[indice_muestra]);
}
void DAC_triangular_sig_muestra(void)
{
    indice_muestra += paso_muestra;

    if(indice_muestra >= NUMERO_MUESTRAS)
    {
        indice_muestra = 0U;
    }

    DAC_write(senal_triangular[indice_muestra]);
}



// Funcion para escribir y asegurar que no se escriba mas del limite DAC_HIGH
void DAC_write(uint16_t value)
{
    if(value > DAC_HIGH)
    {
        value = DAC_HIGH;
    }

    DAC_SetData(DAC0, value);
}


void DAC_muestra_callback(void)
{
    // Dibujar la siguiente muestra
    DAC_draw();

    // Verificar si tenemos un cambio programado
    if(limite_mrt > 0U)
    {
        contador_mrt++;

        if(contador_mrt >= limite_mrt)
        {
            // Cancelar el cambio programado
            limite_mrt = 0U;
            contador_mrt = 0U;

            // Seleccionar la siguiente señal
            if(SENAL_SENOIDAL == siguiente_senal)
            {
                DAC_senoidal_init();
            }
            else if(SENAL_CUADRADA == siguiente_senal)
            {
                DAC_cuadrada_init();
            }
            else if(SENAL_TRIANGULAR == siguiente_senal)
            {
                DAC_triangular_init();
            }
            else
            {
                DAC_off_init();
            }
        }
    }
}

void DAC_config(void)
{
    dac_config_t dac_config;
    
    //Habilitar el PORT 4
    CLOCK_EnableClock(kCLOCK_Port4);


    // P4_2 como DAC0_OUT
    const port_pin_config_t dac_pin_config =
    {
        kPORT_PullDisable,
        kPORT_LowPullResistor,
        kPORT_FastSlewRate,
        kPORT_PassiveFilterDisable,
        kPORT_OpenDrainDisable,
        kPORT_LowDriveStrength,
        kPORT_MuxAlt0,
        kPORT_InputBufferDisable,
        kPORT_InputNormal,
        kPORT_UnlockRegister
    };

    PORT_SetPinConfig(PORT4, P4_2_PIN, &dac_pin_config);

    // Clock del DAC0
    CLOCK_AttachClk(kFRO_HF_to_DAC0);
    CLOCK_SetClkDiv(kCLOCK_DivDac0Clk, 1U);

    //Habilitar DAC0 y VREF
    SPC0->ACTIVE_CFG1 |= 0x11U;

    /* Configuración por defecto */
    DAC_GetDefaultConfig(&dac_config);

    /*
     * Sin FIFO.
     * Cada DAC_SetData() actualiza directamente
     * el valor de salida.
     */
    dac_config.fifoWorkMode = kDAC_FIFODisabled;
    /* Referencia */
    dac_config.referenceVoltageSource = kDAC_ReferenceVoltageSourceAlt1;

    //Inicializar DAC
    DAC_Init(DAC0, &dac_config);
    //Habilitar DAC
    DAC_Enable(DAC0, true);
    // Valir Inical en 0
    DAC_SetData(DAC0, 0U);
}

//Funcion que se ejecutara constante mente en el main

void DAC_draw(void)
{
    if(SENAL_SENOIDAL == senal_actual)
    {
        DAC_senoidal_sig_muestra();
    }
    else if(SENAL_CUADRADA == senal_actual)
    {
        DAC_cuadrada_sig_muestra();
    }
    else if(SENAL_TRIANGULAR == senal_actual)
    {
        DAC_triangular_sig_muestra();
    }
    else
    {
        DAC_write(DAC_LOW);
    }
}


//Funcion para cambiar la señal en funcion de sw2
void DAC_cambiar_senal(void)
{
    indice_muestra = 0U;

    if(SENAL_OFF == senal_actual)
    {
        senal_actual = SENAL_SENOIDAL;

        DAC_write(senal_senoidal[indice_muestra]);
    }
    else if(SENAL_SENOIDAL == senal_actual)
    {
        senal_actual = SENAL_CUADRADA;

        DAC_write(senal_cuadrada[indice_muestra]);
    }
    else if(SENAL_CUADRADA == senal_actual)
    {
        senal_actual = SENAL_TRIANGULAR;

        DAC_write(senal_triangular[indice_muestra]);
    }
    else
    {
        senal_actual = SENAL_OFF;

        DAC_write(DAC_LOW);
    }
}

//Funcion para controlar el paso en el que rrecore el arreglo, se usara para arreglar las frecuencias al tas

void DAC_set_paso(uint16_t step)
{
    if((step > 0U) && (step < NUMERO_MUESTRAS))
    {
        paso_muestra = step;
    }
}


void DAC_programar_cambio(uint32_t interrupciones, dac_signal_t nueva_senal)
{
    contador_mrt = 0U;
    limite_mrt = interrupciones;
    siguiente_senal = nueva_senal;
}
