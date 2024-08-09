#include "MinimumJerkController_Fitts.h"
#include <std_msgs/Float32MultiArray.h>
#include "../MinimumJerkController.h"

void MinimumJerkController_Fitts::configure(const mc_rtc::Configuration & config) {}

void MinimumJerkController_Fitts::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  auto & robot = ctl.robot();

  nh_ = mc_rtc::ROSBridge::get_node_handle();
  spinThread_ = std::thread(std::bind(&MinimumJerkController_Fitts::rosSpinner, this));

  pose_pub_ = nh_->advertise<std_msgs::Float32MultiArray>("EE_position", 1);

  ctl.datastore().assign<std::string>("ControlMode", "Torque");
  mc_rtc::log::success("[MinJerkCtrl] Switched to Switch state - {} controlled",
                       ctl.datastore().get<std::string>("ControlMode"));

  std::shared_ptr<mc_tasks::CompliantEndEffectorTask> ee_task = std::make_shared<mc_tasks::CompliantEndEffectorTask>(
      "FT_sensor_mounting", ctl.robots(), ctl.robot().robotIndex(), 50.0, 10000.0);
  Eigen::Vector6d compliance;
  compliance << 0.05, 0.05, 0.05, 0.05, 1.5, 1.5;
  ee_task->setComplianceVector(compliance);
  ee_task->orientationTask->stiffness(50.0);
  ctl.solver().addTask(ee_task);

  ctl.datastore().call<void, double>("EF_Estimator::setGain", 10);
  // Enable feedback from external forces estimator
  if(!ctl.datastore().call<bool>("EF_Estimator::isActive"))
  {
    ctl.datastore().call("EF_Estimator::toggleActive");
  }
  // Enable force sensor usage if not active
  if(!ctl.datastore().call<bool>("EF_Estimator::useForceSensor"))
  {
    ctl.datastore().call("EF_Estimator::toggleForceSensor");
  }
}

bool MinimumJerkController_Fitts::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
  Eigen::Vector3d pose = ctl.robot().frame("FT_sensor_mounting").position().translation();

  std_msgs::Float32MultiArray msg;
  msg.data.emplace_back(pose.y());
  msg.data.emplace_back(pose.z());
  pose_pub_.publish(msg);

  return false;
}

void MinimumJerkController_Fitts::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<MinimumJerkController &>(ctl_);
}

void MinimumJerkController_Fitts::rosSpinner()
{
  mc_rtc::log::info("ROS spinner thread created");
  ros::Rate r(0.001);
  while(ros::ok())
  {
    ros::spinOnce();
    r.sleep();
  }
  mc_rtc::log::info("ROS spinner destroyed");
}
EXPORT_SINGLE_STATE("MinimumJerkController_Fitts", MinimumJerkController_Fitts)
