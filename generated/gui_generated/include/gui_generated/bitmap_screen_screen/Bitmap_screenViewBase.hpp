/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef BITMAP_SCREEN_VIEW_BASE_HPP
#define BITMAP_SCREEN_VIEW_BASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/bitmap_screen_screen/Bitmap_screenPresenter.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>

class Bitmap_screenViewBase : public touchgfx::View<Bitmap_screenPresenter>
{
public:
    Bitmap_screenViewBase();
    virtual ~Bitmap_screenViewBase() {}

    virtual void setupScreen();

	void bmpImageFromFile();
	void JpgImageFromFile();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Button button1;
    touchgfx::Image image;
    touchgfx::Image image_right;

private:

};

#endif // BITMAP_SCREEN_VIEW_BASE_HPP
