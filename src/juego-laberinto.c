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

void actualizar_posicion_jugador(uint16_t x, uint16_t y){
	//Actualizamos la posición del jugador
	J1.x = x;
	J1.y = y;
	
	//Si hay luz, actualizamos el cono de visión
	if(/*funcion encargada de comprobar el lcd*/){
		
	}else{//ponemos todo a oscuras
		
	}
}

void laberinto_inicializar(){
	
	//iniciamos el laberinto con todo a 0
	for(uint16_t i = 0; i < TAM_X; ++i){
		for(uint16_t j = 0; j < TAM_Y; ++j){
			Laberinto[i][j] = 0;
		}
	}
	
	//introducimos las paredes correspondientes al laberinto
	for(uint16_t i = 0; i < TAM_X/10; ++i){
		for(uint16_t j = 0; j < TAM_Y/10; ++j){
			if(PAREDES_LABERINTO[i][j] == 1){//hay una pared
				uint16_t correspondiente_x  = i*10;
				uint16_t correspondiente_y = j*10;
				for(uint16_t c = correspondiente_x; c < correspondiente_x + 10; ++c){
					for(uint16_t f = correspondiente_y; f < correspondiente_y + 10; ++f){
						if(f < TAM_X && c < TAM_Y){
							Laberinto[f][c] = 1;
						}
					}
				}
			}
		}
	}
	
	//Introducimos como posición del jugador la entrada al laberinto
	actualizar_posicion_jugador(ENTRADA_X, ENTRADA_Y);
	
}