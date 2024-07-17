/*
 * Copyright 2015-2024 CNRS-UM LIRMM, CNRS-AIST JRL
 */

#pragma once

#include <mc_tasks/TrajectoryTaskGeneric.h>

#include <mc_tvm/PositionFunction.h>

namespace mc_tasks
{

/*! \brief Control the position of a frame */
struct MC_TASKS_DLLAPI MinimumJerkEndEffectorTask : public TrajectoryTaskGeneric
{
public:
  /*! \brief Constructor
   *
   * \param frame Control frame
   *
   * \param stiffness Task stiffness
   *
   * \param weight Task weight
   */
  MinimumJerkEndEffectorTask(const mc_rbdyn::RobotFrame & frame);

  /*! \brief Constructor
   *
   * \param bodyName Name of the body to control
   *
   * \param robots Robots controlled by this task
   *
   * \param robotIndex Index of the robot controlled by this task
   *
   * \param stiffness Task stiffness
   *
   * \param weight Task weight
   *
   */
  MinimumJerkEndEffectorTask(const std::string & bodyName, const mc_rbdyn::Robots & robots, unsigned int robotIndex);

  virtual ~MinimumJerkEndEffectorTask() = default;

  /*! \brief Reset the task
   *
   * Set the task objective to the current body position
   */
  void reset() override;

  /*! \brief Get the position target */
  inline const Eigen::Vector3d & position() const noexcept
  {
    switch(backend_)
    {
      case Backend::TVM:
        return static_cast<mc_tvm::PositionFunction *>(errorT.get())->position();
      default:
        mc_rtc::log::error_and_throw("Not implemented");
    }
  }

  /*! \brief Set the position target
   *
   * \param pos Body position in world frame
   *
   */
  inline void position(const Eigen::Vector3d & pos) noexcept
  {
    switch(backend_)
    {
      case Backend::TVM:
        static_cast<mc_tvm::PositionFunction *>(errorT.get())->position(pos);
        break;
      default:
        mc_rtc::log::error_and_throw("Not implemented");
    }
  }

  /*! \brief Get the body point being controlled
   */
  inline const Eigen::Vector3d & bodyPoint() const noexcept
  {
    switch(backend_)
    {
      case Backend::TVM:
      {
        static Eigen::Vector3d res = Eigen::Vector3d::Zero();
        return res;
      }
      default:
        mc_rtc::log::error_and_throw("Not implemented");
    }
  }

  void addToGUI(mc_rtc::gui::StateBuilder & gui) override;

protected:
  mc_rbdyn::ConstRobotFramePtr frame_;
  void addToLogger(mc_rtc::Logger & logger) override;
};

} // namespace mc_tasks
