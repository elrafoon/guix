/* This is a small demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "tx_api.h"
#include "gx_api.h"
#include "gx_validation_utility.h"
#include "gx_system.h"
#include "gx_display.h"

TEST_PARAM test_parameter = {
    "guix_all_widgets_16bpp_rotated_pixelmap_draw", /* Test name */
    13, 16, 463, 424  /* Define the coordinates of the capture area.
                         In this test, we only need to capture the pixelmap
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
#ifdef win32_graphics_driver_setup_565rgb_rotated
#undef win32_graphics_driver_setup_565rgb_rotated
#endif
#define win32_graphics_driver_setup_565rgb_rotated  gx_validation_graphics_driver_setup_565rgb_rotated


#ifdef WIN32
#undef WIN32
#endif

#include "gx_validation_wrapper.h"

#include "demo_guix_all_widgets_16bpp_rotated.c"

char test_comment[256];

typedef struct MAP_INFO_STRUCT{
    GX_RESOURCE_ID map_id;
    char id_name[30];
}MAP_INFO;

MAP_INFO test_map_info_list[]=
{
{GX_PIXELMAP_ID__565RGB_C_A, "GX_PIXELMAP_ID__565RGB_C_A"},/* Compressed, Alpha. */
{GX_PIXELMAP_ID__565RGB_A, "GX_PIXELMAP_ID__565RGB_A"},/* Alpha. */
{GX_PIXELMAP_ID__565RGB_C, "GX_PIXELMAP_ID__565RGB_C"},/* Compress. */
{GX_PIXELMAP_ID__565RGB, "GX_PIXELMAP_ID__565RGB"}, /* Raw. */
{GX_PIXELMAP_ID__4444ARGB_C_A, "GX_PIXELMAP_ID__4444ARGB_C_A"}, /* 4444argb compressed alpha. */
{GX_PIXELMAP_ID__4444ARGB_A, "GX_PIXELMAP_ID__4444ARGB_A"}, /* 4444argb alpha. */
{GX_PIXELMAP_ID_PALETTE_C_A, "GX_PIXELMAP_ID_PALETTE_C_A"}, /* 8bit palette transparent compressed. */
{GX_PIXELMAP_ID_PALETTE_A, "GX_PIXELMAP_ID_PALETTE_A"}, /* 8bit palette transparent raw. */
{GX_PIXELMAP_ID_PALETTE_C, "GX_PIXELMAP_ID_PALETTE_C"}, /* 8bit palette compressed. */
{GX_PIXELMAP_ID_PALETTE, "GX_PIXELMAP_ID_PALETTE"}, /* 8bit palette raw. */
{GX_PIXELMAP_ID_PALETTE_SHARED, "GX_PIXELMAP_ID_PALETTE_SHARED"},
{GX_PIXELMAP_ID_ALPHAMAP_C_A, "GX_PIXELMAP_ID_ALPHAMAP_C_A"}, /* alphamap compressed. */
{GX_PIXELMAP_ID__ALPHAMAP_C_A, "GX_PIXELMAP_ID__ALPHAMAP_C_A"}, /* alphamap compressed. */
{GX_PIXELMAP_ID_ROTATE_ALPHAMAP, "GX_PIXELMAP_ID_ROTATE_ALPHAMAP"}, /* alphamap raw. */
{GX_PIXELMAP_ID__JPEG, "GX_PIXELMAP_ID__JPEG"},
{GX_PIXELMAP_ID_FISH_SMALL_411, "GX_PIXELMAP_ID_FISH_SMALL_411"},
{GX_PIXELMAP_ID_FISH_SMALL_420, "GX_PIXELMAP_ID_FISH_SMALL_420"},
{GX_PIXELMAP_ID_FISH_SMALL_422, "GX_PIXELMAP_ID_FISH_SMALL_422"},
{GX_PIXELMAP_ID_FISH_SMALL_444, "GX_PIXELMAP_ID_FISH_SMALL_444"},
{GX_PIXELMAP_ID__PNG, "GX_PIXELMAP_ID__PNG"},
{GX_PIXELMAP_ID__PNG_A, "GX_PIXELMAP_ID__PNG_A"},
{0, ""}
};

INT test_brush_alpha = 0xff;
INT test_map_id = 0;

