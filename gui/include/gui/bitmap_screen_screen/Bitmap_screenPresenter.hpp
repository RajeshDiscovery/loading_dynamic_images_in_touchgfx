#ifndef BITMAP_SCREEN_PRESENTER_HPP
#define BITMAP_SCREEN_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Bitmap_screenView;

class Bitmap_screenPresenter : public Presenter, public ModelListener
{
public:
    Bitmap_screenPresenter(Bitmap_screenView& v);

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

    virtual ~Bitmap_screenPresenter() {};

private:
    Bitmap_screenPresenter();

    Bitmap_screenView& view;
};


#endif // BITMAP_SCREEN_PRESENTER_HPP
