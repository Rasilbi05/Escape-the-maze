/**
 * @file    juego-laberinto.c
 * @brief   Definición e implementación de funciones para jugar al laberinto
 *
 * @author  Raúl Silva Bienvenido
 * @author  Jose Carlos Leal Iglesias
 * @date    2026-05-21
 * @version 1.0
 *
 * @copyright GNU General Public License version 3 or later
*/

#include "juego-laberinto.h"

//========== DEFINICIÓN DE MATRICES UTILIZADAS ==========
/**
* @brief	 Variable en la que se almacenen todos los datos del jugador
* @ingroup Laberinto
*/
volatile Jugador J1;

/**
* @brief   Valores iniciales de las paredes del laberinto
* @ingroup Laberinto
* @note	   Los ejes están invertidos, ya que hemos representado la matriz de forma horizontal por comodidad visual y semejanza a la pantalla real	
*/
const uint8_t PAREDES_LABERINTO[GLCD_TAMANO_Y/10][GLCD_TAMANO_X/10] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1},
    {1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1},
    {1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,1},
    {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1},
    {1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1},
    {1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,1},
    {1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1},
    {1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,1},
    {1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,1},
    {1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1,1},
    {1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,1},
    {1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,1},
    {1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1},
    {1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,1},
    {1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,1},
    {1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1},
    {1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1},
    {1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/**
*	@brief 	 Matriz de visión del jugador
* @ingroup Laberinto
*/
const uint8_t Vision[VISION][VISION] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};



void dibujar_cono_vision(uint16_t x, uint16_t y, joystick_dir direccion, uint8_t borrar) {
  //variables que nos servirán para realizar la rotación correspondiente a la dirección del jugador
	int8_t dir_x = 0, dir_y = 0, per_x = 0, per_y = 0;
    
	switch(direccion){
		case JOYSTICK_ARRIBA:      dir_x = 0;  dir_y = -1; per_x = 1;  per_y = 0;  break; 
    case JOYSTICK_ABAJO:       dir_x = 0;  dir_y = 1;  per_x = -1; per_y = 0;  break; 
    case JOYSTICK_DERECHA:     dir_x = 1;  dir_y = 0;  per_x = 0;  per_y = 1;  break; 
    case JOYSTICK_IZQUIERDA:   dir_x = -1; dir_y = 0;  per_x = 0;  per_y = -1; break; 
    default:                   dir_x = 0;  dir_y = 0;  per_x = 0;  per_y = 0;  break;
	}
    
  //obtenemos la posición del jugador de la matriz de visión
	uint16_t centro = VISION / 2;
  //recorremos la matriz para mostrar las paredes según su cono de visión
	for(uint16_t i = 0; i < VISION; ++i){
		for(uint16_t j = 0; j < VISION; ++j){
			//hay una pared, o el propio jugador
			if(Vision[i][j] != 0){ 
				int16_t frente = centro - i;
				int16_t lateral = j - centro;
        //calculamos las coordenadas respecto al laberinto original
				int16_t laberinto_x = x + (frente * dir_x) + (lateral * per_x);
				int16_t laberinto_y = y + (frente * dir_y) + (lateral * per_y);
        //comprobamos que las coordenadas están en el rango permitido
				if(laberinto_x >= GLCD_X_MINIMO && laberinto_x <= GLCD_X_MAXIMO && 
				 laberinto_y >= GLCD_Y_MINIMO && laberinto_y <= GLCD_Y_MAXIMO){
					 //obtenemos la coordenada simplificada
					uint16_t bloque_x = laberinto_x / 10;
					uint16_t bloque_y = laberinto_y / 10;
					
					//controlamos que no haya desbordamiento
					if(bloque_x >= GLCD_TAMANO_X/10)
						bloque_x = GLCD_TAMANO_X/10 - 1;
					if(bloque_y >= GLCD_TAMANO_Y/10)
						bloque_y = GLCD_TAMANO_Y/10 - 1;
					//si se quiere borrar, pintamos la coordenada de negro
					if(borrar){
						glcd_punto(laberinto_x, laberinto_y, NEGRO); 
					}else{       
						if(PAREDES_LABERINTO[bloque_y][bloque_x] == PARED){
							glcd_punto(laberinto_x, laberinto_y, BLANCO);  //Hay pared
						}else if(Vision[i][j] == JUGADOR){
							glcd_punto(laberinto_x, laberinto_y, ROJO);
					}else{
							glcd_punto(laberinto_x, laberinto_y, NEGRO);	////No hay pared, es el pasillo
						}
					}
				}
			}
		}
	}
}

void actualizar_posicion_jugador(uint16_t x, uint16_t y, joystick_dir direccion){
	
	//Borramos las coordenadas previas
	dibujar_cono_vision(J1.x, J1.y, J1.ultima_direccion, 1);
	
	//Actualizamos la posición del jugador
	J1.x = x;
	J1.y = y;
	J1.ultima_direccion = direccion;
	
	//Si está la linterna activa, mostramos lo que tenga el personaje por delante
	if(encender_linterna() == ILUMINADO){
		dibujar_cono_vision(x, y, direccion, 0);
	}else{
		dibujar_cono_vision(x,y,direccion, 1);
	}

}

