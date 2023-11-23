/*******************************************************************************/
/*  This file is auto-generated by Azure RTOS GUIX Studio. Do not edit this    */
/*  file by hand. Modifications to this file should only be made by running    */
/*  the Azure RTOS GUIX Studio application and re-generating the application   */
/*  specification file(s). For more information please refer to the Azure RTOS */
/*  GUIX Studio User Guide, or visit our web site at azure.com/rtos            */
/*                                                                             */
/*  GUIX Studio Revision 6.2.0.1                                               */
/*  Date (dd.mm.yyyy): 31.10.2022   Time (hh:mm): 14:11                        */
/*******************************************************************************/


#ifndef _RADIAL_PROGRESS_BAR_SPECIFICATIONS_H_
#define _RADIAL_PROGRESS_BAR_SPECIFICATIONS_H_

#include "gx_api.h"

/* Determine if C++ compiler is being used, if so use standard C.              */
#ifdef __cplusplus
extern   "C" {
#endif

/* Define widget ids                                                           */

#define ID_POS 1
#define ID_SHOW_TEXT 2
#define ID_SHOW_PERCENT 3
#define ID_TRANSPARENT 4
#define ID_NORMAL_WIDTH_SLIDER 5
#define ID_RADIUS_SLIDER 6
#define ID_SELECTED_WIDTH_SLIDER 7
#define ID_NORMAL_WIDTH_PROMPT 8
#define ID_SELECTED_WIDTH_PROMPT 9
#define ID_RADIUS_PROMPT 10
#define ID_ANCHOR_SLIDER 11
#define ID_ANCHOR_PROMPT 12
#define ID_ALIAS 13
#define ID_ROUND_END 14
#define ID_ALPHA_SLIDER 15


/* Define animation ids                                                        */

#define GX_NEXT_ANIMATION_ID 1


/* Define user event ids                                                       */

#define GX_NEXT_USER_EVENT_ID GX_FIRST_USER_EVENT


/* Declare properties structures for each utilized widget type                 */

typedef struct GX_STUDIO_WIDGET_STRUCT
{
   GX_CHAR *widget_name;
   USHORT  widget_type;
   USHORT  widget_id;
   #if defined(GX_WIDGET_USER_DATA)
   INT   user_data;
   #endif
   ULONG style;
   ULONG status;
   ULONG control_block_size;
   GX_RESOURCE_ID normal_fill_color_id;
   GX_RESOURCE_ID selected_fill_color_id;
   GX_RESOURCE_ID disabled_fill_color_id;
   UINT (*create_function) (GX_CONST struct GX_STUDIO_WIDGET_STRUCT *, GX_WIDGET *, GX_WIDGET *);
   void (*draw_function) (GX_WIDGET *);
   UINT (*event_function) (GX_WIDGET *, GX_EVENT *);
   GX_RECTANGLE size;
   GX_CONST struct GX_STUDIO_WIDGET_STRUCT *next_widget;
   GX_CONST struct GX_STUDIO_WIDGET_STRUCT *child_widget;
   ULONG control_block_offset;
   GX_CONST void *properties;
} GX_STUDIO_WIDGET;

typedef struct
{
    GX_CONST GX_STUDIO_WIDGET *widget_information;
    GX_WIDGET        *widget;
} GX_STUDIO_WIDGET_ENTRY;

typedef struct
{
    GX_RESOURCE_ID string_id; 
    GX_RESOURCE_ID font_id;
    GX_RESOURCE_ID normal_text_color_id;
    GX_RESOURCE_ID selected_text_color_id;
    GX_RESOURCE_ID disabled_text_color_id;
    GX_RESOURCE_ID unchecked_pixelmap_id;
    GX_RESOURCE_ID checked_pixelmap_id;
    GX_RESOURCE_ID unchecked_disabled_pixelmap_id;
    GX_RESOURCE_ID checked_disabled_pixelmap_id;
} GX_CHECKBOX_PROPERTIES;

typedef struct
{
    GX_RESOURCE_ID normal_pixelmap_id;
    GX_RESOURCE_ID selected_pixelmap_id;
} GX_ICON_PROPERTIES;

typedef struct
{
    int tickmark_count;
    int minval;
    int maxval;
    int current_val;
    int increment;
    GX_VALUE min_travel;
    GX_VALUE max_travel;
    GX_VALUE needle_width;
    GX_VALUE needle_height;
    GX_VALUE needle_inset;
    GX_VALUE needle_hotspot;
} GX_SLIDER_PROPERTIES;

typedef struct
{
    int min_val;
    int max_val;
    int current_val;
    int increment;
    GX_VALUE min_travel;
    GX_VALUE max_travel;
    GX_VALUE needle_width;
    GX_VALUE needle_height;
    GX_VALUE needle_inset;
    GX_VALUE needle_hotspot;
    GX_RESOURCE_ID lower_pixelmap;
    GX_RESOURCE_ID upper_pixelmap;
    GX_RESOURCE_ID needle_pixelmap;
} GX_PIXELMAP_SLIDER_PROPERTIES;

typedef struct
{
    GX_RESOURCE_ID string_id;
    GX_RESOURCE_ID font_id;
    GX_RESOURCE_ID normal_text_color_id;
    GX_RESOURCE_ID selected_text_color_id;
    GX_RESOURCE_ID disabled_text_color_id;
} GX_PROMPT_PROPERTIES;

typedef struct
{
    GX_RESOURCE_ID string_id;
    GX_RESOURCE_ID font_id;
    GX_RESOURCE_ID normal_text_color_id;
    GX_RESOURCE_ID selected_text_color_id;
    GX_RESOURCE_ID disabled_text_color_id;
    VOID (*format_func)(GX_NUMERIC_PROMPT *, INT);
    INT            numeric_prompt_value;
} GX_NUMERIC_PROMPT_PROPERTIES;

typedef struct
{
    GX_RESOURCE_ID wallpaper_id;
} GX_WINDOW_PROPERTIES;


/* Declare top-level control blocks                                            */

typedef struct PROGRESS_BAR_WINDOW_CONTROL_BLOCK_STRUCT
{
    GX_WINDOW_MEMBERS_DECLARE
    GX_PIXELMAP_SLIDER progress_bar_window_pixelmap_slider;
    GX_ICON progress_bar_window_icon_3;
    GX_ICON progress_bar_window_icon_4;
    GX_CHECKBOX progress_bar_window_checkbox;
    GX_CHECKBOX progress_bar_window_checkbox_1;
    GX_CHECKBOX progress_bar_window_checkbox_2;
    GX_SLIDER progress_bar_window_slider;
    GX_SLIDER progress_bar_window_slider_1;
    GX_SLIDER progress_bar_window_slider_2;
    GX_PROMPT progress_bar_window_prompt;
    GX_PROMPT progress_bar_window_prompt_1;
    GX_PROMPT progress_bar_window_prompt_2;
    GX_PROMPT progress_bar_window_normal_width_prompt;
    GX_PROMPT progress_bar_window_selected_width_prompt;
    GX_PROMPT progress_bar_window_radius_prompt;
    GX_PROMPT progress_bar_window_prompt_3;
    GX_PROMPT progress_bar_window_prompt_4;
    GX_SLIDER progress_bar_window_slider_3;
    GX_PROMPT progress_bar_window_anchor_prompt;
    GX_RADIAL_PROGRESS_BAR progress_bar_window_radial_progress_bar;
    GX_CHECKBOX progress_bar_window_checkbox_3;
    GX_CHECKBOX progress_bar_window_checkbox_4;
    GX_PROMPT progress_bar_window_alpha;
    GX_SLIDER progress_bar_window_alpha_slider;
    GX_NUMERIC_PROMPT progress_bar_window_alpha_prompt;
} PROGRESS_BAR_WINDOW_CONTROL_BLOCK;


/* extern statically defined control blocks                                    */

#ifndef GUIX_STUDIO_GENERATED_FILE
extern PROGRESS_BAR_WINDOW_CONTROL_BLOCK progress_bar_window;
#endif

/* Declare event process functions, draw functions, and callback functions     */

UINT window_event_handle(GX_WINDOW *widget, GX_EVENT *event_ptr);
VOID radial_progress_bar_draw(GX_RADIAL_PROGRESS_BAR *widget);

/* Declare the GX_STUDIO_DISPLAY_INFO structure                                */


typedef struct GX_STUDIO_DISPLAY_INFO_STRUCT 
{
    GX_CONST GX_CHAR *name;
    GX_CONST GX_CHAR *canvas_name;
    GX_CONST GX_THEME **theme_table;
    GX_CONST GX_STRING **language_table;
    USHORT   theme_table_size;
    USHORT   language_table_size;
    UINT     string_table_size;
    UINT     x_resolution;
    UINT     y_resolution;
    GX_DISPLAY *display;
    GX_CANVAS  *canvas;
    GX_WINDOW_ROOT *root_window;
    GX_COLOR   *canvas_memory;
    ULONG      canvas_memory_size;
    USHORT     rotation_angle;
} GX_STUDIO_DISPLAY_INFO;


/* Declare Studio-generated functions for creating top-level widgets           */

UINT gx_studio_checkbox_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_icon_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_slider_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_pixelmap_slider_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_radial_progress_bar_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_prompt_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_numeric_prompt_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
UINT gx_studio_window_create(GX_CONST GX_STUDIO_WIDGET *info, GX_WIDGET *control_block, GX_WIDGET *parent);
GX_WIDGET *gx_studio_widget_create(GX_BYTE *storage, GX_CONST GX_STUDIO_WIDGET *definition, GX_WIDGET *parent);
UINT gx_studio_named_widget_create(char *name, GX_WIDGET *parent, GX_WIDGET **new_widget);
UINT gx_studio_display_configure(USHORT display, UINT (*driver)(GX_DISPLAY *), GX_UBYTE language, USHORT theme, GX_WINDOW_ROOT **return_root);

/* Determine if a C++ compiler is being used.  If so, complete the standard
  C conditional started above.                                                 */
#ifdef __cplusplus
}
#endif

#endif                                       /* sentry                         */