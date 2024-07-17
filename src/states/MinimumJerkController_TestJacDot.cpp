#include "MinimumJerkController_TestJacDot.h"

#include "../MinimumJerkController.h"

void MinimumJerkController_TestJacDot::configure(const mc_rtc::Configuration & config) {}

void MinimumJerkController_TestJacDot::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  auto & robot = ctl.robot();

  initPos_ = robot.bodyPosW("FT_sensor_mounting").translation();
  posTask = std::make_shared<mc_tasks::PositionTask>("FT_sensor_mounting", ctl.robots(), ctl.robot().robotIndex(), 5.0,
                                                     10000.0);
  posTask->reset();
  posTask->position(initPos_ + Eigen::Vector3d(0.0, 0.3, 0.0));
  ctl.solver().addTask(posTask);
  init_ = true;

  cor = new rbd::Coriolis(robot.mb());

  format = Eigen::IOFormat(2, 0, " ", "\n", "[", "]", " ", " ");

  ctl.datastore().assign<std::string>("ControlMode", "Torque");
  mc_rtc::log::success("[MinJerkCtrl] Switched to Switch state - {} controlled",
                       ctl.datastore().get<std::string>("ControlMode"));
}

bool MinimumJerkController_TestJacDot::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  auto & robot = ctl.robot();

  auto C = cor->coriolis(robot.mb(), robot.mbc());
  std::cout << "========== C ==========" << std::endl;
  std::cout << C.format(format) << std::endl;

  if(posTask->eval().norm() < 0.01 and posTask->speed().norm() < 0.001)
  {
    mc_rtc::log::info("Target reached switching target");
    if(init_)
    {
      posTask->position(initPos_ - Eigen::Vector3d(0.0, 0.3, 0.0));
      init_ = false;
    }
    else
    {
      posTask->position(initPos_ + Eigen::Vector3d(0.0, 0.3, 0.0));
      init_ = true;
    }
  }
  return false;
}

void MinimumJerkController_TestJacDot::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
}

EXPORT_SINGLE_STATE("MinimumJerkController_TestJacDot", MinimumJerkController_TestJacDot)