void laberinto_inicializar(){
	
	//inicializamos las dependencias para poder jugar
	glcd_inicializar();
	inicializar_perifericos(FRECUENCIA_PERIFERICOS);
	timer_inicializar(TIMER0);
	
}

bool_t movimiento_valido(uint16_t x, uint16_t y){
	
	//comprobamos que los valores estén dentro del rango permitido
	if(x >= 0 && x < GLCD_TAMANO_X && y >= 0 && y < GLCD_TAMANO_Y){
		//adaptamos las coordenadas
		uint16_t bloque_x = x/10;
		uint16_t bloque_y = y/10;
		if(bloque_x >= GLCD_TAMANO_X/10){
			bloque_x = GLCD_TAMANO_X/10 - 1;
		}
		if(bloque_y >= GLCD_TAMANO_Y/10){
			bloque_y = GLCD_TAMANO_Y/10 - 1;
		}
		//Comprobamos en la matriz de visión si hay o no una pared
		if(PAREDES_LABERINTO[bloque_y][bloque_x] == 1){
			return FALSE;
		}else{
			return TRUE;
		}
	}else{
		return FALSE;
	}

}

void comenzar_juego(){
	
	//recreamos una pantalla de inicio
	timer_iniciar_ciclos_ms(TIMER0, 450);		//timer para simular un parpadeo de texto
	glcd_borrar(NEGRO);
	
	const char *logo[] = {
        " ______                               ",
        "|  ____|                              ",
        "| |__   ___  ___ __ _ _ __   ___      ",
        "|  __| / __|/ __/ _` | '_ \\ / _ \\     ",
        "| |____\\__ \\ (_| (_| | |_) |  __/     ",
        "|______|___/\\___\\__,_| .__/ \\___|     ",
        "                     | |              ",
        "                     |_|              ",
        " _______ _             __  __                  ",
        "|__   __| |           |  \\/  |                 ",
        "   | |  | |__   ___   | \\  / | __ _ _______  ",
        "   | |  | '_ \\ / _ \\  | |\\/| |/ _` |_  / _ \\",
        "   | |  | | | |  __/  | |  | | (_| |/ /  __/  ",
        "   |_|  |_| |_|\\___|  |_|  |_|\\__,_/___\\___/ "
	};

	//Calculamnos el número de líneas del logo
	uint8_t lineas = sizeof(logo) / sizeof(logo[0]);
    
	//dibujamos cada línea por separado
	for(uint8_t i = 0; i < lineas; ++i){
			glcd_texto(0, 0 + (i * 16), GREEN, BLACK, FUENTE8X16, logo[i]);
	}
	
	//parpadeo del mensaje
	do{
		glcd_rectangulo_relleno(315, 40, 475, 110, NEGRO);
		timer_esperar_fin_ciclo(TIMER0);
		glcd_xprintf(315, 50, WHITE, NEGRO, FUENTE8X16," PULSE EL JOYSTICK ");
		glcd_xprintf(315, 70, WHITE, NEGRO, FUENTE8X16,"   PARA COMENZAR   ");
		timer_esperar_fin_ciclo(TIMER0);
	}while(joystick_leer() != JOYSTICK_CENTRO);
		
	//comienza el juego
	glcd_borrar(NEGRO);
	actualizar_posicion_jugador(ENTRADA_X, ENTRADA_Y, JOYSTICK_DERECHA);
	timer_esperar_fin_ciclo(TIMER0);		//espera un poco para no empezar al instante
	
	//creamos un pequeño delay para el movimiento
	timer_iniciar_ciclos_ms(TIMER0, 15);
	
	//blucle del juego
	while(J1.x < SALIDA_X || J1.y < SALIDA_Y){
		timer_esperar_fin_ciclo(TIMER0);
		//obtenemos la dirección leída por el joystick y vamos actualizando la posición del jugador
		joystick_dir nueva_direccion = joystick_leer();
		switch(nueva_direccion){
			case JOYSTICK_ARRIBA:
				if(movimiento_valido(J1.x, J1.y-1)){
					actualizar_posicion_jugador(J1.x, J1.y - 1, nueva_direccion);
				}
			break;
			case JOYSTICK_ABAJO:
				if(movimiento_valido(J1.x, J1.y + 1)){
					actualizar_posicion_jugador(J1.x, J1.y + 1, nueva_direccion);
				}
			break;
			case JOYSTICK_IZQUIERDA:
				if(movimiento_valido(J1.x-1, J1.y)){
					actualizar_posicion_jugador(J1.x - 1, J1.y, nueva_direccion);
				}
			break;
			case JOYSTICK_DERECHA:
				if(movimiento_valido(J1.x+1, J1.y)){
					actualizar_posicion_jugador(J1.x + 1, J1.y, nueva_direccion);
				}
			break;
			default:
			break;
		}
	}
	
	//una vez finalizado el laberinto, mostramos una pantalla de final y despues de 5 segundos, vuelve al inicio
	timer_iniciar_ciclos_ms(TIMER0, 5000);
	glcd_xprintf(0, GLCD_TAMANO_Y/2, VERDE, NEGRO, FUENTE8X16, "\t    Felicidades! Escapate del laberinto");
	timer_esperar_fin_ciclo(TIMER0);
	
}
