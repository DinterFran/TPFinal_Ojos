#ifndef GRAFICPRESENTER_HPP
#define GRAFICPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

#include "main.h"

using namespace touchgfx;

class GraficView;

class GraficPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GraficPresenter(GraficView& v);

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

    virtual ~GraficPresenter() {}

private:
    GraficPresenter();

    GraficView& view;
};

#endif // GRAFICPRESENTER_HPP
