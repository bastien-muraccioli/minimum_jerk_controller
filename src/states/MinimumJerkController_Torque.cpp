#include "MinimumJerkController_Torque.h"

#include "../MinimumJerkController.h"

void MinimumJerkController_Torque::configure(const mc_rtc::Configuration & config) {}

void MinimumJerkController_Torque::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  auto & robot = ctl.robot();

  ctl.datastore().assign<std::string>("ControlMode", "Torque");
  mc_rtc::log::success("[MinJerkCtrl] Switched to Switch state - {} controlled",
                       ctl.datastore().get<std::string>("ControlMode"));
}

bool MinimumJerkController_Torque::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  return false;
}

void MinimumJerkController_Torque::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
}

EXPORT_SINGLE_STATE("MinimumJerkController_Torque", MinimumJerkController_Torque)
