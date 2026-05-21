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

//========== DEFINICIÓN DE MATRICES UTILIZADAS ==========
/**
* @brief Matriz que representa al laberinto en su completitud
* @ingroup Laberinto
*/
volatile uint8_t Laberinto[270][480];

/**
* @brief   Matriz que representa el cono de visión del jugador
* @ingroup Laberinto
*/
volatile uint8_t Jugador[40][40];

/**
* @brief   Almacena las coordenadas x e y de una pared
* @ingroup Laberinto
*/
struct{
	uint16_t  x, y, ancho, alto;
}typedef Pared;

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