#ifndef GRAFICVIEW_HPP
#define GRAFICVIEW_HPP

#include <gui_generated/grafic_screen/GraficViewBase.hpp>
#include <gui/grafic_screen/GraficPresenter.hpp>

#include "math.h"

class GraficView : public GraficViewBase
{
public:
    GraficView();
    virtual ~GraficView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // GRAFICVIEW_HPP
