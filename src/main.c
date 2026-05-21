/**
 * @file    main.c
 * @brief   Programa principal de ejecución de Escape the Maze
 *
 * @author 	Raúl Silva Bienvenido
 * @author 	Jose Carlos Leal Iglesias
 * @date 		2026-04-30
 * @version 0.1
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "adc_lpc40xx.h"
#include "adc_ntc.h"
#include "adc_perifericos.h"


int main(void){
	inicializar_perifericos(1e6);
	glcd_inicializar();
	glcd_borrar(NEGRO);
	timer_inicializar(TIMER0);
	
	timer_iniciar_ciclos_ms(TIMER0,1000);
	
	//inicializaciones
	uint16_t valor_ldr;
	while(1){
		valor_ldr = ldr_leer_valor(CANAL_LDR);
		
		glcd_xprintf(0,0,YELLOW,DARKBLUE,FUENTE16X32,"El valor traducido de la LDR es: %d",valor_ldr);
		
		timer_esperar_fin_ciclo(TIMER0);
		//lógica del juego
	}

}