/* This is a small demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "tx_api.h"
#include "gx_api.h"
#include "gx_validation_utility.h"
#include "gx_system.h"

TEST_PARAM test_parameter = {
    "guix_all_widgets_scroll_wheel_flick", /* Test name */
    100, 117, 525, 336  /* Define the coordinates of the capture area.
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

typedef struct TEST_STRUCT{
INT       event_type;
GX_VALUE  xpos;
GX_VALUE  ypos;
INT       wait_ticks;
GX_CHAR  *comments;
}TEST;

#define XPOS 270
#define YPOS 235

TEST test_list[]={
{GX_EVENT_PEN_DOWN, XPOS, YPOS,       5, "pen down"},/* Flick up. */
{GX_EVENT_PEN_DRAG, XPOS, YPOS - 50,  5, "pen drag"},
{GX_EVENT_PEN_UP,   XPOS, YPOS - 50,  5, "pen up"},
{GX_EVENT_PEN_DOWN, XPOS, YPOS,       5, "pen down"},/* Flick up. */
{GX_EVENT_PEN_DRAG, XPOS, YPOS - 50,  5, "pen_drag"},
{GX_EVENT_PEN_UP,   XPOS, YPOS - 50,  5, "pen up"},
{GX_EVENT_PEN_DOWN, XPOS, YPOS,       5, "pen down"},/* Flick up. */
{GX_EVENT_PEN_DRAG, XPOS, YPOS - 50,  5, "pen_drag"},
{GX_EVENT_PEN_UP,   XPOS, YPOS - 50,  5, "pen up"},
{GX_EVENT_PEN_DOWN, XPOS, YPOS,       5, "pen down"},/* Flick down. */
{GX_EVENT_PEN_DRAG, XPOS, YPOS + 80 , 5, "pen drag"},
{GX_EVENT_PEN_UP,   XPOS, YPOS + 80,  5, "pen up"},
{GX_EVENT_PEN_DOWN, XPOS, YPOS,       5, "pen down"},/* Flick down.*/
{GX_EVENT_PEN_DRAG, XPOS, YPOS + 50,  5, "pen drag"},
{GX_EVENT_PEN_UP,   XPOS, YPOS + 50,  5, "pen up"},
{GX_EVENT_PEN_DOWN, XPOS, YPOS,       5, "pen down"},/* Flick down.*/
{GX_EVENT_PEN_DRAG, XPOS, YPOS + 50,  5, "pen drag"},
{GX_EVENT_PEN_UP,   XPOS, YPOS + 50,  5, "pen up"},
{0, 0, 0, 0, 0}
};

char *test_comment[1];

TX_SEMAPHORE semaphore_memory;

static VOID control_thread_entry(ULONG input)
{
INT                      frame_id = 1;
TEST                    *test = test_list;
GX_EVENT                 my_event;

    memset(&my_event, 0, sizeof(GX_EVENT));
    my_event.gx_event_display_handle = 1;

    selected_semaphore = &semaphore_memory;

    tx_semaphore_create(selected_semaphore, "test_semaphore", 0);

    /* Create scroll wheel screen dynamically. */
    gx_studio_named_widget_create("scroll_wheel_screen", GX_NULL, (GX_WIDGET **)&pScrollWheelScreen);

    /* Toggle from button screen to scroll wheel screen. */
    ToggleScreen((GX_WINDOW *)pScrollWheelScreen, pButtonScreen);

    while(test->event_type)
    {
        test_comment[0] = test->comments;
        gx_validation_current_frame_id_get(&frame_id);
        gx_validation_capture_frames(frame_id, 30, GX_NULL, 0, 1000);
        my_event.gx_event_type = test->event_type;
        my_event.gx_event_payload.gx_event_pointdata.gx_point_x = test->xpos;
        my_event.gx_event_payload.gx_event_pointdata.gx_point_y = test->ypos;
        gx_system_event_send(&my_event);

        if(test->wait_ticks)
        {
            tx_thread_sleep(test->wait_ticks);
        }

        if(test->event_type == GX_EVENT_PEN_UP)
        {
            tx_semaphore_get(selected_semaphore, TX_WAIT_FOREVER);
        }
    
        test++;
    }

    tx_semaphore_delete(selected_semaphore);
    selected_semaphore = GX_NULL;

    /* Signal the end of the test case.  Verify the output. */
    gx_validation_end();

    exit(0);
}
