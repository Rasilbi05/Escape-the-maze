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

void laberinto_inicializar(){
	
	//creamos un vector con las paredes que apareceran en el laberinto
	Pared paredes[]={
		{0, 0, 480, 10},		//límite superior
		{260, 0, 480, 10},	//límite inferior
		{0, 0, 10, 270},		//límite izquierdo
		{0, 460, 10, 270},	//límite derecho
		//PAREDES DEL LABERINTO
		
	};
	
	uint16_t num_paredes = sizeof(paredes) / sizeof(Pared);
	
	//rellenamos la matriz Laberinto con 0s
	for(uint16_t i = 0; i<270; ++i){
		for(uint16_t j = 0; j<480; ++j){
			Laberinto[i][j] = 0;
		}
	}
	
	//introducimos las paredes en el laberinto
	for(uint16_t k = 0; k<num_paredes; ++k){
		uint16_t fila_inicio = paredes[k].x;
		uint16_t fila_final = paredes[k].x + paredes[k].alto;
		uint16_t columna_inicio = paredes[k].y;
		uint16_t columna_final = paredes[k].y + paredes[k].ancho;
		
		//comprobamos que no sobrepasen los valores
		if(fila_final > 270){
				fila_final = 270;
		}
		
		if(columna_final > 480){
				columna_final = 480;
		}
		
		//introducimos las paredes
		for(uint16_t i = fila_inicio; i<fila_final;++i){
			for(uint16_t j = columna_inicio; j<columna_final; ++j){
				Laberinto[i][j] = 1;			
			}
		}
		
	}
	
	
}