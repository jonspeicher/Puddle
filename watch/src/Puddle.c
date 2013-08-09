// TBD: Screen is 144 px wide x 168 px tall, status bar is 16 px tall

#include <pebble_os.h>
#include <pebble_app.h>
#include <pebble_fonts.h>

#include "forecast.h"
#include "forecast_bridge.h"

PBL_APP_INFO(FORECAST_BRIDGE_APP_UUID,
             "Puddle", "Jon Speicher",
             0, 1, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer debugLayer;

void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  bool success = forecast_bridge_request_forecast();

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

// TBD: This is still a mess of course - J. Speicher (8/6/13)

static char label[60];
void forecast_request_success_handler(Forecast* forecast) {
  snprintf(label, 60, "%d,%d,%s", forecast->dummy_integer,
      forecast->another_dummy_integer, forecast->dummy_string);
  text_layer_set_text(&debugLayer, label);
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
  forecast_bridge_register_callbacks(callbacks, (void*) ctx);
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
