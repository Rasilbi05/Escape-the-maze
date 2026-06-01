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


// ===== Variables Privadas (Volátiles porque cambian en la ISR) =====
/**
 * @brief Variable para almacenar el dato de la LDR por interrupción.
 * @ingroup Perifericos
 */
static volatile uint8_t valor_linterna_int = OSCURO;
static volatile uint16_t valor_joy_x = 2048;
static volatile uint16_t valor_joy_y = 2048;

void inicializar_perifericos(uint32_t frecuencia_adc){
	adc_inicializar(frecuencia_adc,CANAL_LDR);
	adc_inicializar(frecuencia_adc,CANAL_JOYSTICK_X);
	adc_inicializar(frecuencia_adc,CANAL_JOYSTICK_Y);
	
	//Configuración para habilitar las interrupciones de los periféricos
	adc_modo_burst(FALSE);
	adc_configurar_interrupciones(CANAL_LDR | CANAL_JOYSTICK_X | CANAL_JOYSTICK_Y,TRUE); 
	NVIC_ClearPendingIRQ(ADC_IRQn); 
	NVIC_SetPriority(ADC_IRQn, 0); 
	NVIC_EnableIRQ(ADC_IRQn); 
	__enable_irq();
	
	//Iniciliazicación necesaria para el botón del joystgick
	
	LPC_IOCON->P2_21 = (1u << 4);		//Activamos resistencia de pull-up para filtrar la pulsación del botón.
	gpio_ajustar_dir(PUERTO2,PIN21,DIR_ENTRADA);
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
	if (gpio_leer_pin(PUERTO2,PIN21) == PULSADO){
		return JOYSTICK_CENTRO;
	}
	return JOYSTICK_NADA;
}

uint8_t joystick_leer_int(void){
	if (valor_joy_x > UMBRAL_ABAJO_DERECHA){
			return JOYSTICK_DERECHA;
	}
	if (valor_joy_x < UMBRAL_ARRIBA_IZQUIERDA){
			return JOYSTICK_IZQUIERDA;
	}
	if (valor_joy_y > UMBRAL_ABAJO_DERECHA){
			return JOYSTICK_ABAJO;
	}
	if (valor_joy_y < UMBRAL_ARRIBA_IZQUIERDA){
			return JOYSTICK_ARRIBA;
	}
	if (gpio_leer_pin(PUERTO2,PIN21) == PULSADO){
		return JOYSTICK_CENTRO;
	}    
    return JOYSTICK_NADA;
}

void adc_iniciar_lectura(void) {
    adc_modo_burst(TRUE);
}

/**
 * @brief Función manejadora de interrupción del adc guarda todos los valores en ráfaga.
 * @ingroup Perifericos
 */
void ADC_IRQHandler(void) {
	uint32_t estado = LPC_ADC->STAT;

	if (estado & CANAL_JOYSTICK_X) {
		valor_joy_x = (LPC_ADC->DR[INDICE_JOY_X] >> 4) & 0xFFF;
	}
	
	if (estado & CANAL_JOYSTICK_Y) {
		valor_joy_y = (LPC_ADC->DR[INDICE_JOY_Y] >> 4) & 0xFFF;
	}
	
	if (estado & CANAL_LDR) {
		uint16_t valor_adc_ldr = (LPC_ADC->DR[INDICE_LDR] >> 4) & 0xFFF;
			
		if(valor_adc_ldr > UMBRAL_LUZ) {
			valor_linterna_int = OSCURO;
		} else {
			valor_linterna_int = ILUMINADO;     
		}

		adc_modo_burst(FALSE);
	}
}
