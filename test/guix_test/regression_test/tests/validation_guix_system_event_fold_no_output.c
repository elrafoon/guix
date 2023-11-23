/* This is a small demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "tx_api.h"
#include "gx_api.h"
#include "gx_system.h"
#include "gx_validation_utility.h"

TEST_PARAM test_parameter = {
    "guix_system_event_fold_no_output", /* Test name */
    0, 0, 0, 0  /* Define the coordinates of the capture area.*/
};

static VOID      control_thread_entry(ULONG);
int main(int argc, char ** argv)
{
    /* Start ThreadX system */
    tx_kernel_enter(); 
    return(0);
}

VOID tx_application_define(void *first_unused_memory)
{
    /* Call the actual line example routine. */
    gx_validation_application_define(first_unused_memory);
    /* Termiante the test if it runs for more than 100 ticks */
    /* This function is not implemented yet. */
    gx_validation_watchdog_create(100);

    /* Create a dedicated thread to perform various operations
       on the line drawing example. These operations simulate 
       user input. */
    gx_validation_control_thread_create(control_thread_entry);

}

#ifdef WIN32
#undef WIN32
#endif

#include "gx_validation_wrapper.h"
#include "demo_guix_all_widgets.c"

#define TIMER_EVENT_QUEUED 2
char test_comment[255];
int  timer_ticks = 0;

static UINT test_event_process(GX_WINDOW *window, GX_EVENT* event_ptr)
{
    switch(event_ptr->gx_event_type)
    {
    case GX_EVENT_TIMER:
        timer_ticks = event_ptr->gx_event_payload.gx_event_ulongdata;
        break;
     
    }
    return gx_window_event_process(window, event_ptr);
}

/* This thread simulates user input.  Its priority is lower
   than the GUIX thread, so that GUIX finishes an operation 
   before this thread is able to issue the next command. */
static VOID control_thread_entry(ULONG input)
{
GX_EVENT my_event; 
int      index = 0;

    memset(&my_event, 0, sizeof(GX_EVENT));
    my_event.gx_event_display_handle = 1;
    
    gx_widget_event_process_set((GX_WIDGET *)&button_screen, (UINT (*)(GX_WIDGET *, GX_EVENT *))test_event_process);
    my_event.gx_event_type = GX_EVENT_TIMER;
    my_event.gx_event_target = (GX_WIDGET *)&button_screen;
    my_event.gx_event_payload.gx_event_ulongdata = 1;
 
    tx_thread_suspend(&_gx_system_thread);
    for(index = 0; index < TIMER_EVENT_QUEUED + 1; index++)
    {
        gx_system_event_fold(&my_event);
    }
    tx_thread_resume(&_gx_system_thread);

    if(timer_ticks == TIMER_EVENT_QUEUED) 
    {
        gx_validation_print_test_result(TEST_SUCCESS);
        exit(0);
    }
    else 
    {
        gx_validation_print_test_result(TEST_FAIL);
        exit(1);
    }
}