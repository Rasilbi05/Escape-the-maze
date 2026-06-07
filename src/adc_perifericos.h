/**
 * @file    adc_perifericos.h
 * @brief   Funciones y  macros para el manejo de los perifericos del juego.
 *
 * @author  Jose Carlos Leal Iglesias
 * @author  Raul Silva Bienvenido
 * @date    2026
 * @version 1.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef ADC_PERIFERICOS_H
#define ADC_PERIFERICOS_H

#include "tipos.h"
#include "adc_lpc40xx.h"
#include "gpio_lpc40xx.h"

#define CANAL_LDR            ADC_CANAL_5
#define CANAL_JOYSTICK_X     ADC_CANAL_0
#define CANAL_JOYSTICK_Y     ADC_CANAL_1
#define UMBRAL_LUZ           200   //Valor limite para iluinar el cono de vision del jugador
#define UMBRAL_ABAJO_DERECHA 3900  //Valor limite para considerar un movimineto hacia abajo/derecha
#define UMBRAL_ARRIBA_IZQUIERDA                                                                    \
  100  //Valor limite para considerar un movimiento hacia arriba/izquierda
#define FRECUENCIA_PERIFERICOS 1e6
#define PULSADO                0

// ===== Perifericos - Constantes Publicas =====
/**
 * @brief Constantes para indicar la direccion hacia donde se pulsa el Joystick.
 * @ingroup Perifericos
 */
typedef enum {
  JOYSTICK_NADA      = 0,
  JOYSTICK_ARRIBA    = 1,
  JOYSTICK_ABAJO     = 2,
  JOYSTICK_IZQUIERDA = 3,
  JOYSTICK_DERECHA   = 4,
  JOYSTICK_CENTRO    = 5
} joystick_dir;

/**
 * @brief Constantes para indicar la iluminacion del cono de vision.
 * @ingroup Perifericos
 */
typedef enum { OSCURO = 0, ILUMINADO = 1 } iluminacion;

//========= FUNCIONES PUBLICAS ==========

/**
 * @brief   Inicializar los canales del adc conectados a los perifericos.
 * @param 	frecuencia_adc Frecuencia a la que se va usar el adc de los perifiricos.
 * @ingroup Perifericos
 */
void inicializar_perifericos(uint32_t frecuencia_adc);

/**
 * @brief   Leer el valor del adc de la LDR y devolver un numero segun el valor retornado.
 * @ingroup Perifericos
 *
 * @retval  OSCURO/0 si el valor de la ldr es superior a UMBRAL_LUZ
 * @retval	ILUMINADO/1 si el valor de la ldr es inferior a UMBRAK_LUZ
 */
uint8_t encender_linterna(void);

/**
 * @brief   Leer el joystick y retornar un numero diferente segun el valor del adc que se este leyendo.
 * @ingroup Perifericos
 *
 * @retval  JOYSTICK_NADA/0 si no se esta pulsando ninguna direccion.
 * @retval  JOYSTICK_ARRIBA/1 si el joystick esta pulsado hacia ARRIBA.
 * @retval  JOYSTICK_ABAJO/2 si el joystick esta pulsado hacia ABAJO.
 * @retval  JOYSTICK_IZQUIERDA/3 si el joystick esta pulsado hacia la IZQUIERDA.
 * @retval  JOYSTICK_DERECHA/4 si el joystick esta pulsado hacia la DERECHA.
 * @retval  JOYSTICK_CENTRO/5 si el joystick esta pulsado hacia el CENTRO.
 */
uint8_t joystick_leer(void);

#endif  //ADC_PERIFERICOS_H
