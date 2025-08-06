#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();

}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}
void Screen1View::sendBrilloValue(int valor)
{
	int test = valor;
	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", test);
	textArea2.setWildcard(textArea2Buffer);
    textArea2.invalidate();
}
