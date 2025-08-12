/*
 * led_matrix_control.h
 *
 *  Created on: Jul 21, 2025
 *      Author: Franco Dinter
 */

#ifndef APPLICATION_USER_CORE_LED_MATRIX_CONTROL_H_
#define APPLICATION_USER_CORE_LED_MATRIX_CONTROL_H_

#include "main.h"
#include "stm32h747i_discovery_qspi.h"

#define  	NUM_FILAS 					8
#define  	NUM_MATRICES				4
#define  	MAX_BRIGTHNESS				15
#define  	INTENSITY_ADD				0x0A
#define		MAX_SELECTIONS 				100
#define		TIME_DELAY_SHOW_LED			1500    // tiempo en milisegundos

// Structurs

typedef struct {
    uint8_t n_matrix;   // Número de matriz (0..N)
    uint8_t n_row;     // Número de fila (0..N)
    uint8_t n_column;      // Número de bit/columna (0..N)
} SeleccionLED;


// Led Matrix functions
HAL_StatusTypeDef MAX7219_SendToAll(uint8_t address, uint8_t data, uint8_t pos);
void MAX7219_Test_Brightness(void);
void MAX7219_Init(int brillo);
void MatrizLedSelect(uint8_t num_mx, uint8_t row, uint8_t column);
void MAX7219_ResetAll(void);
void MAX7219_ClearAll(void);
void MAX7219_CS_Enable(void);
void MAX7219_CS_Disable(void);
void MAX7219_LightSingleLed(uint8_t matrix_index, uint8_t row, uint8_t bit_position);
void MAX7219_SaveSelection(uint8_t num_mx, uint8_t row, uint8_t column);
void MAX7219_ShowSelecctions(uint8_t index);

// Varibles externas

extern uint8_t current_matrix;
extern uint8_t current_row;   // de 1 a 8
extern uint8_t current_bit;
extern uint8_t in_data_count;
#endif /* APPLICATION_USER_CORE_LED_MATRIX_CONTROL_H_ */
