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
	uint8_t num_mx = (uint8_t)matriz;
	uint8_t fila = (uint8_t)row;
	uint8_t columna = (uint8_t)column;
	//MatrizLedSelect(num_mx, fila, columna);
    // Avanzamos una posición por cada toque

    // Apagar todo primero
    MAX7219_ClearAll();

    // Prender el nuevo LED
    MatrizLedSelect(num_mx, fila, columna);
    //MAX7219_LightSingleLed(current_matrix, current_row, current_bit);
}


