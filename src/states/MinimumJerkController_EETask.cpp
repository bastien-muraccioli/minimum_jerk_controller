#include "MinimumJerkController_EETask.h"

#include "../MinimumJerkController.h"

void MinimumJerkController_EETask::configure(const mc_rtc::Configuration & config) {}

void MinimumJerkController_EETask::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  auto & robot = ctl.robot();

  ctl.datastore().assign<std::string>("ControlMode", "Torque");
  mc_rtc::log::success("[MinJerkCtrl] Switched to Switch state - {} controlled",
                       ctl.datastore().get<std::string>("ControlMode"));

  std::shared_ptr<mc_tasks::CompliantEndEffectorTask> ee_task = std::make_shared<mc_tasks::CompliantEndEffectorTask>(
      "FT_sensor_mounting", ctl.robots(), ctl.robot().robotIndex(), 1.0, 10000.0);
  ctl.solver().addTask(ee_task);
}

bool MinimumJerkController_EETask::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  return false;
}

void MinimumJerkController_EETask::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
}

EXPORT_SINGLE_STATE("MinimumJerkController_EETask", MinimumJerkController_EETask)
