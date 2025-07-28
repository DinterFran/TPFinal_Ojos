/*
 * led_matrix_control.c
 *
 *  Created on: Jul 21, 2025
 *      Author: Franco Dinter
 */
#include "led_matrix_control.h"

// TODO: buscar no hacerlas globalas, pasarlas como parametros.
// Variables //
uint8_t current_matrix = 0;
uint8_t current_row = 1;   // de 1 a 8
uint8_t current_bit = 0;
void MAX7219_ClearAll(void);
void MAX7219_ResetAll(void);
void MAX7219_LightSingleLed(uint8_t matrix_index, uint8_t row, uint8_t bit_position);

void MAX7219_CS_Enable(void) {
    HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_RESET);
}

void MAX7219_CS_Disable(void) {
    HAL_GPIO_WritePin(MAX7219_CS_GPIO_Port, MAX7219_CS_Pin, GPIO_PIN_SET);
}

void MAX7219_BlinkTest(void) {
    for (uint8_t m = 0; m < NUM_MATRICES; m++) {
        for (uint8_t fila = 1; fila <= 8; fila++) {
            for (uint8_t bit = 0; bit < 8; bit++) {
                uint8_t valor = 1 << bit;
                MAX7219_SendToAll(fila, valor, m);
                HAL_Delay(100);
                MAX7219_SendToAll(fila, 0x00, m);
            }
        }
    }
}

//Forma de matriz:
//{ 1  , 2 	, 3  , 4  }
//{ 5  , 6  , 7  , 8  }
//{ 9  , 10 , 11 , 12 }
//{ 13 , 14 , 15 , 16 }
uint8_t matrix_pattern[NUM_MATRICES][NUM_FILAS] = {0};
// Funciona
void MatrizLedSelect(uint8_t num_mx, uint8_t row, uint8_t column){
	// arreglo para darle valores a las matrices


	if(num_mx >= NUM_MATRICES || row >= NUM_FILAS || column >= 8){
		// evitar valores erroneos
		return;
	}
	//primero completo los datos de las filas
	uint8_t current_row = row * 2 - 1;

	for (uint8_t matriz = 0 ; matriz < NUM_MATRICES; matriz++){
		for(uint8_t fila = 0; fila < NUM_FILAS ; fila++){

			if(matriz != num_mx){
				matrix_pattern[matriz][fila] = 0x00;
			} else {
				if( (fila == current_row) || (fila == (current_row-1))){
					switch (column) {
					    case 0:
					    	matrix_pattern[matriz][fila] = 0b00000011;
					        break; // Optional: exits the switch statement
					    case 1:
					    	matrix_pattern[matriz][fila] = 0b00001100;
					        break;
					    case 2:
					    	matrix_pattern[matriz][fila] = 0b00110000;
					        break;
					    case 3:
					    	matrix_pattern[matriz][fila] = 0b11000000;
					        // Code to execute if expression matches constant_value_2
					        break;

					    default:
					    	matrix_pattern[matriz][fila] = 0x00;
					}
				} else {
					matrix_pattern[matriz][fila] = 0x00;
				}
			}
		}
	}
	// ya actualiza toda la matriz
	uint8_t spi_packet[NUM_MATRICES * 2];
	uint8_t posicion_spi = 0;
	for(uint8_t fila = 1; fila <= NUM_FILAS ; fila++){

        for(uint8_t matriz = 0; matriz < NUM_MATRICES; matriz++){
            // El orden de envío es de la última matriz a la primera
        	posicion_spi = (NUM_MATRICES - 1 - matriz) * 2;
        	spi_packet[posicion_spi] = fila;
        	spi_packet[posicion_spi + 1] = matrix_pattern[matriz][fila-1];
        }

		MAX7219_CS_Enable();
		HAL_SPI_Transmit(&hspi5, spi_packet, sizeof(spi_packet), 100);
		MAX7219_CS_Disable();
	}

}




void MAX7219_ClearAll(void) {
    for (uint8_t fila = 1; fila <= 8; fila++) {
        uint8_t tx[NUM_MATRICES * 2];

        // IMPORTANTE: llenar el buffer en orden inverso,
        // porque el primer par enviado es para la matriz más lejana,
        // y el último par es para la matriz más cercana al micro.
        for (int i = 0; i < NUM_MATRICES; i++) {
            //int index = (NUM_MATRICES - 1) - i;  // índice invertido

            tx[i * 2]     = fila;   // Dirección fila (1 a 8)
            tx[i * 2 + 1] = 0x00;   // Apagar todos los LEDs en esa fila
        }

        MAX7219_CS_Enable();
        HAL_SPI_Transmit(&hspi5, tx, sizeof(tx), 500);
        MAX7219_CS_Disable();
    }
}


HAL_StatusTypeDef MAX7219_SendToAll(uint8_t address, uint8_t data, uint8_t pos) {
    uint8_t tx[NUM_MATRICES * 2];

    for (int i = 0; i < NUM_MATRICES; i++) {
        if (i == pos) {
            tx[i * 2]     = address;
            tx[i * 2 + 1] = data;
        } else {
            tx[i * 2]     = 0x00;  // No-op (no hace nada)
            tx[i * 2 + 1] = 0x00;
        }
    }

    MAX7219_CS_Enable();
    HAL_Delay(1);
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(&hspi5, tx, NUM_MATRICES * 2, 100);
    HAL_Delay(1);
    MAX7219_CS_Disable();

    return ret;
}
void MAX7219_ResetAll(void) {
    for (uint8_t i = 0; i < NUM_MATRICES; i++) {
        MAX7219_SendToAll(0x0F, 0x00, i);  // Display test off
        MAX7219_SendToAll(0x09, 0x00, i);  // Decode mode off
        MAX7219_SendToAll(0x0B, 0x07, i);  // Scan limit = 8
        MAX7219_SendToAll(0x0C, 0x01, i);  // Normal operation
        MAX7219_SendToAll(0x0A, 0x08, i);  // Medium intensity
    }
}
void MAX7219_LightSingleLed(uint8_t matrix_index, uint8_t row, uint8_t bit_position) {
    uint8_t data = 1 << bit_position;  // prende un solo bit

    uint8_t tx[NUM_MATRICES * 2];

    for (int i = 0; i < NUM_MATRICES; i++) {
        int idx = NUM_MATRICES - 1 - i;

        if (idx == matrix_index) {
            tx[i * 2] = row;         // dirección fila (1 a 8)
            tx[i * 2 + 1] = data;    // un solo LED prendido
        } else {
            tx[i * 2] = 0x00;        // NO-OP
            tx[i * 2 + 1] = 0x00;
        }
    }

    MAX7219_CS_Enable();
    HAL_SPI_Transmit(&hspi5, tx, sizeof(tx), 100);
    MAX7219_CS_Disable();
}




