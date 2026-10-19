/*
 * RGB.h
 *
 *  Created on: 7 sep. 2026
 *      Author: Santiago Reina
 */

#ifndef RGB_H_
#define RGB_H_

#include <stdint.h>

//Funcion para inicializar el modulo RGB
void RGB_init(void);

//Funcion para encender los LEDs de colores
void RGB_red_led_on_off(uint8_t on_off);
void RGB_blue_led_on_off(uint8_t on_off);
void RGB_green_led_on_off(uint8_t on_off);

//Funciones para encender los colores RGB
void RGB_off(void);
void RGB_blue(void);
void RGB_red(void);
void RGB_green(void);
void RGB_purple(void);
void RGB_yellow(void);
void RGB_cyan(void);
void RGB_white(void);


#endif /* RGB_H_ */
