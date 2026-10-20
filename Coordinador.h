/*
 * Coordinador.h
 *
 *  Created on: 19 oct. 2026
 *      Author: Santiago Queen ✨
 */

#ifndef COORDINADOR_H_
#define COORDINADOR_H_

#include <stdint.h>


// Tiempos
#define TIEMPO_BLANCO_MS    (1000U)
#define TIEMPO_VERDE_MS     (1000U)
#define TIEMPO_CONTEO_MS    (7000U)
#define ANTIRREBOTE_MS     (50U)

typedef enum
{
    EST_ESPERAR_INICIO,
    EST_BLANCO_1,
    EST_APAGADO_1,
    EST_BLANCO_2,
    EST_APAGADO_2,
    EST_ESPERAR_SW2,
    EST_VERDE,
    EST_CONTAR_SW3,
    EST_MOSTRAR_COLOR

} estado_t;

void COOR_Inicio(void);
// Procesar el estado actual
void COOR_Procesar(void);

#endif /* COORDINADOR_H_ */
