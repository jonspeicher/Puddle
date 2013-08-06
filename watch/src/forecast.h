#pragma once

// TBD: Remove this - J. Speicher (8/6/13)

#include "http.h"

typedef struct {
  int16_t dummy_integer;
  int16_t another_dummy_integer;
  char* dummy_string[20];
} Forecast;

typedef void (*ForecastSuccessHandler)(Forecast* forecast);
typedef void (*ForecastFailureHandler)();

typedef struct {
  ForecastSuccessHandler success;
  ForecastFailureHandler failure;
} ForecastCallbacks;

// TBD: Make this ForecastCallbacks and do type-unpacking - J. Speicher (8/6/13)

void forecast_register_callbacks(HTTPCallbacks callbacks, void* ctx);
bool forecast_request_forecast();
