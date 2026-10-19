/*
 * MRT.h
 *
 *  Created on: 19 sep. 2026
 *      Author: Fernando
 */

#include "GPIO.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "frdm_hardware.h"
#include "fsl_clock.h"

static gpio_callback_t gpio_callback = (gpio_callback_t)0;

void GPIO_register_callback(gpio_callback_t callback)
{
    gpio_callback = callback;
}


// Interrupcion del GPIO0 para los pines SW2 y SW3

void GPIO00_IRQHandler(void)
{
    uint8_t buttons = GPIO_BUTTON_NONE;

    uint8_t status_sw2;
    uint8_t status_sw3;

    // Revisar las banderas de los botones
    status_sw2 = GPIO_PinGetInterruptFlag(GPIO0, SW2_PIN);
    status_sw3 = GPIO_PinGetInterruptFlag(GPIO0, SW3_PIN);

    // Limpiar las banderas
    if(status_sw2)
    {
        GPIO_PinClearInterruptFlag(GPIO0, SW2_PIN);
    }

    if(status_sw3)
    {
        GPIO_PinClearInterruptFlag(GPIO0, SW3_PIN);
    }

    // Identificar el boton que genero la interrupcion
    if(status_sw2 && status_sw3)
    {
        buttons = GPIO_BUTTON_BOTH;
    }
    else if(status_sw2)
    {
        buttons = GPIO_BUTTON_SW2;
    }
    else if(status_sw3)
    {
        buttons = GPIO_BUTTON_SW3;
    }

    // Ejecutar el callback
    if((GPIO_BUTTON_NONE != buttons) && (gpio_callback))
    {
        gpio_callback(buttons);
    }
}


void GPIO_config_RGB(void)
{
	/* Define the init structure for the output LED pin*/
		gpio_pin_config_t led_config = {
			kGPIO_DigitalOutput,
			1,
		};

		// Habilitar el reloj para los puertos 0 y 1 
		CLOCK_EnableClock(kCLOCK_Port0);
		CLOCK_EnableClock(kCLOCK_Port1);

		// Habilitar el reloj para los GPIO 0 y 1
		CLOCK_EnableClock(kCLOCK_Gpio0);
		CLOCK_EnableClock(kCLOCK_Gpio1);

		// Configurar los pines de salida para los LEDs RGB
		const port_pin_config_t output_config = 
		{// Inrenamente deshabilitado el pull-up/pull-down
			kPORT_PullDisable,
			/* Low internal pull resistor value is selected. */
			kPORT_LowPullResistor,
			/* Fast slew rate is configured */
			kPORT_FastSlewRate,
			/* Passive input filter is disabled */
			kPORT_PassiveFilterDisable,
			/* Open drain output is disabled */
			kPORT_OpenDrainDisable,
			/* Low drive strength is configured */
			kPORT_LowDriveStrength,
			/* Pin is configured as PIO0_10 */
			kPORT_MuxAlt0,
			/* Digital input enabled */
			kPORT_InputBufferEnable,
			/* Digital input is not inverted */
			kPORT_InputNormal,
			/* Pin Control Register fields [15:0] are not locked */
			kPORT_UnlockRegister
		};

		// Configurar los pines de salida para los LEDs RGB
		PORT_SetPinConfig(RED_LED_PORT, RED_LED_PIN, &output_config);
		PORT_SetPinConfig(GREEN_LED_PORT, GREEN_LED_PIN, &output_config);
		PORT_SetPinConfig(BLUE_LED_PORT, BLUE_LED_PIN, &output_config);

		// Inicializar los pines de salida para los LEDs RGB
		GPIO_PinInit(RED_LED_GPIO, RED_LED_PIN, &led_config);
		GPIO_PinInit(GREEN_LED_GPIO, GREEN_LED_PIN, &led_config);
		GPIO_PinInit(BLUE_LED_GPIO, BLUE_LED_PIN, &led_config);

}

void GPIO_config_SW(void)
{
		gpio_pin_config_t sw_config = {
			kGPIO_DigitalInput,
			0,
		};

		
		CLOCK_EnableClock(kCLOCK_Gpio0);
		CLOCK_EnableClock(kCLOCK_Port0);
    	

		// Configurar los pines de entrada para los botones SW2 y SW3
		const port_pin_config_t input_config = 
		{/* Inrenamente deshabilitado el pull-up/pull-down */
			kPORT_PullUp,
			/* Hi internal pull resistor value is selected. */
			kPORT_LowPullResistor,
			/* Fast slew rate is configured */
			kPORT_FastSlewRate,
			/* Passive input filter is disabled */
			kPORT_PassiveFilterEnable,
			/* Open drain output is disabled */
			kPORT_OpenDrainDisable,
			/* Low drive strength is configured */
			kPORT_LowDriveStrength,
			/* Pin is configured as PIO0_10 */
			kPORT_MuxAlt0,
			/* Digital input enabled */
			kPORT_InputBufferEnable,
			/* Digital input is not inverted */
			kPORT_InputNormal,
			/* Pin Control Register fields [15:0] are not locked */
			kPORT_UnlockRegister
		};

				// Configurar los pines de entrada para los botones SW2 y SW3
		PORT_SetPinConfig(SW2_PORT, SW2_PIN, &input_config);
		PORT_SetPinConfig(SW3_PORT, SW3_PIN, &input_config);

				// Inicializar los pines de entrada para los botones SW2 y SW3
		GPIO_PinInit(SW2_GPIO, SW2_PIN, &sw_config);
		GPIO_PinInit(SW3_GPIO, SW3_PIN, &sw_config);

		// Configurar la interrupcion para los pines de entrada de los botones SW2 y SW3
		GPIO_SetPinInterruptConfig(SW2_GPIO, SW2_PIN, kGPIO_InterruptFallingEdge);
		GPIO_SetPinInterruptConfig(SW3_GPIO, SW3_PIN, kGPIO_InterruptFallingEdge);

		// Limpiar posibles interrupciones anteriores
		GPIO_PinClearInterruptFlag(GPIO0, SW2_PIN);
		GPIO_PinClearInterruptFlag(GPIO0, SW3_PIN);
}
