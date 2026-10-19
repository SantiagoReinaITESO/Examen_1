/*
 * DAC.h
 *
 *  Created on: 17 sep. 2026
 *      Author: Santiago Reina
 */

#ifndef DAC_H_
#define DAC_H_

#include <stdint.h>

// Tipos de señales que podemos generar
typedef enum
{
    SENAL_OFF,
    SENAL_SENOIDAL,
    SENAL_CUADRADA,
    SENAL_TRIANGULAR,

} dac_signal_t;

//Señal off
void DAC_off_init(void);
//Señal Senoidal--
void DAC_senoidal_init(void);
void DAC_senoidal_sig_muestra(void);
//Señal Cuadrada--
void DAC_cuadrada_init(void);
void DAC_cuadrada_sig_muestra(void);
//SeñalTriangular--
void DAC_triangular_init(void);
void DAC_triangular_sig_muestra(void);


//Funcion de configuaracion del DAC salida por P4_2
void DAC_config(void);
//Funcion para escribir el siguiente dato del DAC
void DAC_write(uint16_t value);

//Funciones para actualizar y dibujar la señal correspondiente
void DAC_muestra_callback(void);
void DAC_draw(void);

//Control de señales
void DAC_cambiar_senal(void);
dac_signal_t DAC_get_signal(void);

//Controlar el paso que se rrecorrera el arrelgo
void DAC_set_paso(uint16_t step);

// Cambiar automaticamente despues de varias interrupciones
void DAC_programar_cambio(uint32_t interrupciones, dac_signal_t nueva_senal);

#endif /* DAC_H_ */
