/**
	\file
	\brief
		This is the header file for the NVIC device driver for MCXN947.
		It contains some configuration functions and runtime functions.
		It is implemented using  CMSIS Core functions
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	27/07/2025
	\todo
	    Pending interrupts and disable interrupts are not enable.
 */

#ifndef NVIC_H_
#define NVIC_H_

#include <stdint.h>


#define NVIC_global_enable_interrupts __enable_irq()
#define NVIC_disable_interrupts __disable_irq()

/** enum type that defines the priority levels for the NVIC.
 * The highest priority is PRIORITY_0 and the lowest PRIORITY_15 */
typedef enum {PRIORITY_0, PRIORITY_1, PRIORITY_2, PRIORITY_3, PRIORITY_4, PRIORITY_5, PRIORITY_6,
			  PRIORITY_7, PRIORITY_8, PRIORITY_9, PRIORITY_10, PRIORITY_11, PRIORITY_12, PRIORITY_13,
			  PRIORITY_14, PRIORITY_15 } priority_level_t;

/** enum type that defines the IRQs for the NVIC.*/
typedef enum {
	 NVIC_OR_IRQn                      = 0,                /**< OR IRQ */
	 NVIC_EDMA_0_CH0_IRQn              = 1,                /**< eDMA_0_CH0 error or transfer complete */
	 NVIC_EDMA_0_CH1_IRQn              = 2,                /**< eDMA_0_CH1 error or transfer complete */
	 NVIC_EDMA_0_CH2_IRQn              = 3,                /**< eDMA_0_CH2 error or transfer complete */
	 NVIC_EDMA_0_CH3_IRQn              = 4,                /**< eDMA_0_CH3 error or transfer complete */
	 NVIC_EDMA_0_CH4_IRQn              = 5,                /**< eDMA_0_CH4 error or transfer complete */
	 NVIC_EDMA_0_CH5_IRQn              = 6,                /**< eDMA_0_CH5 error or transfer complete */
	 NVIC_EDMA_0_CH6_IRQn              = 7,                /**< eDMA_0_CH6 error or transfer complete */
	 NVIC_EDMA_0_CH7_IRQn              = 8,                /**< eDMA_0_CH7 error or transfer complete */
	 NVIC_EDMA_0_CH8_IRQn              = 9,                /**< eDMA_0_CH8 error or transfer complete */
	 NVIC_EDMA_0_CH9_IRQn              = 10,               /**< eDMA_0_CH9 error or transfer complete */
	 NVIC_EDMA_0_CH10_IRQn             = 11,               /**< eDMA_0_CH10 error or transfer complete */
	 NVIC_EDMA_0_CH11_IRQn             = 12,               /**< eDMA_0_CH11 error or transfer complete */
	 NVIC_EDMA_0_CH12_IRQn             = 13,               /**< eDMA_0_CH12 error or transfer complete */
	 NVIC_EDMA_0_CH13_IRQn             = 14,               /**< eDMA_0_CH13 error or transfer complete */
	 NVIC_EDMA_0_CH14_IRQn             = 15,               /**< eDMA_0_CH14 error or transfer complete */
	 NVIC_EDMA_0_CH15_IRQn             = 16,               /**< eDMA_0_CH15 error or transfer complete */
	 NVIC_GPIO00_IRQn                  = 17,               /**< GPIO0 interrupt 0 */
	 NVIC_GPIO01_IRQn                  = 18,               /**< GPIO0 interrupt 1 */
	 NVIC_GPIO10_IRQn                  = 19,               /**< GPIO1 interrupt 0 */
	 NVIC_GPIO11_IRQn                  = 20,               /**< GPIO1 interrupt 1 */
	 NVIC_GPIO20_IRQn                  = 21,               /**< GPIO2 interrupt 0 */
	 NVIC_GPIO21_IRQn                  = 22,               /**< GPIO2 interrupt 1 */
	 NVIC_GPIO30_IRQn                  = 23,               /**< GPIO3 interrupt 0 */
	 NVIC_GPIO31_IRQn                  = 24,               /**< GPIO3 interrupt 1 */
	 NVIC_GPIO40_IRQn                  = 25,               /**< GPIO4 interrupt 0 */
	 NVIC_GPIO41_IRQn                  = 26,               /**< GPIO4 interrupt 1 */
	 NVIC_GPIO50_IRQn                  = 27,               /**< GPIO5 interrupt 0 */
	 NVIC_GPIO51_IRQn                  = 28,               /**< GPIO5 interrupt 1 */
	 NVIC_UTICK0_IRQn                  = 29,               /**< Micro-Tick Timer interrupt */
	 NVIC_MRT0_IRQn                    = 30,               /**< Multi-Rate Timer interrupt */
	 NVIC_CTIMER0_IRQn                 = 31,               /**< Standard counter/timer 0 interrupt */
	 NVIC_CTIMER1_IRQn                 = 32,               /**< Standard counter/timer 1 interrupt */
	 NVIC_SCT0_IRQn                    = 33,               /**< SCTimer/PWM interrupt */
	 NVIC_CTIMER2_IRQn                 = 34,               /**< Standard counter/timer 2 interrupt */
	 NVIC_LP_FLEXCOMM0_IRQn            = 35,               /**< LP_FLEXCOMM0 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_LP_FLEXCOMM1_IRQn            = 36,               /**< LP_FLEXCOMM1 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_LP_FLEXCOMM2_IRQn            = 37,               /**< LP_FLEXCOMM2 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_LP_FLEXCOMM3_IRQn            = 38,               /**< LP_FLEXCOMM3 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_LP_FLEXCOMM4_IRQn            = 39,               /**< LP_FLEXCOMM4 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_LP_FLEXCOMM5_IRQn            = 40,               /**< LP_FLEXCOMM5 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_LP_FLEXCOMM6_IRQn            = 41,               /**< LP_FLEXCOMM6 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_LP_FLEXCOMM7_IRQn            = 42,               /**< LP_FLEXCOMM7 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_LP_FLEXCOMM8_IRQn            = 43,               /**< LP_FLEXCOMM8 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_LP_FLEXCOMM9_IRQn            = 44,               /**< LP_FLEXCOMM9 (LPSPI interrupt or LPI2C interrupt or LPUART Receive/Transmit interrupt) */
	 NVIC_ADC0_IRQn                    = 45,               /**< Analog-to-Digital Converter 0 - General Purpose interrupt */
	 NVIC_ADC1_IRQn                    = 46,               /**< Analog-to-Digital Converter 1 - General Purpose interrupt */
	 NVIC_PINT0_IRQn                   = 47,               /**< Pin Interrupt Pattern Match Interrupt */
	 NVIC_PDM_EVENT_IRQn               = 48,               /**< Microphone Interface interrupt */
	 NVIC_Reserved65_IRQn              = 49,               /**< Reserved interrupt */
	 NVIC_USB0_FS_IRQn                 = 50,               /**< Universal Serial Bus - Full Speed interrupt */
	 NVIC_USB0_DCD_IRQn                = 51,               /**< Universal Serial Bus - Device Charge Detect interrupt */
	 NVIC_RTC_IRQn                     = 52,               /**< RTC Subsystem interrupt (RTC interrupt or Wake timer interrupt) */
	 NVIC_SMARTDMA_IRQn                = 53,               /**< SmartDMA_IRQ */
	 NVIC_MAILBOX_IRQn                 = 54,               /**< Inter-CPU Mailbox interrupt0 for CPU0 Inter-CPU Mailbox interrupt1 for CPU1 */
	 NVIC_CTIMER3_IRQn                 = 55,               /**< Standard counter/timer 3 interrupt */
	 NVIC_CTIMER4_IRQn                 = 56,               /**< Standard counter/timer 4 interrupt */
	 NVIC_OS_EVENT_IRQn                = 57,               /**< OS event timer interrupt */
	 NVIC_FLEXSPI0_IRQn                = 58,               /**< Flexible Serial Peripheral Interface interrupt */
	 NVIC_SAI0_IRQn                    = 59,               /**< Serial Audio Interface 0 interrupt */
	 NVIC_SAI1_IRQn                    = 60,               /**< Serial Audio Interface 1 interrupt */
	 NVIC_USDHC0_IRQn                  = 61,               /**< Ultra Secured Digital Host Controller interrupt */
	 NVIC_CAN0_IRQn                    = 62,               /**< Controller Area Network 0 interrupt */
	 NVIC_CAN1_IRQn                    = 63,               /**< Controller Area Network 1 interrupt */
	 NVIC_Reserved80_IRQn              = 64,               /**< Reserved interrupt */
	 NVIC_Reserved81_IRQn              = 65,               /**< Reserved interrupt */
	 NVIC_USB1_HS_PHY_IRQn             = 66,               /**< USBHS DCD or USBHS Phy interrupt */
	 NVIC_USB1_HS_IRQn                 = 67,               /**< USB High Speed OTG Controller interrupt */
	 NVIC_SEC_HYPERVISOR_CALL_IRQn     = 68,               /**< AHB Secure Controller hypervisor call interrupt */
	 NVIC_Reserved85_IRQn              = 69,               /**< Reserved interrupt */
	 NVIC_PLU_IRQn                     = 70,               /**< Programmable Logic Unit interrupt */
	 NVIC_Freqme_IRQn                  = 71,               /**< Frequency Measurement interrupt */
	 NVIC_SEC_VIO_IRQn                 = 72,               /**< Secure violation interrupt (Memory Block Checker interrupt or secure AHB matrix violation interrupt) */
	 NVIC_ELS_IRQn                     = 73,               /**< ELS interrupt */
	 NVIC_PKC_IRQn                     = 74,               /**< PKC interrupt */
	 NVIC_PUF_IRQn                     = 75,               /**< Physical Unclonable Function interrupt */
	 NVIC_PQ_IRQn                      = 76,               /**< Power Quad interrupt */
	 NVIC_EDMA_1_CH0_IRQn              = 77,               /**< eDMA_1_CH0 error or transfer complete */
	 NVIC_EDMA_1_CH1_IRQn              = 78,               /**< eDMA_1_CH1 error or transfer complete */
	 NVIC_EDMA_1_CH2_IRQn              = 79,               /**< eDMA_1_CH2 error or transfer complete */
	 NVIC_EDMA_1_CH3_IRQn              = 80,               /**< eDMA_1_CH3 error or transfer complete */
	 NVIC_EDMA_1_CH4_IRQn              = 81,               /**< eDMA_1_CH4 error or transfer complete */
	 NVIC_EDMA_1_CH5_IRQn              = 82,               /**< eDMA_1_CH5 error or transfer complete */
	 NVIC_EDMA_1_CH6_IRQn              = 83,               /**< eDMA_1_CH6 error or transfer complete */
	 NVIC_EDMA_1_CH7_IRQn              = 84,               /**< eDMA_1_CH7 error or transfer complete */
	 NVIC_EDMA_1_CH8_IRQn              = 85,               /**< eDMA_1_CH8 error or transfer complete */
	 NVIC_EDMA_1_CH9_IRQn              = 86,               /**< eDMA_1_CH9 error or transfer complete */
	 NVIC_EDMA_1_CH10_IRQn             = 87,               /**< eDMA_1_CH10 error or transfer complete */
	 NVIC_EDMA_1_CH11_IRQn             = 88,               /**< eDMA_1_CH11 error or transfer complete */
	 NVIC_EDMA_1_CH12_IRQn             = 89,               /**< eDMA_1_CH12 error or transfer complete */
	 NVIC_EDMA_1_CH13_IRQn             = 90,               /**< eDMA_1_CH13 error or transfer complete */
	 NVIC_EDMA_1_CH14_IRQn             = 91,               /**< eDMA_1_CH14 error or transfer complete */
	 NVIC_EDMA_1_CH15_IRQn             = 92,               /**< eDMA_1_CH15 error or transfer complete */
	 NVIC_CDOG0_IRQn                   = 93,               /**< Code Watchdog Timer 0 interrupt */
	 NVIC_CDOG1_IRQn                   = 94,               /**< Code Watchdog Timer 1 interrupt */
	 NVIC_I3C0_IRQn                    = 95,               /**< Improved Inter Integrated Circuit interrupt 0 */
	 NVIC_I3C1_IRQn                    = 96,               /**< Improved Inter Integrated Circuit interrupt 1 */
	 NVIC_Reserved113_IRQn             = 97,               /**< Reserved interrupt */
	 NVIC_GDET_IRQn                    = 98,               /**< Digital Glitch Detect 0 interrupt  or Digital Glitch Detect 1 interrupt */
	 NVIC_VBAT0_IRQn                   = 99,               /**< VBAT interrupt( VBAT interrupt or digital tamper interrupt) */
	 NVIC_EWM0_IRQn                    = 100,              /**< External Watchdog Monitor interrupt */
	 NVIC_TSI_END_OF_SCAN_IRQn         = 101,              /**< TSI End of Scan interrupt */
	 NVIC_TSI_OUT_OF_SCAN_IRQn         = 102,              /**< TSI Out of Scan interrupt */
	 NVIC_EMVSIM0_IRQn                 = 103,              /**< EMVSIM0 interrupt */
	 NVIC_EMVSIM1_IRQn                 = 104,              /**< EMVSIM1 interrupt */
	 NVIC_FLEXIO_IRQn                  = 105,              /**< Flexible Input/Output interrupt */
	 NVIC_DAC0_IRQn                    = 106,              /**< Digital-to-Analog Converter 0 - General Purpose interrupt */
	 NVIC_DAC1_IRQn                    = 107,              /**< Digital-to-Analog Converter 1 - General Purpose interrupt */
	 NVIC_DAC2_IRQn                    = 108,              /**< 14-bit Digital-to-Analog Converter interrupt */
	 NVIC_HSCMP0_IRQn                  = 109,              /**< High-Speed comparator0 interrupt */
	 NVIC_HSCMP1_IRQn                  = 110,              /**< High-Speed comparator1 interrupt */
	 NVIC_HSCMP2_IRQn                  = 111,              /**< High-Speed comparator2 interrupt */
	 NVIC_FLEXPWM0_RELOAD_ERROR_IRQn   = 112,              /**< FlexPWM0_reload_error interrupt */
	 NVIC_FLEXPWM0_FAULT_IRQn          = 113,              /**< FlexPWM0_fault interrupt */
	 NVIC_FLEXPWM0_SUBMODULE0_IRQn     = 114,              /**< FlexPWM0 Submodule 0 capture/compare/reload interrupt */
	 NVIC_FLEXPWM0_SUBMODULE1_IRQn     = 115,              /**< FlexPWM0 Submodule 1 capture/compare/reload interrupt */
	 NVIC_FLEXPWM0_SUBMODULE2_IRQn     = 116,              /**< FlexPWM0 Submodule 2 capture/compare/reload interrupt */
	 NVIC_FLEXPWM0_SUBMODULE3_IRQn     = 117,              /**< FlexPWM0 Submodule 3 capture/compare/reload interrupt */
	 NVIC_FLEXPWM1_RELOAD_ERROR_IRQn   = 118,              /**< FlexPWM1_reload_error interrupt */
	 NVIC_FLEXPWM1_FAULT_IRQn          = 119,              /**< FlexPWM1_fault interrupt */
	 NVIC_FLEXPWM1_SUBMODULE0_IRQn     = 120,              /**< FlexPWM1 Submodule 0 capture/compare/reload interrupt */
	 NVIC_FLEXPWM1_SUBMODULE1_IRQn     = 121,              /**< FlexPWM1 Submodule 1 capture/compare/reload interrupt */
	 NVIC_FLEXPWM1_SUBMODULE2_IRQn     = 122,              /**< FlexPWM1 Submodule 2 capture/compare/reload interrupt */
	 NVIC_FLEXPWM1_SUBMODULE3_IRQn     = 123,              /**< FlexPWM1 Submodule 3 capture/compare/reload interrupt */
	 NVIC_QDC0_COMPARE_IRQn            = 124,              /**< QDC0_Compare interrupt */
	 NVIC_QDC0_HOME_IRQn               = 125,              /**< QDC0_Home interrupt */
	 NVIC_QDC0_WDG_SAB_IRQn            = 126,              /**< QDC0_WDG_IRQ/SAB interrupt */
	 NVIC_QDC0_IDX_IRQn                = 127,              /**< QDC0_IDX interrupt */
	 NVIC_QDC1_COMPARE_IRQn            = 128,              /**< QDC1_Compare interrupt */
	 NVIC_QDC1_HOME_IRQn               = 129,              /**< QDC1_Home interrupt */
	 NVIC_QDC1_WDG_SAB_IRQn            = 130,              /**< QDC1_WDG_IRQ/SAB interrupt */
	 NVIC_QDC1_IDX_IRQn                = 131,              /**< QDC1_IDX interrupt */
	 NVIC_ITRC0_IRQn                   = 132,              /**< Intrusion and Tamper Response Controller interrupt */
	 NVIC_BSP32_IRQn                   = 133,              /**< CoolFlux BSP32 interrupt */
	 NVIC_ELS_ERR_IRQn                 = 134,              /**< ELS error interrupt */
	 NVIC_PKC_ERR_IRQn                 = 135,              /**< PKC error interrupt */
	 NVIC_ERM_SINGLE_BIT_ERROR_IRQn    = 136,              /**< ERM Single Bit error interrupt */
	 NVIC_ERM_MULTI_BIT_ERROR_IRQn     = 137,              /**< ERM Multi Bit error interrupt */
	 NVIC_FMU0_IRQn                    = 138,              /**< Flash Management Unit interrupt */
	 NVIC_ETHERNET_IRQn                = 139,              /**< Ethernet QoS interrupt */
	 NVIC_ETHERNET_PMT_IRQn            = 140,              /**< Ethernet QoS power management interrupt */
	 NVIC_ETHERNET_MACLP_IRQn          = 141,              /**< Ethernet QoS MAC interrupt */
	 NVIC_SINC_FILTER_IRQn             = 142,              /**< SINC Filter interrupt  */
	 NVIC_LPTMR0_IRQn                  = 143,              /**< Low Power Timer 0 interrupt */
	 NVIC_LPTMR1_IRQn                  = 144,              /**< Low Power Timer 1 interrupt */
	 NVIC_SCG_IRQn                     = 145,              /**< System Clock Generator interrupt */
	 NVIC_SPC_IRQn                     = 146,              /**< System Power Controller interrupt */
	 NVIC_WUU_IRQn                     = 147,              /**< Wake Up Unit interrupt */
	 NVIC_PORT_EFT_IRQn                = 148,              /**< PORT0~5 EFT interrupt */
	 NVIC_ETB0_IRQn                    = 149,              /**< ETB counter expires interrupt */
	 NVIC_Reserved166_IRQn             = 150,              /**< Reserved interrupt */
	 NVIC_Reserved167_IRQn             = 151,              /**< Reserved interrupt */
	 NVIC_WWDT0_IRQn                   = 152,              /**< Windowed Watchdog Timer 0 interrupt */
	 NVIC_WWDT1_IRQn                   = 153,              /**< Windowed Watchdog Timer 1 interrupt */
	 NVIC_CMC0_IRQn                    = 154,              /**< Core Mode Controller interrupt */
	 NVIC_CTI0_IRQn                    = 155               /**< Cross Trigger Interface interrup*/
} interrupt_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables a IRQ in the NVIC and establishes its priority.

 	 \param[in] interruptNumber is the desired IRQ to be activivated.
 	 \param[in] priority establishes the priority of the IRQ
 	 \return void
 */
void NVIC_enable_interrupt_and_priotity(interrupt_t interrupt_number, priority_level_t priority);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function establishes the threshold level to interrupt the MCU.

 	 \param[in]  priority threshold to be established.
 	 \return void
 	 \todo Implement a mechanism to clear interrupts by a specific pin.
 */
void NVIC_set_basepri_threshold(priority_level_t priority);

#endif /* NVIC_H_ */
