#pragma once

#include <mc_control/fsm/State.h>
#include <mc_tasks/CompliantEndEffectorTask.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <mc_rtc_ros/ros.h>
#include <thread>

struct MinimumJerkController_Fitts : mc_control::fsm::State
{

  void configure(const mc_rtc::Configuration & config) override;

  void start(mc_control::fsm::Controller & ctl) override;

  bool run(mc_control::fsm::Controller & ctl) override;

  void teardown(mc_control::fsm::Controller & ctl) override;

private:
  void rosSpinner();

private:
  Eigen::Vector3d initPos_;
  bool init_;

  std::shared_ptr<rclcpp::Node> nh_;
  std::thread spinThread_;
  typename rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr pose_pub_;
};
