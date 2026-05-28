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
	
	//Quitamos las luces previas
	for(uint16_t i = 0; i < TAM_X; ++i){
		for(uint16_t j = 0; j < TAM_Y; ++j){
			if(Laberinto[i][j] == LUZ){
				Laberinto[i][j] = OSCURIDAD;
			}else if(Laberinto[i][j] == JUGADOR){
				Laberinto[i][j] = 0;
			}
		}
	}
	
	//Actualizamos la posición del jugador
	J1.x = x;
	J1.y = y;
	
	//Si hay luz, actualizamos el cono de visión
	if(/*funcion encargada de comprobar el lcd*/){
		int8_t dir_x = 0, dir_y = 0, per_x = 0, per_y = 0;
		
		switch(J1.ultima_direccion){
			case JOYSTICK_ARRIBA:
				dir_x = -1; dir_y = 0; per_x = 0; per_y = 1;
			break;
			case JOYSTICK_ABAJO:
				dir_x = 1; dir_y = 0; per_x = 0; per_y = -1;
			break;
			case JOYSTICK_DERECHA:
				dir_x = 0; dir_y = 1; per_x = 1; per_y = 0;
			break;
			case JOYSTICK_IZQUIERDA:
				dir_x = 0; dir_y = -1; per_x = -1; per_y = 0;
			break;
			default:
				dir_x = 0; dir_y = 0; per_x = 0; per_y = 0;
			break;
		}
		
		uint16_t centro = VISION/2;
		//recorremos el cono de visión para actualizar el laberinto
		for(uint16_t i = 0; i<VISION; ++i){
			for(uint16_t j = 0; j<VISION;++j){
				if(Vision[i][j] == 1){
					//distancias respecto al centro
					int16_t frente = centro - i;
					int16_t lateral = j - centro;
					
					//calculamos las coordenadas con respecto al laberinto
					int16_t laberinto_x = J1.x + (frente*dir_x) + (lateral*per_x);
					int16_t laberinto_y = J1.y + (frente*dir_y) + (lateral*per_y);
					
					//actualizamos los valores en el laberinto
					if(laberinto_x >= 0 && laberinto_x < TAM_X && laberinto_y >= 0 && laberinto_y < TAM_Y){
						if(Laberinto[laberinto_x][laberinto_y] == 1){	//hay pared
							Laberinto[laberinto_x][laberinto_y] = LUZ;
						}
					}
				}
			}
		}	
	}

	//marcamos las casillas del jugador
	for(int16_t dx = -5; dx < 5; ++dx){
		for(int16_t dy = -5; dy < 5; ++dy){
			int16_t jug_x = J1.x + dx;
			int16_t jug_y = J1.y + dy;
			if(jug_x >= 0 && jug_x < TAM_X && jug_y >= 0 && jug_y < TAM_Y){
					Laberinto[jug_x][jug_y] = JUGADOR;
			}
		}
	}	
}

void laberinto_inicializar(){
	
	//inicializamos las dependencias para poder jugar
	glcd_inicializar();
	inicializar_perifericos(FRECUENCIA_PERIFERICOS);
	timer_inicializar(TIMER0);
	
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
						if(c < TAM_X && f < TAM_Y){
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

void comenzar_juego(){
	//recreamos una pantalla de inicio
	timer_iniciar_ciclos_ms(TIMER0, 450);		//timer para simular un parpadeo de texto
	
	do{
		glcd_borrar(NEGRO);
		timer_esperar_fin_ciclo(TIMER0);
		
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
		
		glcd_rectangulo_relleno(315, 40, 475, 110, BLACK);
		timer_esperar_fin_ciclo(TIMER0);
		glcd_xprintf(315, 50, WHITE, NEGRO, FUENTE8X16," MUEVA EL JOYSTICK ");
		glcd_xprintf(315, 70, WHITE, NEGRO, FUENTE8X16," HACIA ARRIBA PARA ");
		glcd_xprintf(315, 90, WHITE, NEGRO, FUENTE8X16,"      COMENZAR     ");
		timer_esperar_fin_ciclo(TIMER0);

	}while(joystick_leer() != JOYSTICK_ARRIBA);
		
	
}
