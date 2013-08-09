#pragma once

#include "http.h"

#define FORECAST_BRIDGE_APP_UUID HTTP_UUID

typedef void (*ForecastSuccessHandler)(Forecast* forecast);
typedef void (*ForecastFailureHandler)();

typedef struct {
  ForecastSuccessHandler success;
  ForecastFailureHandler failure;
} ForecastCallbacks;

void forecast_bridge_register_callbacks(ForecastCallbacks callbacks, void* ctx);
bool forecast_bridge_request_forecast();
