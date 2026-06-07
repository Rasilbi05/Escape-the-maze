/**
 * @file    adc_perifericos.c
 * @brief   Funciones necesarias para leer los valores analagicos de la LDR y del joystick.
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

void inicializar_perifericos(uint32_t frecuencia_adc) {
  adc_inicializar(frecuencia_adc, CANAL_LDR);
  adc_inicializar(frecuencia_adc, CANAL_JOYSTICK_X);
  adc_inicializar(frecuencia_adc, CANAL_JOYSTICK_Y);

  //Iniciliazicacion necesaria para el boton del joystgick

  LPC_IOCON->P2_21 =
      (1u << 4);  //Activamos resistencia de pull-up para filtrar la pulsacion del boton.
  gpio_ajustar_dir(PUERTO2, PIN21, DIR_ENTRADA);
}

uint8_t encender_linterna(void) {
  if (adc_convertir(CANAL_LDR) > UMBRAL_LUZ) {
    return OSCURO;
  } else {
    return ILUMINADO;
  }
}

uint8_t joystick_leer(void) {
  if (adc_convertir(CANAL_JOYSTICK_X) > UMBRAL_ABAJO_DERECHA) {
    return JOYSTICK_DERECHA;
  }
  if (adc_convertir(CANAL_JOYSTICK_X) < UMBRAL_ARRIBA_IZQUIERDA) {
    return JOYSTICK_IZQUIERDA;
  }
  if (adc_convertir(CANAL_JOYSTICK_Y) > UMBRAL_ABAJO_DERECHA) {
    return JOYSTICK_ABAJO;
  }
  if (adc_convertir(CANAL_JOYSTICK_Y) < UMBRAL_ARRIBA_IZQUIERDA) {
    return JOYSTICK_ARRIBA;
  }
  if (gpio_leer_pin(PUERTO2, PIN21) == PULSADO) {
    return JOYSTICK_CENTRO;
  }
  return JOYSTICK_NADA;
}
