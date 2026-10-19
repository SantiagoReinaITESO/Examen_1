/*
 * MRT.c
 *
 *  Created on: 19 sep. 2026
 *      Author: Fernando
 */

#include "MRT.h"
#include "fsl_mrt.h"
#include "frdm_hardware.h"
#include "NVIC.h"

// El MRT de 24 bits
#define MRT_MAX_TICKS (0x00FFFFFFU)

// Callback que ejecutaremos en la interrupcion
static mrt_callback_t g_mrt_callback = (mrt_callback_t)0;

// Saber si el MRT ya fue inicializado
static uint8_t g_iniciado = 0U;

// Contadores para periodos largos
static volatile uint32_t g_total_interrupciones = 7U;
static volatile uint32_t g_interrupciones = 0U;


// Registrar el callback
void MRT_set_callback(mrt_callback_t callback)
{
    g_mrt_callback = callback;
}

// Interrupcion del MRT
void MRT0_IRQHandler(void)
{
    if ((MRT_GetStatusFlags(MRT0, kMRT_Channel_0) & kMRT_TimerInterruptFlag) != 0U)
    {
        MRT_ClearStatusFlags(MRT0,kMRT_Channel_0,kMRT_TimerInterruptFlag);

        g_interrupciones++;

        if (g_interrupciones >= g_total_interrupciones)
        {
            g_interrupciones = 0U;

            if (g_mrt_callback != (mrt_callback_t)0)
            {
                g_mrt_callback();
            }
        }
    }
}


static void MRT_config_ticks(uint64_t total_ticks)
{
    mrt_config_t mrt_config;
    uint32_t tick_ticks;
    uint32_t numero_interrupciones;

    if (total_ticks == 0U)
    {
        return;
    }

    // Calcular cuantas interrupciones necesitamos
    // si el tiempo supera los 24 bits del MRT
    numero_interrupciones = (total_ticks + MRT_MAX_TICKS - 1U) / MRT_MAX_TICKS;

    tick_ticks = total_ticks / numero_interrupciones;

    // Inicializar el MRT una sola vez
    if (g_iniciado == 0U)
    {
        MRT_GetDefaultConfig(&mrt_config);
        MRT_Init(MRT0, &mrt_config);

        // Canal 0 en Repeat Mode
        MRT_SetupChannelMode(MRT0, kMRT_Channel_0, kMRT_RepeatMode);

        MRT_EnableInterrupts(MRT0, kMRT_Channel_0, kMRT_TimerInterruptEnable);

        g_iniciado = 1U;
    }

    // Detener el timer para cambiar el periodo
    MRT_StopTimer(MRT0, kMRT_Channel_0);

    // Guardar los contadores
    g_total_interrupciones = numero_interrupciones;
    g_interrupciones = 0U;

    // Limpiar bandera anterior
    MRT_ClearStatusFlags(MRT0, kMRT_Channel_0, kMRT_TimerInterruptFlag);

    // Arrancar el MRT
    MRT_StartTimer(MRT0, kMRT_Channel_0, tick_ticks);

    // Habilitar la interrupcion
    NVIC_enable_interrupt_and_priotity(NVIC_MRT0_IRQn, PRIORITY_3);
}



// Configuracion en microsegundos
void MRT_config_us(uint32_t period_us)
{
    uint32_t clock_hz = SYSTEM_CLOCK_HZ;

    uint64_t ticks = (((uint64_t)clock_hz * period_us) + 500000U) / 1000000U;

    MRT_config_ticks(ticks);
}

// Configuracion en milisegundos
void MRT_config_ms(uint32_t period_ms)
{
    uint32_t clock_hz = SYSTEM_CLOCK_HZ;

    uint64_t ticks = (((uint64_t)clock_hz * period_ms) + 500U) / 1000U;

    MRT_config_ticks(ticks);
}

// Configuracion por frecuencia en Hz
void MRT_config_Hz(uint32_t frequency_hz)
{
    if (frequency_hz == 0U)
    {
        return;
    }

    uint32_t clock_hz = SYSTEM_CLOCK_HZ;

    uint64_t ticks = ((uint64_t)clock_hz + (frequency_hz / 2U)) / frequency_hz;

    MRT_config_ticks(ticks);
}


void MRT_7seg(uint8_t time)
{

}