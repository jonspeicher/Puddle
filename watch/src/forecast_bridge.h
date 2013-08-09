#pragma once

typedef struct {
  int16_t dummy_integer;
  int16_t another_dummy_integer;
  char* dummy_string;
} Forecast;

typedef void (*ForecastSuccessHandler)(Forecast* forecast);
typedef void (*ForecastFailureHandler)();

typedef struct {
  ForecastSuccessHandler success;
  ForecastFailureHandler failure;
} ForecastCallbacks;

void forecast_bridge_register_callbacks(ForecastCallbacks callbacks, void* ctx);
bool forecast_bridge_request_forecast();
