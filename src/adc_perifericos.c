/**
 * @file    adc_perifericos.c
 * @brief   Funciones necesarias para leer los valores analógicos de la LDR y del joystick.
 *
 * @author  Jose Carlos Leal Iglesias
 * @author  Raul Silva Bienvenido
 * @date	2026
 * @version 1.0
 *
 * @copyright GNU General Public License version 3 or later
 *
 * 
 */

#include "adc_perifericos.h"
#include <math.h>


void inicializar_perifericos(uint32_t frecuencia_adc){
	adc_inicializar(frecuencia_adc,CANAL_LDR);
	adc_inicializar(frecuencia_adc,CANAL_JOYSTICK_X);
	adc_inicializar(frecuencia_adc,CANAL_JOYSTICK_Y);
}

uint16_t ldr_leer_valor(adc_canal_t canal){
	
	return adc_convertir(canal);

}

/**
 * @brief   Leer el joystick y retornar un número diferente según la dirección que se esté pulsando.
 * @ingroup Perifericos
 *
 * @retval  JOYSTICK_NADA/0 si no se está pulsando ningúna dirección.
 * @retval  JOYSTICK_ARRIBA/1 si el joystick está pulsado hacia ARRIBA.
 * @retval  JOYSTICK_ABAJO/2 si el joystick está pulsado hacia ABAJO.
 * @retval  JOYSTICK_IZQUIERDA/3 si el joystick está pulsado hacia la IZQUIERDA.
 * @retval  JOYSTICK_DERECHA/4 si el joystick está pulsado hacia la DERECHA.
 * @retval  JOYSTICK_CENTRO/5 si el joystick está pulsado hacia el CENTRO.
 */
uint8_t joystick_leer(void){
	if (adc_convertir(CANAL_JOYSTICK_X) > UMBRAL_ABAJO_DERECHA){
		return JOYSTICK_DERECHA;
	}
	if (adc_convertir(CANAL_JOYSTICK_X) < UMBRAL_ARRIBA_IZQUIERDA){
		return JOYSTICK_IZQUIERDA;
	}
	if (adc_convertir(CANAL_JOYSTICK_Y) > UMBRAL_ABAJO_DERECHA){
		return JOYSTICK_ABAJO;
	}
	if (adc_convertir(CANAL_JOYSTICK_Y) < UMBRAL_ARRIBA_IZQUIERDA){
		return JOYSTICK_ARRIBA;
	}
	if (adc_convertir(CANAL_JOYSTICK_B) < UMBRAL_ARRIBA_IZQUIERDA){
		return JOYSTICK_CENTRO;
	}
	return JOYSTICK_NADA;
}
