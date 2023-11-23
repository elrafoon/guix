/* This is a small demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "tx_api.h"
#include "gx_api.h"
#include "gx_validation_utility.h"
#include "gx_system.h"

TEST_PARAM test_parameter = {
    "guix_utility_1bpp_pixelmap_resize", /* Test name */
    40, 90, 600, 430  /* Define the coordinates of the capture area.
                         In this test, we only need to capture the pixelmap
                         drawing area.  */
};

extern void mark_dirty();
extern void convert_start();

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
       on the pixelmap drawing example. These operations simulate 
       user input. */
    gx_validation_control_thread_create(control_thread_entry);

    /* Termiante the test if it runs for more than 100 ticks */
    /* This function is not implemented yet. */
    gx_validation_watchdog_create(100);

    /* Call the actual line example routine. */
    gx_validation_application_define(first_unused_memory);

}


/* Replace the default graphics driver with the validation driver. */
#ifdef win32_graphics_driver_setup_monochrome
#undef win32_graphics_driver_setup_monochrome
#endif
#define win32_graphics_driver_setup_monochrome  gx_validation_graphics_driver_setup_monochrome


#ifdef WIN32
#undef WIN32
#endif

#include "gx_validation_wrapper.h"

#include "demo_guix_all_widgets_1bpp.c"

GX_RESOURCE_ID resize_pixelmap_id_list[]={
    GX_PIXELMAP_ID_ICON_FOOT_ALPHA,
    GX_PIXELMAP_ID_ROTATE_FISH
};

char test_comment[256];

extern float x_ratio;
extern float y_ratio;
extern GX_RESOURCE_ID resize_pixelmap_id;
VOID *test_allocate(ULONG size)
{
   return GX_NULL;
}

VOID test_free(VOID *mem)
{
    return;
}
/* This thread simulates user input.  Its priority is lower
   than the GUIX thread, so that GUIX finishes an operation 
   before this thread is able to issue the next command. */
static VOID control_thread_entry(ULONG input)
{
int      frame_id = 1;
int      pixelmap_index;

    /* Toggle to Image Convert Screen. */
    ToggleScreen((GX_WINDOW *)&resize_screen, (GX_WINDOW *)&rotate_screen);
    x_ratio = 1.5;
    y_ratio = 1.5;
    for(pixelmap_index = 0; pixelmap_index < 2; pixelmap_index++)
    {
        resize_pixelmap_id = resize_pixelmap_id_list[pixelmap_index];
        gx_system_dirty_mark((GX_WIDGET *)&resize_screen.resize_screen_resize_window);

        /* Capture a frame. */
        gx_validation_set_frame_id(frame_id++);
        sprintf(test_comment, "pixelmap_id = %d",(int)resize_pixelmap_id);
        gx_validation_set_frame_comment(test_comment);
        gx_validation_screen_refresh();
    }
    
    gx_system_memory_allocator_set(test_allocate, test_free);
    for(pixelmap_index = 0; pixelmap_index < 2; pixelmap_index++)
    {
        resize_pixelmap_id = resize_pixelmap_id_list[pixelmap_index];
        gx_system_dirty_mark((GX_WIDGET *)&resize_screen.resize_screen_resize_window);

        /* Capture a frame. */
        gx_validation_set_frame_id(frame_id++);
        sprintf(test_comment, "Set system allocate function to return null then call rotate. pixelmap_id = %d",(int)resize_pixelmap_id);
        gx_validation_set_frame_comment(test_comment);
        gx_validation_screen_refresh();
    }

    /* Signal the end of the test case.  Verify the output. */
    gx_validation_end();

    exit(0);
}