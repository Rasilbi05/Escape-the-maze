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
 #define CANAL_JOYSTICK_X ADC_CANAL_0
 #define CANAL_JOYSTICK_Y ADC_CANAL_1
 #define CANAL_JOYSTICK_B ADC_CANAL_4
 #define UMBRAL_LUZ 200 								//Valor a partir del cual se iluminará el cono de visión del jugador
 #define UMBRAL_ABAJO_DERECHA 3900			//Valor límite para considerar un movimineto hacia abajo/derecha
 #define UMBRAL_ARRIBA_IZQUIERDA 100 		//Valor límite para considerar un movimiento hacia arriba/izquierda
 #define FRECUENCIA_PERIFERICOS 1e6
 
// ===== Perifericos - Constantes Publicas =====
/**
 * @brief Constantes para indicar la dirección hacia donde se pulsó el Joystick.
 * @ingroup Joystick
 */
typedef enum  {
  JOYSTICK_NADA = 0,
  JOYSTICK_ARRIBA = 1,
  JOYSTICK_ABAJO = 2,
  JOYSTICK_IZQUIERDA = 3,
  JOYSTICK_DERECHA = 4,
	JOYSTICK_CENTRO = 5
}joystick_dir;
 
 void inicializar_perifericos(uint32_t frecuencia_adc);
 uint16_t ldr_leer_valor(adc_canal_t canal);
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
 uint8_t joystick_leer(void);
 
 
 #endif //ADC_PERIFERICOS_H



