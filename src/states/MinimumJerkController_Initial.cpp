#include "MinimumJerkController_Initial.h"

#include "../MinimumJerkController.h"

void MinimumJerkController_Initial::configure(const mc_rtc::Configuration & config) {}

void MinimumJerkController_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
}

bool MinimumJerkController_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  output("OK");
  return true;
}

void MinimumJerkController_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
}

EXPORT_SINGLE_STATE("MinimumJerkController_Initial", MinimumJerkController_Initial)
