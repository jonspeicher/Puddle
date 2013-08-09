#pragma once

#include <pebble_os.h>
#include <stdint.h>

typedef struct {
  int16_t dummy_integer;
  int16_t another_dummy_integer;
  char* dummy_string;
} Forecast;

bool forecast_from_bridge_dict(DictionaryIterator* dict, Forecast* forecast);