VOID pixelmap_window_draw(GX_WINDOW *window)
{
GX_PIXELMAP *map = GX_NULL;
GX_PIXELMAP  test_map;
INT          xpos;
INT          ypos;
GX_RECTANGLE *size = &window->gx_widget_size;
GX_BRUSH     *brush;

    gx_window_draw(window);

    gx_context_pixelmap_get(test_map_id, &map);

    gx_context_brush_get(&brush);

    brush->gx_brush_style |= GX_BRUSH_SOLID_FILL;
    brush->gx_brush_alpha = test_brush_alpha;

    if(map)
    {
        gx_context_fill_color_set(GX_COLOR_ID_PURPLE);

        /* Draw map to top-left corner. */
        xpos = size->gx_rectangle_left-10;
        ypos = size->gx_rectangle_top-10;
        gx_canvas_pixelmap_draw(xpos, ypos, map);

        /* Draw map to bottom-left corner. */
        xpos = size->gx_rectangle_left-10;
        ypos = size->gx_rectangle_bottom - map->gx_pixelmap_height + 10;
        gx_canvas_pixelmap_draw(xpos, ypos, map);

        /* Draw map to top-center. */
        xpos = (size->gx_rectangle_left + size->gx_rectangle_right - map->gx_pixelmap_width) >> 1;
        ypos = size->gx_rectangle_top - (map->gx_pixelmap_height >> 1);
        gx_canvas_pixelmap_draw(xpos, ypos, map);

        /* Draw map to top-right corner. */
        xpos = size->gx_rectangle_right - map->gx_pixelmap_width + 10;
        ypos = size->gx_rectangle_top- 10;
        gx_canvas_pixelmap_draw(xpos, ypos, map);

        /* Draw map to bottom-right corner. */
        xpos = size->gx_rectangle_right - map->gx_pixelmap_width + 10;
        ypos = size->gx_rectangle_bottom - map->gx_pixelmap_height + 10;
        gx_canvas_pixelmap_draw(xpos, ypos, map);

        /* Draw map to center. */
        xpos = (size->gx_rectangle_top + size->gx_rectangle_bottom - map->gx_pixelmap_width) >> 1;
        ypos = (size->gx_rectangle_top + size->gx_rectangle_bottom - map->gx_pixelmap_height) >> 1;
        gx_canvas_pixelmap_draw(xpos, ypos, map);

        /* Draw map to bottom-center. */
        xpos = (size->gx_rectangle_left + size->gx_rectangle_right - map->gx_pixelmap_width) >> 1;
        ypos = size->gx_rectangle_bottom - (map->gx_pixelmap_height >> 1);
        gx_canvas_pixelmap_draw(xpos, ypos, map);
    }
}

VOID pixelmap_window_invalid_map_draw(GX_WINDOW *window)
{
GX_PIXELMAP invalid_map;
GX_PIXELMAP *map;
INT          xpos;
INT          ypos;
GX_BRUSH    *brush;

    gx_context_brush_get(&brush);
    brush->gx_brush_alpha = 255;

    xpos = window->gx_widget_size.gx_rectangle_left;
    ypos = window->gx_widget_size.gx_rectangle_top;

    /* Draw palette map with invalid aux data. */
    gx_context_pixelmap_get(GX_PIXELMAP_ID_PALETTE, &map);
    memcpy(&invalid_map, map, sizeof(GX_PIXELMAP));
    invalid_map.gx_pixelmap_aux_data = GX_NULL;
    gx_canvas_pixelmap_draw(xpos, ypos, &invalid_map);

    /* Draw unsupported map. */
    invalid_map.gx_pixelmap_format = GX_COLOR_FORMAT_1555XRGB;
    gx_canvas_pixelmap_draw(xpos, ypos, &invalid_map);

    /* Blend palette map width invalid aux data. */
    brush->gx_brush_alpha = 128;
    invalid_map.gx_pixelmap_format = GX_COLOR_FORMAT_8BIT_PALETTE;
    gx_canvas_pixelmap_draw(xpos, ypos, &invalid_map);

    /* Blend with unsupported format. */
    invalid_map.gx_pixelmap_format = GX_COLOR_FORMAT_1555XRGB;
    root->gx_window_root_canvas->gx_canvas_display->gx_display_driver_pixelmap_blend(GX_NULL, 0, 0, &invalid_map, 128);

    /* Blend with unsupported flag. */
    invalid_map.gx_pixelmap_format = GX_COLOR_FORMAT_8BIT_PALETTE;
    invalid_map.gx_pixelmap_flags |= GX_PIXELMAP_COMPRESSED;
    root->gx_window_root_canvas->gx_canvas_display->gx_display_driver_pixelmap_blend(GX_NULL, 0, 0, &invalid_map, 128);
}

