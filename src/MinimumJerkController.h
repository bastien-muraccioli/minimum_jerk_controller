#pragma once

#include <mc_control/fsm/Controller.h>

#include "api.h"

struct MinimumJerkController_DLLAPI MinimumJerkController : public mc_control::fsm::Controller
{
  MinimumJerkController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

  bool run() override;

  void reset(const mc_control::ControllerResetData & reset_data) override;

private:
  mc_rtc::Configuration config_;
};
