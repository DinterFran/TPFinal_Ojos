#include <gui/waitingscreen_screen/WaitingScreenView.hpp>

WaitingScreenView::WaitingScreenView()
{

}

void WaitingScreenView::setupScreen()
{
    WaitingScreenViewBase::setupScreen();
}

void WaitingScreenView::tearDownScreen()
{
    WaitingScreenViewBase::tearDownScreen();
}
void WaitingScreenView::handleTickEvent(void)
{
    presenter->checkProgressUpdate();
}
void WaitingScreenView::ProgressBar(uint8_t progress)
{

		boxProgress1.setValue((int)progress);
		boxProgress1.invalidate();
}
