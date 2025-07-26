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
protected:
};

#endif // WAITINGSCREENVIEW_HPP
