#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xE3, 0x7B, 0xFC, 0xE9, 0x30, 0xD7, 0x4B, 0xC3, 0x96, 0x93, 0x15, 0x0C, 0x35, 0xDC, 0xB8, 0x58 }
PBL_APP_INFO(MY_UUID,
             "Puddle", "Jon Speicher",
             0, 1, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer debug_layer;

void handle_init(AppContextRef ctx) {
  window_init(&window, "Puddle Main");
  window_stack_push(&window, true /* Animated */);

  text_layer_init(&debug_layer, GRect(0, 65, 144, 30));
  text_layer_set_text_alignment(&debug_layer, GTextAlignmentCenter);
  text_layer_set_text(&debug_layer, "Debug Layer");
  text_layer_set_font(&debug_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  layer_add_child(&window.layer, &debug_layer.layer);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
