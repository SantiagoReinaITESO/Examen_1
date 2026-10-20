/*
 * MRT.h
 *
 *  Created on: 19 sep. 2026
 *      Author: Fernando
 */

#ifndef MRT_H_
#define MRT_H_

#include <stdint.h>

// este es el callback del mrt osea cada ves que salta la interrupcion
typedef void (*mrt_callback_t)(void);

// Registrar la funcion que se ejecutara
// cuando ocurra la interrupcion
void MRT_set_callback(mrt_callback_t callback);

// Configurar el MRT en milisegundos
void MRT_config_ms(uint32_t period_ms);

// Configurar el MRT en microsegundos
void MRT_config_us(uint32_t period_us);

// Configurar el MRT en Hertz
void MRT_config_Hz(uint32_t frequency_hz);

void mrt_delay_ms(uint32_t ms);


uint32_t MRT_get_time_ms(void);

void MRT_set_time_ms(uint32_t time_ms);

#endif /* MRT_H_ */
