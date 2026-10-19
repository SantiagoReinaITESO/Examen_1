/*
 * GPIO.h
 *
 *  Created on: 17 jun. 2026
 *      Author: luispizano
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#define GPIO_BUTTON_NONE  (0U)
#define GPIO_BUTTON_SW2   (1U)
#define GPIO_BUTTON_SW3   (2U)
#define GPIO_BUTTON_BOTH  (3U)

// Tipo de dato para los callbacks
typedef void (*gpio_callback_t)(uint8_t buttons);


/*! These constants are used to select an specific port in the different API functions*/
typedef enum{GPIO_0, /*!< Definition to select GPIO A */
			 GPIO_1, /*!< Definition to select GPIO B */
			 GPIO_2, /*!< Definition to select GPIO C */
			 GPIO_3, /*!< Definition to select GPIO D */
			 GPIO_4, /*!< Definition to select GPIO E */
			 GPIO_5  /*!< Definition to select GPIO F */
} gpio_name_t;

void GPIO_config_RGB(void);
void GPIO_config_SW(void);

// Registrar el callback de los botones
void GPIO_register_callback(gpio_callback_t callback);


#endif /* GPIO_H_ */
