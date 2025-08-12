#ifndef WAITINGSCREENVIEW_HPP
#define WAITINGSCREENVIEW_HPP

#include <gui_generated/waitingscreen_screen/WaitingScreenViewBase.hpp>
#include <gui/waitingscreen_screen/WaitingScreenPresenter.hpp>

class WaitingScreenView : public WaitingScreenViewBase
{
public:
    WaitingScreenView();
    virtual ~WaitingScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    //funciones mias:
    virtual void handleTickEvent();
    void ProgressBar(uint8_t progress);
protected:
    bool increase = true;
};

#endif // WAITINGSCREENVIEW_HPP
