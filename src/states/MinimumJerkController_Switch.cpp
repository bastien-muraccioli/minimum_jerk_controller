#include "MinimumJerkController_Switch.h"

#include "../MinimumJerkController.h"

void MinimumJerkController_Switch::configure(const mc_rtc::Configuration & config) {}

void MinimumJerkController_Switch::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  auto & robot = ctl.robot();

  initPos_ = robot.bodyPosW("FT_sensor_mounting").translation();

  Eigen::VectorXd W_1(9);
  W_1 << 1e7, 1e7, 1e7, 1e5, 1e5, 1e5, 1e2, 1e2, 1e2;
  Eigen::VectorXd W_2(8);
  W_2 << 1e0, 1e0, 1e0, 5 * 1e3, 2 * 1e3, 6 * 1e2, 6 * 1e2, 6 * 1e2;
  ctl.minJerkTask->W_1(W_1);
  ctl.minJerkTask->W_2(W_2);

  ctl.minJerkTask->setTarget(initPos_ + Eigen::Vector3d(0.1, 0.3, 0.0));
  ctl.compPostureTask->stiffness(0.0);
  ctl.compPostureTask->damping(1.0);
  ctl.compPostureTask->makeCompliant(true);

  ctl.solver().addTask(ctl.minJerkTask);

  oriTask_ = std::make_shared<mc_tasks::OrientationTask>("FT_sensor_mounting", ctl.robots(), ctl.robot().robotIndex(),
                                                         20.0, 10000.0);
  // ctl.solver().addTask(oriTask_);

  init_ = true;
  if(ctl.datastore().call<bool>("EF_Estimator::isActive"))
  {
    ctl.datastore().call("EF_Estimator::toggleActive");
  }

  ctl.gui()->addElement({"Controller"}, mc_rtc::gui::Checkbox("Trigger next target", gui_switch_));

  ctl.datastore().assign<std::string>("ControlMode", "Torque");
  mc_rtc::log::success("[MinJerkCtrl] Switched to Switch state - {} controlled",
                       ctl.datastore().get<std::string>("ControlMode"));
}

bool MinimumJerkController_Switch::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  if(ctl.minJerkTask->eval().norm() < 0.03 and ctl.minJerkTask->speed().norm() < 0.001 and gui_switch_)
  {
    mc_rtc::log::info("Target reached switching target");
    if(init_)
    {
      ctl.minJerkTask->setTarget(initPos_ + Eigen::Vector3d(0.1, -0.3, 0.0));
      init_ = false;
    }
    else
    {
      ctl.minJerkTask->setTarget(initPos_ + Eigen::Vector3d(0.1, 0.3, 0.0));
      init_ = true;
    }
  }
  else
  {
    // mc_rtc::log::info("Target not reached yet");
  }

  return false;
}

void MinimumJerkController_Switch::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
}

EXPORT_SINGLE_STATE("MinimumJerkController_Switch", MinimumJerkController_Switch)
