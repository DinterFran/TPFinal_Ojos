#include <gui/grafic_screen/GraficView.hpp>

GraficView::GraficView()
{

}

void GraficView::setupScreen()
{
    GraficViewBase::setupScreen();
    graph1.clear(); // limpio la pantalla
    const float amplitud = 50.0f;
	const float offset   = 50.0f;
	const float frecuencia = 2.0f; // ciclos en el rango X
	const int numPuntos = 100;
	for (int x = 0; x <= numPuntos; x++)
	    {
	        float angulo = 2.0f * M_PI * frecuencia * (x / (float)numPuntos);
	        float valorY = offset + amplitud * sin(angulo);
	        graph1.addDataPoint((int16_t)x, (int16_t)valorY);
	    }
}

void GraficView::tearDownScreen()
{
    GraficViewBase::tearDownScreen();
}
