#include <pebble_os.h>

#include "forecast.h"
#include "http.h"

// TBD: Use the real forecast.io URL - J. Speicher (8/6/13)

#define FORECAST_URL    "http://latrice.local:9000/response.json"
#define FORECAST_COOKIE 100

bool forecast_register_callbacks(ForecastCallbacks callbacks) {
  return true;
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
