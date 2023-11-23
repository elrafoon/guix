/* This is a small demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "tx_api.h"
#include "gx_api.h"
#include "gx_validation_utility.h"

TEST_PARAM test_parameter = {
    "guix_all_widgets_root_window_operation", /* Test name */
    73, 7, 300, 200  /* Define the coordinates of the capture area.
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


/* Replace the default graphics driver with the validation driver. */
#ifdef win32_graphics_driver_setup_24xrgb  
#undef win32_graphics_driver_setup_24xrgb  
#endif
#define win32_graphics_driver_setup_24xrgb  gx_validation_graphics_driver_setup_24xrgb


#ifdef WIN32
#undef WIN32
#endif

#include "gx_validation_wrapper.h"

#include "demo_guix_all_widgets.c"

char test_comment[255];

GX_WINDOW_ROOT     nested_root_1;
GX_WINDOW_ROOT     nested_root_2;

static VOID control_thread_entry(ULONG input)
{
int       frame_id = 1;

    gx_window_root_create(&nested_root_1, "nested_root_1", &animation_canvas, GX_STYLE_BORDER_NONE, GX_NULL, &NestedWindow.gx_widget_size);
    gx_window_root_create(&nested_root_2, "nested_root_2", &animation_canvas, GX_STYLE_BORDER_NONE, GX_NULL, &NestedWindow.gx_widget_size);
    ToggleScreen(pWindowScreen, pButtonScreen);
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Original window screen, with two nested_root_window created.");
    gx_validation_screen_refresh(); 

    gx_window_close(&NestedWindow);
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Close nested root window.");
    gx_validation_screen_refresh(); 

    gx_window_root_delete(&nested_root);
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Delete nested_root.");
    gx_validation_screen_refresh();  
    
    gx_window_root_delete(&nested_root_1);
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Delete nested_root_1.");
    gx_validation_screen_refresh();   

    gx_window_root_delete(&nested_root_2);
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Delete nested_root_2.");
    gx_validation_screen_refresh();   

    /* Signal the end of the test case.  Verify the output. */
    gx_validation_end();

    exit(0);
}