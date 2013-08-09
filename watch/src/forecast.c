#include <pebble_os.h>
#include "forecast.h"

bool forecast_from_bridge_dict(DictionaryIterator* dict, Forecast* forecast) {
    Tuple* data_tuple = dict_find(dict, 10);
    if (data_tuple) {
      forecast->dummy_integer = data_tuple->value->int16;
    }

    data_tuple = dict_find(dict, 20);
    if (data_tuple) {
      forecast->another_dummy_integer = data_tuple->value->int16;
    }

    data_tuple = dict_find(dict, 30);
    if (data_tuple && data_tuple->type == TUPLE_CSTRING) {
      forecast->dummy_string = data_tuple->value->cstring;
    }
  return true;
};
