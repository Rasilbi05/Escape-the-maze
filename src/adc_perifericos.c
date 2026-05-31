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

// ===== Estados de la Máquina Secuencial =====
typedef enum {
    MEDIR_X,
    MEDIR_Y,
    MEDIR_LDR,
    REPOSO
} estado_adc_t;

static volatile estado_adc_t estado_actual = REPOSO;

void inicializar_perifericos(uint32_t frecuencia_adc){
	adc_inicializar(frecuencia_adc,CANAL_LDR);
	adc_inicializar(frecuencia_adc,CANAL_JOYSTICK_X);
	adc_inicializar(frecuencia_adc,CANAL_JOYSTICK_Y);
	//Configuración para habilitar las interrupciones de los periféricos
	adc_configurar_interrupciones(CANAL_LDR | CANAL_JOYSTICK_X | CANAL_JOYSTICK_Y,TRUE); 
	NVIC_ClearPendingIRQ(ADC_IRQn); 
	NVIC_SetPriority(ADC_IRQn, 0); 
	NVIC_EnableIRQ(ADC_IRQn); 
	__enable_irq();
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

uint8_t joystick_leer_int(void){
    // Evaluamos las variables guardadas por la interrupción, ¡cero bloqueos!
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
    
    return JOYSTICK_NADA;
}

void adc_iniciar_lectura(void) {
    if (estado_actual == REPOSO) {
        estado_actual = MEDIR_LDR;
        
        LPC_ADC->CR &= ~0xFF;                           
        LPC_ADC->CR |= CANAL_LDR;         
        
        adc_modo_conversion(ADC_START_AHORA, ADC_FLANCO_SUBIDA); 
    }
}

/**
 * @brief Función manejadora de interrupción del adc guarda todos los valores en rafaga.
 * @ingroup Perifericos
 */
void ADC_IRQHandler(void) {
    switch(estado_actual) {
        
        case MEDIR_LDR:
            {
                uint16_t valor_adc_ldr = (LPC_ADC->DR[INDICE_LDR] >> 4) & 0xFFF;
                if(valor_adc_ldr > UMBRAL_LUZ){
                    valor_linterna_int = OSCURO;
                } else {
                    valor_linterna_int = ILUMINADO;		
                }
            }
            
            estado_actual = MEDIR_X;
            LPC_ADC->CR &= ~0xFF; 
            LPC_ADC->CR |= CANAL_JOYSTICK_X;
            
            adc_modo_conversion(ADC_START_AHORA, ADC_FLANCO_SUBIDA); 
            break;

        case MEDIR_X:
            valor_joy_x = (LPC_ADC->DR[INDICE_JOY_X] >> 4) & 0xFFF;
            
            estado_actual = MEDIR_Y;
            LPC_ADC->CR &= ~0xFF; 
            LPC_ADC->CR |= CANAL_JOYSTICK_Y;
            
            adc_modo_conversion(ADC_START_AHORA, ADC_FLANCO_SUBIDA); 
            break;
            
        case MEDIR_Y:
            valor_joy_y = (LPC_ADC->DR[INDICE_JOY_Y] >> 4) & 0xFFF;
            
            estado_actual = REPOSO;
            break;
            
        default:
            estado_actual = REPOSO;
            break;
    }
}
