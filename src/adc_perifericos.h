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
 #define UMBRAL_LUZ 200 								//Valor límite para iluinar el cono de visión del jugador
 #define UMBRAL_ABAJO_DERECHA 3900			//Valor límite para considerar un movimineto hacia abajo/derecha
 #define UMBRAL_ARRIBA_IZQUIERDA 100 		//Valor límite para considerar un movimiento hacia arriba/izquierda
 #define FRECUENCIA_PERIFERICOS 1e6

 
// ===== Perifericos - Constantes Publicas =====
/**
 * @brief Constantes para indicar la dirección hacia donde se pulsó el Joystick.
 * @ingroup Perifericos
 */
typedef enum  {
  JOYSTICK_NADA = 0,
  JOYSTICK_ARRIBA = 1,
  JOYSTICK_ABAJO = 2,
  JOYSTICK_IZQUIERDA = 3,
  JOYSTICK_DERECHA = 4,
	JOYSTICK_CENTRO = 5
}joystick_dir;

/**
 * @brief Constantes para indicar la iluminación del cono de visión.
 * @ingroup Perifericos
 */
typedef enum{
	OSCURO = 0,
	ILUMINADO = 1
}iluminacion;

/**
 * @brief   Inicializar los canales del asdc conectados a los perifericos y habilitar interrupciones de LDR.
 * @param 	frecuencia_adc Frecuencia a la que se va usar el adc de los periféricos.
 * @ingroup Perifericos
 */
 void inicializar_perifericos(uint32_t frecuencia_adc);

/**
 * @brief   Leer el valor del adc de la LDR y devolver un número según el valor retornado.
 * @ingroup Perifericos
 *
 * @retval  OSCURO/0 si el valor de la ldr es superior a UMBRAL_LUZ
 * @retval	ILUMINADO/1 si el valor de la ldr es inferior a UMBRAK_LUZ
 */
 uint8_t encender_linterna(void);

/**
 * @brief   Devuelve el valor del adc de la LDR mediante interrupciones.
 * @ingroup Perifericos
 
 * @retval  OSCURO/0 si el valor de la ldr es superior a UMBRAL_LUZ
 * @retval	ILUMINADO/1 si el valor de la ldr es inferior a UMBRAK_LUZ
 */
 uint8_t encender_linterna_int(void);
/**
 * @brief   Leer el joystick y retornar un número diferente según el valor del adc que se esté leyendo.
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



