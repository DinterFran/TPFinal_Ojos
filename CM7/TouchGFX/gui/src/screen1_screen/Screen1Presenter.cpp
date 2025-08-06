#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}
int brillo_actual = 7;
void Screen1Presenter::updateBrilloValue(int value){
	if( value == 1){
		if(brillo_actual < 15){
			brillo_actual++;
		}
	} else {
		if(brillo_actual > 0){
			brillo_actual--;
		}
	}

	view.sendBrilloValue(brillo_actual);

}