VOID pixelmap_window_invalid_alphamap_draw(GX_WINDOW *window)
{
GX_PIXELMAP *map;
INT          xpos;
INT          ypos;
GX_BRUSH    *brush;

    gx_context_brush_get(&brush);

    xpos = window->gx_widget_size.gx_rectangle_left;
    ypos = window->gx_widget_size.gx_rectangle_top;

    /* Draw alphamap with brush alpha set to 0. */
    gx_context_pixelmap_get(GX_PIXELMAP_ID_ALPHAMAP_C_A, &map);
    brush->gx_brush_alpha = 0;
    gx_canvas_pixelmap_draw(xpos, ypos, map);

    /* Set wrong display color format. */
    root->gx_window_root_canvas->gx_canvas_display->gx_display_color_format = GX_COLOR_FORMAT_1555XRGB;

    /* Draw compressed alphamap with brush alpha.  */
    brush->gx_brush_alpha = 128;
    gx_canvas_pixelmap_draw(xpos, ypos, map);

    /* Draw compressed alphamap without brush alpha. */
    brush->gx_brush_alpha = 255;
    gx_canvas_pixelmap_draw(xpos, ypos, map);

    gx_context_pixelmap_get(GX_PIXELMAP_ID_ROTATE_ALPHAMAP, &map);

    /* Draw raw alphamap with brush alpha. */
    brush->gx_brush_alpha = 128;
    gx_canvas_pixelmap_draw(xpos, ypos, map);

    /* Draw raw alphamap without brush alpha. */
    brush->gx_brush_alpha = 255;
    gx_canvas_pixelmap_draw(xpos, ypos, map);

}

VOID test_image_convert_draw(GX_WINDOW *window)
{
GX_IMAGE_READER image_reader;
GX_PIXELMAP     pic_outmap;
GX_UBYTE mode = GX_IMAGE_READER_MODE_ALPHA | GX_IMAGE_READER_MODE_ROTATE_CW | GX_IMAGE_READER_MODE_COMPRESS;
GX_PIXELMAP *pixelmap;

    gx_window_background_draw(window);

    gx_context_pixelmap_get(GX_PIXELMAP_ID__PNG_A, &pixelmap);

    gx_image_reader_create(&image_reader,
                           pixelmap -> gx_pixelmap_data,
                          (INT)(pixelmap -> gx_pixelmap_data_size),
                          GX_COLOR_FORMAT_565RGB, mode);

    if (gx_image_reader_start(&image_reader, &pic_outmap) == GX_SUCCESS)
    {
        gx_canvas_pixelmap_draw(window->gx_widget_size.gx_rectangle_left,
                                window->gx_widget_size.gx_rectangle_top, &pic_outmap);

        dynamic_memory_free((VOID *)pic_outmap.gx_pixelmap_data);

        if (pic_outmap.gx_pixelmap_aux_data)
        {
            dynamic_memory_free((VOID *)pic_outmap.gx_pixelmap_aux_data);
        }
    }
}

/* This thread simulates user input.  Its priority is lower
   than the GUIX thread, so that GUIX finishes an operation 
   before this thread is able to issue the next command. */
static VOID control_thread_entry(ULONG input)
{
INT  frame_id = 1;
MAP_INFO *info;

    /* Reset draw function of button screen to test 32argb pixelmap draw. */
    gx_widget_draw_set(&button_screen, pixelmap_window_draw);

    for(test_brush_alpha = 255; test_brush_alpha > 0; test_brush_alpha -= 128)
    {
        info = test_map_info_list;

        while(info->map_id)
        {
            test_map_id = info->map_id;

            sprintf(test_comment, "brush alpha = %d, map id = %s", test_brush_alpha, info->id_name);

            gx_validation_set_frame_id(frame_id++);
            gx_validation_set_frame_comment(test_comment);
            gx_validation_screen_refresh();

            info++;
        }
    }

    test_brush_alpha = 0;
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Set brush alpha to 0");
    gx_validation_screen_refresh();

    test_brush_alpha = 255;
    test_map_id = GX_PIXELMAP_ID__PNG;
    gx_system_memory_allocator_set(GX_NULL, GX_NULL);
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Set memory allocator to NULL and test png draw.");
    gx_validation_screen_refresh();

    gx_widget_draw_set(&button_screen, pixelmap_window_invalid_map_draw);
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Test invalid pixelmap draw.");
    gx_validation_screen_refresh();

    gx_widget_draw_set(&button_screen, pixelmap_window_invalid_alphamap_draw);
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Test invalid alphamap draw.");
    gx_validation_screen_refresh();

    gx_system_memory_allocator_set(dynamic_memory_allocate, dynamic_memory_free);
    gx_widget_draw_set(&button_screen, test_image_convert_draw);
    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("Test image convert.");
    gx_validation_screen_refresh();

    /* Signal the end of the test case.  Verify the output. */
    gx_validation_end();

    exit(0);
}
