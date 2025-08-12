#include <gui/waitingscreen_screen/WaitingScreenView.hpp>
#include <gui/waitingscreen_screen/WaitingScreenPresenter.hpp>

WaitingScreenPresenter::WaitingScreenPresenter(WaitingScreenView& v)
    : view(v)
{
	ledTaskHandle = NULL; // inicializo el hanlde que se encarga de la tarea
	progressQueue = xQueueCreate(5, sizeof(uint8_t));
}

void WaitingScreenPresenter::activate()
{

}

void WaitingScreenPresenter::deactivate()
{
	// si ya hay una tarea la elimino
	if(ledTaskHandle != NULL)
	    {
	        vTaskDelete(ledTaskHandle);
	        ledTaskHandle = NULL;
	    }
}
void WaitingScreenPresenter::Start_Pattern()
{
    // Creo la tarea que se encarga de los leds
    xTaskCreate(
        ledDisplayTask,        // Función de la tarea
        "LEDTask",            // Nombre de la tarea
        512,                  // Tamaño del stack (ajustar según necesites)
        this,                 // Parámetro (pasar 'this' para acceder al presenter)
        2,                    // Prioridad (2 = alta prioridad)
        &ledTaskHandle        // Handle de la tarea
    );
}
void WaitingScreenPresenter::ledDisplayTask(void* pvParameters)
{
    // Convertir el parámetro de vuelta al presenter
    WaitingScreenPresenter* presenter = static_cast<WaitingScreenPresenter*>(pvParameters);

    // Aquí va tu función original, pero modificada
    for(uint8_t i = 0; i < in_data_count; i++)
    {
    	MAX7219_ShowSelecctions(i);
        vTaskDelay(pdMS_TO_TICKS(TIME_DELAY_SHOW_LED));

        uint8_t progress = ((i + 1) * 100) / in_data_count;

        xQueueSend(presenter->progressQueue, &progress, 0);
    }

    MAX7219_ClearAll();

    uint8_t finalProgress = 100;
	xQueueSend(presenter->progressQueue, &finalProgress, 0);
    // Elimino la tarea ya termine
    presenter->ledTaskHandle = NULL;
    vTaskDelete(NULL);
}
void WaitingScreenPresenter::checkProgressUpdate()
{
    uint8_t progress;

    // Verificar si hay datos en la cola (no bloquear)
    if(xQueueReceive(progressQueue, &progress, 0) == pdTRUE)
    {
        view.ProgressBar(progress);
    }
}
