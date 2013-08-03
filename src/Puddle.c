#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "http.h"

#define MY_UUID { 0x91, 0x41, 0xB6, 0x28, 0xBC, 0x89, 0x49, 0x8E, 0xB1, 0x47, 0x04, 0x9F, 0x49, 0xC0, 0x99, 0xAD }
PBL_APP_INFO(MY_UUID,
             "Puddle", "Jon Speicher",
             0, 1, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

#define DUMMY_COOKIE 100

Window window;
TextLayer debugLayer;

void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  DictionaryIterator *body;
  HTTPResult result = http_out_get("http://latrice.local:9000/response.json", DUMMY_COOKIE, &body);

  switch ((int) result)
  {
    case HTTP_OK:
      break;
    case HTTP_BUSY:
      text_layer_set_text(&debugLayer, "busy");
      return;
    case HTTP_INVALID_ARGS:
      text_layer_set_text(&debugLayer, "invalid args");
      return;
    case HTTP_NOT_ENOUGH_STORAGE:
      text_layer_set_text(&debugLayer, "storage");
      return;
    case HTTP_INTERNAL_INCONSISTENCY:
      text_layer_set_text(&debugLayer, "incons");
      return;
    default:
      text_layer_set_text(&debugLayer, "default");
      return;
  }

  dict_write_int32(body, 1, 100);
  dict_write_int32(body, 2, 200);
  dict_write_cstring(body, 3, "us");

  if (http_out_send() != HTTP_OK) {
    text_layer_set_text(&debugLayer, "send Failed!");
    return;
  }
}

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  text_layer_set_text(&debugLayer, "Reset!");
  app_message_out_release();
}

void click_config_provider(ClickConfig **config, Window *window) {
  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;
  config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
}

void http_request_failure_handler(int32_t cookie, int http_status, void* context) {
  text_layer_set_text(&debugLayer, "request Failed!");
}

void http_request_success_handler(int32_t cookie, int http_status, DictionaryIterator* received, void* context) {
    text_layer_set_text(&debugLayer, "request Success!");
}

void handle_init(AppContextRef ctx) {
  window_init(&window, "Puddle Main");
  window_stack_push(&window, true /* Animated */);

  text_layer_init(&debugLayer, GRect(0, 65, 144, 30));
  text_layer_set_text_alignment(&debugLayer, GTextAlignmentCenter);
  text_layer_set_text(&debugLayer, "Debug Layer");
  text_layer_set_font(&debugLayer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  layer_add_child(&window.layer, &debugLayer.layer);

  window_set_click_config_provider(&window, (ClickConfigProvider) click_config_provider);

  http_set_app_id(54332);
  http_register_callbacks((HTTPCallbacks) {
    .failure = http_request_failure_handler,
    .success = http_request_success_handler
    },
    (void*) ctx
  );
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .messaging_info = {
      .buffer_sizes = {
        .inbound = 124,
        .outbound = 256,
      }
    }
  };
  app_event_loop(params, &handlers);
}
