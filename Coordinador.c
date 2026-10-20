/*
 * Coordinador.c
 *
 *  Created on: 19 oct. 2026
 *      Author: Santiago Queen ✨
 */

#include <stdint.h>

#include "Coordinador.h"
#include "GPIO.h"
#include "frdm_hardware.h"
#include "RGB.h"
#include "MRT.h"

// Estado actual
static volatile estado_t estado = EST_ESPERAR_INICIO;

// Variable para avisar que se presiono SW2
static volatile uint8_t evento_sw2 = 0U;

// Contador de pulsaciones SW3
static volatile uint8_t contador_sw3 = 0U;

// Momento en el que inicio el estado
static volatile uint32_t tiempo_inicio = 0U;

// Variables para evitar rebotes
static uint32_t ultimo_sw2 = 0U;
static uint32_t ultimo_sw3 = 0U;
static uint8_t primer_sw2 = 1U;
static uint8_t primer_sw3 = 1U;


// Callback de los botones
static void COOR_boton_callback(uint8_t boton)
{
    uint32_t tiempo = MRT_get_time_ms();

    if(boton == GPIO_BUTTON_SW2)
    {
        if((primer_sw2 == 1U) || ((tiempo - ultimo_sw2) >= ANTIRREBOTE_MS))
        {
            primer_sw2 = 0U;
            ultimo_sw2 = tiempo;

            // SW2 solo funciona en estos estados
            if((estado == EST_ESPERAR_INICIO) || (estado == EST_ESPERAR_SW2) || (estado == EST_MOSTRAR_COLOR))
            {
                evento_sw2 = 1U;
            }
        }
    }

    else if(boton == GPIO_BUTTON_SW3)
    {
        // Contar solamente durante los 7 segundos
        if(estado == EST_CONTAR_SW3)
        {
            if((tiempo - tiempo_inicio) < TIEMPO_CONTEO_MS)
            {
                if((primer_sw3 == 1U) || ((tiempo - ultimo_sw3) >= ANTIRREBOTE_MS))
                {
                    primer_sw3 = 0U;
                    ultimo_sw3 = tiempo;

                    // Guardar hasta 6 (mas de 5)
                    if(contador_sw3 < 6U)
                    {
                        contador_sw3++;
                    }
                }
            }
        }
    }
}


void COOR_Inicio(void)
{
    RGB_off();

    estado = EST_ESPERAR_INICIO;

    evento_sw2 = 0U;
    contador_sw3 = 0U;
    tiempo_inicio = 0U;

    ultimo_sw2 = 0U;
    ultimo_sw3 = 0U;

    primer_sw2 = 1U;
    primer_sw3 = 1U;

    // SET del MRT
    MRT_set_time_ms(0U);

    // Registrar callback GPIO
    GPIO_register_callback(COOR_boton_callback);
}


// Procesar la maquina de estados
void COOR_Procesar(void)
{
    // GET del MRT
    uint32_t tiempo = MRT_get_time_ms();
    switch (estado)
    {
        
        case EST_ESPERAR_INICIO:
            if(evento_sw2 == 1U)
            {
                evento_sw2 = 0U;
                RGB_white();
                tiempo_inicio = tiempo;
                estado = EST_BLANCO_1;
            }
        
        break;

        case EST_BLANCO_1:
            if((tiempo - tiempo_inicio) >= TIEMPO_BLANCO_MS)
            {
                RGB_off();
                tiempo_inicio = tiempo;
                estado = EST_APAGADO_1;
            }
        break;

        case EST_APAGADO_1:
            if((tiempo - tiempo_inicio) >= TIEMPO_BLANCO_MS)
            {
                RGB_white();
                tiempo_inicio = tiempo;
                estado = EST_BLANCO_2;
            }
        break;

        case EST_BLANCO_2:
            if((tiempo - tiempo_inicio) >= TIEMPO_BLANCO_MS)
            {
                RGB_off();
                tiempo_inicio = tiempo;
                estado = EST_APAGADO_2;
            }
        break;
        
        case EST_APAGADO_2:
            if((tiempo - tiempo_inicio) >= TIEMPO_BLANCO_MS)
            {
                estado = EST_ESPERAR_SW2;
            }
        break;

        case EST_ESPERAR_SW2:
            if(evento_sw2 == 1U)
            {
                evento_sw2 = 0U;
                RGB_green();
                tiempo_inicio = tiempo;
                estado = EST_VERDE;
            }
        break;

        case EST_VERDE:
            if((tiempo - tiempo_inicio) >= TIEMPO_VERDE_MS)
            {
                RGB_off();
                contador_sw3 = 0U;
                primer_sw3 = 1U;
                tiempo_inicio = tiempo;
                estado = EST_CONTAR_SW3;
            }
        break;

        case EST_CONTAR_SW3:
            if((tiempo - tiempo_inicio) >= TIEMPO_CONTEO_MS)
            {
                estado = EST_MOSTRAR_COLOR;
                switch(contador_sw3)
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
                        RGB_off();
                    break;
                }
            }
        break;

        case EST_MOSTRAR_COLOR:
            if(evento_sw2 == 1U)
            {
                evento_sw2 = 0U;
                RGB_green();
                tiempo_inicio = tiempo;
                estado = EST_VERDE;
            }
        break;

        default:
            RGB_off();
            estado = EST_ESPERAR_INICIO;
        break;
    }
}

