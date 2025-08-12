#ifndef WAITINGSCREENPRESENTER_HPP
#define WAITINGSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
using namespace touchgfx;

class WaitingScreenView;

class WaitingScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    WaitingScreenPresenter(WaitingScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~WaitingScreenPresenter() {}
    void updateProgress(uint8_t progress);
    static void ledDisplayTask(void* pvParameters);
    void Start_Pattern();
    void checkProgressUpdate();
private:
    WaitingScreenPresenter();

    WaitingScreenView& view;
    TaskHandle_t ledTaskHandle; // Handle de la muestra de leds
    QueueHandle_t progressQueue; // cola donde se guarda el progreso de la barra
};

#endif // WAITINGSCREENPRESENTER_HPP
