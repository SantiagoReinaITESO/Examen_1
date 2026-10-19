/*
 * RGB.c
 *
 *  Created on: 7 sep. 2026
 *      Author: Santiago Reina
 */

#include "RGB.h"
#include "GPIO.h"
#include "frdm_hardware.h"

#include "fsl_gpio.h"

//Funcion para iniciar el modulo RGB
void RGB_init(void)
{
    GPIO_config_RGB();

    RGB_off();
}

//Funciones para encender y apagar los leds RGB

void RGB_red_led_on_off(uint8_t on_off)
{
    GPIO_PinWrite(RED_LED_GPIO, RED_LED_PIN, on_off);
}

void RGB_blue_led_on_off(uint8_t on_off)
{
    GPIO_PinWrite(BLUE_LED_GPIO, BLUE_LED_PIN, on_off);
}

void RGB_green_led_on_off(uint8_t on_off)
{
    GPIO_PinWrite(GREEN_LED_GPIO, GREEN_LED_PIN, on_off);
}

//Funciones para encender los colores RGB

void RGB_off(void)
{
    RGB_red_led_on_off(OFF);
    RGB_green_led_on_off(OFF);
    RGB_blue_led_on_off(OFF);
}

void RGB_blue(void)
{
    RGB_red_led_on_off(OFF);
    RGB_green_led_on_off(OFF);
    RGB_blue_led_on_off(ON);
}

void RGB_red(void)
{
    RGB_red_led_on_off(ON);
    RGB_green_led_on_off(OFF);
    RGB_blue_led_on_off(OFF);
}

void RGB_green(void)
{
    RGB_red_led_on_off(OFF);
    RGB_green_led_on_off(ON);
    RGB_blue_led_on_off(OFF);
}

void RGB_purple(void)
{
    RGB_red_led_on_off(ON);
    RGB_green_led_on_off(OFF);
    RGB_blue_led_on_off(ON);
}

void RGB_yellow(void)
{
    RGB_red_led_on_off(ON);
    RGB_green_led_on_off(ON);
    RGB_blue_led_on_off(OFF);
}

void RGB_cyan(void)
{
    RGB_red_led_on_off(OFF);
    RGB_green_led_on_off(ON);
    RGB_blue_led_on_off(ON);
}

void RGB_white(void)
{
    RGB_red_led_on_off(ON);
    RGB_green_led_on_off(ON);
    RGB_blue_led_on_off(ON);
}

