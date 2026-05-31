/**
 * @file    adc_perifericos.c
 * @brief   Funciones necesarias para leer los valores analógicos de la LDR y del joystick.
 *
 * @author  Jose Carlos Leal Iglesias
 * @author  Raul Silva Bienvenido
 * @date	2026
 * @version 1.0
 *
 * @copyright GNU General Public License version 3 or later
 *
 * 
 */

#include "adc_perifericos.h"

/**
 * @brief Variable para almacenar el dato de la LDR por interrupción.
 * @ingroup Perifericos
 */
static volatile uint8_t valor_linterna_int = OSCURO;

void inicializar_perifericos(uint32_t frecuencia_adc){
	adc_inicializar(frecuencia_adc,CANAL_LDR);
	adc_inicializar(frecuencia_adc,CANAL_JOYSTICK_X);
	adc_inicializar(frecuencia_adc,CANAL_JOYSTICK_Y);
	//Configuración para habilitar las interrupciones de la ldr
	//adc_configurar_interrupciones(CANAL_LDR,TRUE); 
	//NVIC_ClearPendingIRQ(ADC_IRQn); 
	//NVIC_SetPriority(ADC_IRQn, 0); 
	//NVIC_EnableIRQ(ADC_IRQn); 
	//__enable_irq();
	//Iniciliazicación necesaria para el botón del joystgick
	
}

uint8_t encender_linterna(void){
	if(adc_convertir(CANAL_LDR) > UMBRAL_LUZ){
		return OSCURO;
	}else{
		return ILUMINADO;
	}
}

uint8_t encender_linterna_int(void){
	return valor_linterna_int;
}

uint8_t joystick_leer(void){
	if (adc_convertir(CANAL_JOYSTICK_X) > UMBRAL_ABAJO_DERECHA){
		return JOYSTICK_DERECHA;
	}
	if (adc_convertir(CANAL_JOYSTICK_X) < UMBRAL_ARRIBA_IZQUIERDA){
		return JOYSTICK_IZQUIERDA;
	}
	if (adc_convertir(CANAL_JOYSTICK_Y) > UMBRAL_ABAJO_DERECHA){
		return JOYSTICK_ABAJO;
	}
	if (adc_convertir(CANAL_JOYSTICK_Y) < UMBRAL_ARRIBA_IZQUIERDA){
		return JOYSTICK_ARRIBA;
	}
	if (adc_convertir(CANAL_JOYSTICK_B) < UMBRAL_ARRIBA_IZQUIERDA){
		return JOYSTICK_CENTRO;
	}
	return JOYSTICK_NADA;
}

/*
void ADC_IRQHandler(void){

	uint16_t valor_adc = (LPC_ADC->DR[CANAL_LDR] >> 4) & 0xFFF;
	
	if(valor_adc > UMBRAL_LUZ){
		valor_linterna_int = OSCURO;
	}else{
		valor_linterna_int = ILUMINADO;		
	}

}
*/