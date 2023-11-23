/* This is a small demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "tx_api.h"
#include "gx_api.h"
#include "gx_validation_utility.h"
#include "gx_system.h"
#include "gx_display.h"

TEST_PARAM test_parameter = {
    "guix_display_driver_aliased_filled_circle_draw", /* Test name */
    20, 65, 350, 400  /* Define the coordinates of the capture area.
                         In this test, we only need to capture the line
                         drawing area.  */
};

static VOID      control_thread_entry(ULONG);
int main(int argc, char ** argv)
{
    /* Parse the command line argument. */
    gx_validation_setup(argc, argv);

    /* Start ThreadX system */
    tx_kernel_enter(); 
    return(0);
}

VOID tx_application_define(void *first_unused_memory)
{

    /* Create a dedicated thread to perform various operations
       on the line drawing example. These operations simulate 
       user input. */
    gx_validation_control_thread_create(control_thread_entry);

    /* Termiante the test if it runs for more than 100 ticks */
    /* This function is not implemented yet. */
    gx_validation_watchdog_create(100);

    /* Call the actual line example routine. */
    gx_validation_application_define(first_unused_memory);

}

#ifdef win32_graphics_driver_setup_565rgb  
#undef win32_graphics_driver_setup_565rgb  
#endif
/* Replace the default graphics driver with the validation driver. */
#define win32_graphics_driver_setup_565rgb  gx_validation_graphics_driver_setup_565rgb


#ifdef WIN32
#undef WIN32
#endif

#include "gx_validation_wrapper.h"

#include "demo_guix_all_widgets_16bpp.c"

extern GX_WINDOW     *pLineWin;

static VOID test_filled_circle_draw(GX_WINDOW *window)
{
GX_DRAW_CONTEXT *context;
GX_RECTANGLE    *size;
GX_FIXED_VAL     xcenter;
GX_FIXED_VAL     ycenter;
GX_FIXED_VAL     r;
VOID           (*old_blend_func)(GX_DRAW_CONTEXT *context,
                                 INT x, INT y, GX_COLOR color, GX_UBYTE alpha);

    gx_window_draw((GX_WINDOW*) window);

    /* set line color. */
    gx_context_line_color_set(GX_COLOR_ID_CANVAS);

    context = _gx_system_current_draw_context;
    context->gx_draw_context_clip = &window->gx_widget_size;

    old_blend_func = context->gx_draw_context_display->gx_display_driver_pixel_blend;

    context->gx_draw_context_display->gx_display_driver_pixel_blend = GX_NULL;
    _gx_display_driver_generic_aliased_filled_circle_draw(context, 0, 0, 100);
 
    /* restore old blend funciton. */
    context->gx_draw_context_display->gx_display_driver_pixel_blend = old_blend_func;

    size = &window->gx_widget_size;
    xcenter = GX_FIXED_VAL_MAKE((size->gx_rectangle_left + size->gx_rectangle_right) >> 1);
    ycenter = GX_FIXED_VAL_MAKE((size->gx_rectangle_top + size->gx_rectangle_bottom) >> 1);
    r = GX_FIXED_VAL_MAKE(100);

    _gx_display_driver_generic_aliased_filled_circle_draw(context, xcenter, ycenter, r);
}

/* This thread simulates user input.  Its priority is lower
   than the GUIX thread, so that GUIX finishes an operation 
   before this thread is able to issue the next command. */
static VOID control_thread_entry(ULONG input)
{
    gx_widget_draw_set((GX_WIDGET *)pLineWin, (void(*)(GX_WIDGET *))test_filled_circle_draw);
    ToggleScreen((GX_WINDOW *)&lines_screen, (GX_WINDOW *)&button_screen);

    gx_validation_set_frame_id(1);
    gx_validation_set_frame_comment("Test aliased filled circle draw");
    gx_validation_screen_refresh();

    /* Signal the end of the test case.  Verify the output. */
    gx_validation_end();

    exit(0);
}




