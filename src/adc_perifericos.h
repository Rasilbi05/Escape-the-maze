/**
 * @file    adc_perifericos.h
 * @brief   Funciones y  macros para el manejo de los periféricos del juego.
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
 
 #include "adc_lpc40xx.h"
 #include "tipos.h"
 
 #define CANAL_LDR ADC_CANAL_5
 #define CANAL_JOYSTICK ADC_CANAL_0
 #define UMBRAL_LUZ 2500 //Valor a partir del cual se iluminará el cono de visión del jugador
 
 void inicializar_perifericos(uint32_t frecuencia_adc);
 uint16_t ldr_leer_valor(adc_canal_t canal);
 
 
 #endif //ADC_PERIFERICOS_H



