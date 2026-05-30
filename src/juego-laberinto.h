/**
 * @file    juego-laberinto.h
 * @brief   Definición e implementación de funciones para jugar al laberinto
 *
 * @author  Raúl Silva Bienvenido
 * @author  Jose Carlos Leal Iglesias
 * @date    2026-05-21
 * @version 1.0
 *
 * @copyright GNU General Public License version 3 or later
*/

#include "tipos.h"
#include "adc_perifericos.h"
#include "glcd.h"
#include "timer_lpc40xx.h"
#define ENTRADA_X		0
#define ENTRADA_Y		10
#define SALIDA_X		250
#define SALIDA_Y		460
#define VISION			50
#define PARED				1
#define JUGADOR			3


/**
* @brief	 Tipo jugador para mantener toda su información
* @ingroup Laberinto
*/
typedef struct{
	uint16_t x, y;
	joystick_dir ultima_direccion;
}Jugador;


//========= FUNCIONES PRIVADAS ==========
/**
*	@brief 	 Función encargada de, en base a las nuevas coordenadas, actualizar la posición del jugador junto a su cono de visión
* @ingroup Laberinto
*/
void actualizar_posicion_jugador(uint16_t x, uint16_t y, joystick_dir direccion);

/**
* @brief   Dibuja o borra el cono de visión del jugador directamente en la pantalla LCD.
* @param   centro_x Coordenada X global
* @param   centro_y Coordenada Y global
* @param   direccion Dirección hacia la que apunta el joystick
* @param   borrar 1 para apagar la luz (pintar de negro), 0 para renderizar el escenario
* @ingroup Laberinto
 */
void dibujar_cono_vision(uint16_t centro_x, uint16_t centro_y, uint8_t direccion, uint8_t borrar);

//========= FUNCIONES PÚBLICAS ==========
/**
* @brief Función inicializadora de las matrices Laberinto y Jugador
* @ingroup Laberinto
*/
void laberinto_inicializar();
/**
* @brief Función encargada de comenzar el juego
* @ingroup Laberinto
*/
void comenzar_juego();
