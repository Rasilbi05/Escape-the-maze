# Escape-the-maze 🎮

Este proyecto ha sido desarrollado para la asignatura **Diseño Basado en Microprocesadores** de la **Universidad de Cádiz (UCA)**. El objetivo es diseñar un programa sobre un microprocesador **LPC4088 (ARM Cortex-M4)**, integrando periféricos externos.

## Integrantes 👥
* Raúl Silva Bienvenido
* Jose Carlos Leal Iglesias

## Mecánicas del Juego 🕹️
Te encuentras en un laberinto a oscuras, pero cuentas con una linterna especial:
* **Sensor LDR**: Controla la visibilidad. Cuanta más luz detecte el sensor (emulando la intensidad de tu linterna), mayor será el área del mapa revelada en la pantalla.
* **Joystick XY**: Permite un movimiento fluido y preciso del personaje para sortear obstáculos y encontrar la salida.
  
## Detalles Técnicos y Hardware 🚀

### 🖲️ Componentes y Pinout
El proyecto hace uso de periféricos analógicos y digitales mapeados de la siguiente forma (Pendiente de confirmar pines finales):

| Periférico | Pin LPC4088 | Canal / Función | Descripción |
| :--- | :--- | :--- | :--- |
| **Joystick Eje X** | *Por determinar* | ADC Canal X | Control movimiento horizontal |
| **Joystick Eje Y** | *Por determinar* | ADC Canal Y | Control movimiento vertical |
| **Foto-resistencia (LDR)** | *Por determinar* | ADC Canal Z | Control dinámico de iluminación |
| **Embedded Artists LCD** | Bus 24-bit | TFT / RGB | Pantalla principal de juego |
| **J-Link EDU** | Interface SWD | Debug / Flash | Depuración y carga de firmware |

## Configuración del Entorno 🛠️

1. **IDE**: Utilizar [Keil µVision5](https://www.keil.com/download/product/).
2. **Drivers J-Link**: Versión 9.32 o superior para la comunicación con el adaptador Segger.
3. **Packs de Dispositivos**: Instalar `Keil::LPC4000_DFP` desde el *Pack Installer* de Keil.

## Compilación y Carga 🧩

1. Abrir el archivo de proyecto en `project/proyecto.uvprojx`.
2. Pulsar `Ctrl + F7` (**Translate**) y `F7` para compilar y generar el ejecutable.
4. Conectar la placa mediante J-Link y pulsar `F8` (**Download**) para cargar el programa en la memoria Flash del microcontrolador.

## Estructura del Repositorio 📂
* `/src`: Código fuente (`.c`), cabeceras (`.h`) y librerías del sistema (`.lib`).
* `/project`: Archivos de configuración y entorno de Keil µVision.
* `/.gitignore`: Configuración para evitar la subida de archivos temporales y de salida local (`Objects/`, `Listings/`, etc.).

