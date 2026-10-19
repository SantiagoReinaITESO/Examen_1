/*
 * frdm_hardware.h
 *
 *  Created on: 3 sep. 2026
 *      Author: Santiago Queen
 */

#ifndef FRDM_HARDWARE_H_
#define FRDM_HARDWARE_H_

#define RED_LED_GPIO       (GPIO0)
#define GREEN_LED_GPIO     (GPIO0)
#define BLUE_LED_GPIO      (GPIO1)

#define RED_LED_PORT       (PORT0)
#define GREEN_LED_PORT     (PORT0)
#define BLUE_LED_PORT      (PORT1)

#define RED_LED_PIN        (10U)
#define GREEN_LED_PIN      (27U)
#define BLUE_LED_PIN       (2U)

//Salida digital de prueba
#define SIGNAL_GPIO         (GPIO2)
#define SIGNAL_PORT         (PORT2)
#define SIGNAL_PIN          (0U)

#define SW2_GPIO           (GPIO0)
#define SW3_GPIO           (GPIO0)

#define SW2_PORT           (PORT0)
#define SW3_PORT           (PORT0)

#define SW2_PIN            (23U)
#define SW3_PIN            (6U)


#define P4_2_PIN           (2U)

#define ON                 (0U)
#define OFF                (1U)

/* Reloj del sistema */
#define SYSTEM_CLOCK_HZ    (48000000U)

//Señal DAC
#define NUMERO_MUESTRAS    (100U)
#define DAC_LOW            (0U)
#define DAC_HIGH           (4095U)

//Defines para Generador
#define FREQ_500  (500U)
#define FREQ_1000 (1000U)
#define FREQ_1500 (1500U)
#define FREQ_5000 (5000U)

typedef enum
{
    FALSE,
    TRUE
} bool_value_t;

#endif /* FRDM_HARDWARE_H_ */
