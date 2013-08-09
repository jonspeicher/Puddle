// ----------------------------------------------------------------------------
// forecast - Provides data structures and methods for manipulating forecasts
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#pragma once

#include <pebble_os.h>
#include <stdint.h>

// Defines the data contained within a forecast.

typedef struct {
  int16_t dummy_integer;
  int16_t another_dummy_integer;
  char* dummy_string;
} Forecast;

// Converts a forecast contained within a dictionary returned by the forecast
// bridge into a forecast data structure. Note that if a particular field in
// the dictionary representation is not present or is in an unexpected format,
// the corresponding field in the forecast will not be modified. It is
// therefore the responsibility of the caller to initialize the forecast to
// sensible defaults or to discard nonconforming forecasts. This function will
// return false in the event that not all fields can be successfully populated.

bool forecast_from_bridge_dict(DictionaryIterator* dict, Forecast* forecast);
