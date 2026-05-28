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
	adc_inicializar(frecuencia_adc,CANAL_JOYSTICK);
}

uint16_t ldr_leer_valor(adc_canal_t canal){
	
	return adc_convertir(canal);

}