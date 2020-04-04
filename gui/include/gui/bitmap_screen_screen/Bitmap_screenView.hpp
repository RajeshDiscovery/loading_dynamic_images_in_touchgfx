#ifndef BITMAP_SCREEN_VIEW_HPP
#define BITMAP_SCREEN_VIEW_HPP

#include <gui_generated/bitmap_screen_screen/Bitmap_screenViewBase.hpp>
#include <gui/bitmap_screen_screen/Bitmap_screenPresenter.hpp>

class Bitmap_screenView : public Bitmap_screenViewBase
{
public:
    Bitmap_screenView();
    virtual ~Bitmap_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BITMAP_SCREEN_VIEW_HPP
