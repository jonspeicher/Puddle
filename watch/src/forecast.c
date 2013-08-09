// ----------------------------------------------------------------------------
// forecast - Provides data structures and methods for manipulating forecasts
// Copyright (c) 2013 Jonathan Speicher (jon.speicher@gmail.com)
// Licensed under the MIT license: http://opensource.org/licenses/MIT
// ----------------------------------------------------------------------------

#include <pebble_os.h>
#include <stdint.h>
#include "forecast.h"

// Define the keys used in the dictionary returned by the bridge.

// TBD: These should be real, as should the conversions - J. Speicher (8/9/13)

#define DUMMY_INTEGER_KEY         10
#define ANOTHER_DUMMY_INTEGER_KEY 20
#define DUMMY_STRING_KEY          30

// Private functions.

static bool get_int16(DictionaryIterator* dict, uint32_t key, int16_t* dest);
static bool get_cstring(DictionaryIterator* dict, uint32_t key, char** dest);

// Public functions -----------------------------------------------------------

bool forecast_from_bridge_dict(DictionaryIterator* dict, Forecast* forecast) {
  // TBD: Test results - J. Speicher (8/9/13)
  get_int16(dict, DUMMY_INTEGER_KEY, &forecast->dummy_integer);
  get_int16(dict, ANOTHER_DUMMY_INTEGER_KEY, &forecast->another_dummy_integer);
  get_cstring(dict, DUMMY_STRING_KEY, &forecast->dummy_string);
  return true;
};

// Private functions ----------------------------------------------------------

bool get_int16(DictionaryIterator* dict, uint32_t key, int16_t* dest) {
  Tuple* tuple = dict_find(dict, key);
  if (tuple && tuple->type == TUPLE_INT) {
    *dest = tuple->value->int16;
    return true;
  }
  return false;
}

bool get_cstring(DictionaryIterator* dict, uint32_t key, char** dest) {
  Tuple* tuple = dict_find(dict, key);
  if (tuple && tuple->type == TUPLE_CSTRING) {
    *dest = tuple->value->cstring;
    return true;
  }
  return false;
}
