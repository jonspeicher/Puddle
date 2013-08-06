// TBD: Screen is 144 px wide x 168 px tall, status bar is 16 px tall

#include <pebble_os.h>
#include <pebble_app.h>
#include <pebble_fonts.h>

#include "forecast.h"
#include "http.h"

// TBD: Use define from http.h
#define MY_UUID { 0x91, 0x41, 0xB6, 0x28, 0xBC, 0x89, 0x49, 0x8E, 0xB1, 0x47, 0x04, 0x9F, 0x49, 0xC0, 0x99, 0xAD }
PBL_APP_INFO(MY_UUID,
             "Puddle", "Jon Speicher",
             0, 1, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer debugLayer;

void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  bool success = forecast_request_forecast();

  if (!success) {
    text_layer_set_text(&debugLayer, "request failed");
  }
}

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  text_layer_set_text(&debugLayer, "reset");
}

void click_config_provider(ClickConfig **config, Window *window) {
  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;
  config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
}

void forecast_request_failure_handler() {
  text_layer_set_text(&debugLayer, "response failed");
}

static char ten[20];
static char twenty[20];
static char thirty[20];
static char label[60];
void forecast_request_success_handler(Forecast* forecast) {
  /*
  Tuple* data_tuple = dict_find(received, 10); // TBD: key in response.json that maps to +int
  if (data_tuple) {
    snprintf(ten, 20, "%d,", data_tuple->value->int16);
  } else {
    snprintf(ten, 20, "no tuple,");
  }

  data_tuple = dict_find(received, 20);
  if (data_tuple) {
    snprintf(twenty, 20, "%d,", data_tuple->value->int16);
  } else {
    snprintf(twenty, 20, "no tuple,");
  }

  data_tuple = dict_find(received, 30);
  if (data_tuple) {
    snprintf(thirty, 20, "%s", data_tuple->value->cstring);
  } else {
    snprintf(thirty, 20, "no tuple");
  }

  label[0] = '\0';
  strcat(label, ten);
  strcat(label, twenty);
  strcat(label, thirty);

  text_layer_set_text(&debugLayer, label);
  */
  text_layer_set_text(&debugLayer, "request success");
}

void handle_init(AppContextRef ctx) {
  window_init(&window, "Puddle Main");
  window_stack_push(&window, true /* Animated */);

  text_layer_init(&debugLayer, window.layer.frame);
  text_layer_set_text_alignment(&debugLayer, GTextAlignmentCenter);
  text_layer_set_text(&debugLayer, "Debug Layer");
  text_layer_set_font(&debugLayer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  layer_add_child(&window.layer, &debugLayer.layer);

  window_set_click_config_provider(&window, (ClickConfigProvider) click_config_provider);

  ForecastCallbacks callbacks = {
    .success = forecast_request_success_handler,
    .failure = forecast_request_failure_handler
  };
  forecast_register_callbacks(callbacks, (void*) ctx);
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
