// TBD: Clean up this file, organize, statics for private functions, long lines,
// play golf on returns, etcetera - J. Speicher (8/6/13)

#include <pebble_os.h>

#include "forecast.h"
#include "http.h"

// TBD: Use the real forecast.io URL - J. Speicher (8/6/13)

#define FORECAST_URL    "http://latrice.local:9000/response.json"
#define FORECAST_COOKIE 100

static ForecastCallbacks forecast_callbacks = {
  .success = NULL,
  .failure = NULL
};

void http_request_success_handler(int32_t cookie, int http_status, DictionaryIterator* received, void* context) {
  Forecast forecast = {
    .dummy_integer = -1,
    .another_dummy_integer = -1,
    .dummy_string = ""
  };

  // TBD: Invert this logic and early-return? - J. Speicher (8/6/13)

  if (cookie == FORECAST_COOKIE && forecast_callbacks.success) {
    Tuple* data_tuple = dict_find(received, 10);
    if (data_tuple) {
      forecast.dummy_integer = data_tuple->value->int16;
    }

    data_tuple = dict_find(received, 20);
    if (data_tuple) {
      forecast.another_dummy_integer = data_tuple->value->int16;
    }

    data_tuple = dict_find(received, 30);
    if (data_tuple && data_tuple->type == TUPLE_CSTRING) {
      forecast.dummy_string = data_tuple->value->cstring;
    }

    // TBD: This probably needs a big comment; check to make sure that received
    // is also transient to be sure that this pattern is common in the Pebble
    // world - J. Speicher (8/6/13)

    forecast_callbacks.success(&forecast);
  }
}

void http_request_failure_handler(int32_t cookie, int http_status, void* context) {
  if ((cookie == FORECAST_COOKIE || cookie == 0) && forecast_callbacks.failure) {
    forecast_callbacks.failure();
  }
}

void forecast_register_callbacks(ForecastCallbacks callbacks, void* ctx) {
  forecast_callbacks = callbacks;
  HTTPCallbacks http_callbacks = {
    .success = http_request_success_handler,
    .failure = http_request_failure_handler
  };
  http_set_app_id(54332);
  http_register_callbacks(http_callbacks, ctx);
}

bool forecast_request_forecast() {
  DictionaryIterator* post_dict;
  HTTPResult result = http_out_get(FORECAST_URL, FORECAST_COOKIE, &post_dict);

  if (result != HTTP_OK) {
    return false;
  }

  // TBD: Make an actual request with actual request data, use symbolic keys,
  // pass request data in from user - J. Speicher (8/6/13)

  dict_write_int32(post_dict, 1, 100);
  dict_write_int32(post_dict, 2, 200);
  dict_write_cstring(post_dict, 3, "us");

  result = http_out_send();
  return (result == HTTP_OK);
}
