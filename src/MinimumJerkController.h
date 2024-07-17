#pragma once

#include <mc_control/fsm/Controller.h>
#include <mc_tasks/CompliantPostureTask.h>
#include <mc_tasks/MinimumJerkTask.h>

#include "api.h"

struct MinimumJerkController_DLLAPI MinimumJerkController : public mc_control::fsm::Controller
{
  MinimumJerkController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

  bool run() override;

  void reset(const mc_control::ControllerResetData & reset_data) override;

  std::shared_ptr<mc_tasks::CompliantPostureTask> compPostureTask;
  std::shared_ptr<mc_tasks::MinimumJerkTask> minJerkTask;

  Eigen::VectorXd posture_target_log;

private:
  mc_rtc::Configuration config_;
  void getPostureTarget(void);
};
