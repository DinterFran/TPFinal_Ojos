#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

Screen2Presenter::Screen2Presenter(Screen2View& v)
    : view(v)
{

}

void Screen2Presenter::activate()
{

}

void Screen2Presenter::deactivate()
{

}


void Screen2Presenter:: selectMatrizLed(int matriz, int row, int column)
{
//	uint8_t num_mx = (uint8_t)matriz;
//	uint8_t fila = (uint8_t)row;
//	uint8_t columna = (uint8_t)column;
//	MatrizLedSelect(num_mx, fila, columna);
    // Avanzamos una posición por cada toque
    current_bit++;
    if (current_bit > 7) {
        current_bit = 0;
        current_row++;
        if (current_row > 8) {
            current_row = 1;
            current_matrix++;
            if (current_matrix >= NUM_MATRICES) {
                current_matrix = 0;
            }
        }
    }

    // Apagar todo primero
    MAX7219_ClearAll();

    // Prender el nuevo LED
    MatrizLedSelect(current_matrix, current_row, current_bit);
    //MAX7219_LightSingleLed(current_matrix, current_row, current_bit);
}


