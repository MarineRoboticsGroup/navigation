/*
 * twirling_cost_function.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: Morgan Quigley
 */

#include <base_local_planner/twirling_cost_function.h>
#include <ros/ros.h>
#include <math.h>

namespace base_local_planner {

void TwirlingCostFunction::setParams(double max_turning_radian, double twirling_scale, double wheelbase) {
  // TODO: move this to prepare if possible
  max_turning_radian_ = max_turning_radian;
  twirling_scale_ = twirling_scale;
  wheelbase_ = wheelbase;
}

double TwirlingCostFunction::scoreTrajectory(Trajectory &traj) {
  //chadchadchadchad
  double v = fabs(traj.xv_);
  double vtheta = fabs(traj.thetav_);
  double turning_angle;
  double res;

  if (v == 0.0){
      res = 9999.0;
  }
  else{
    turning_angle =  atan2(vtheta * wheelbase_, v);
    // if the turning angle is too large we remove this sample by increasing its cost
    if (turning_angle <= max_turning_radian_) { //0.348 radians is equal to 20 degrees 
      res = turning_angle/ ( 1.0 + v);
    }
    else {
      res = 9999.0;
    }
  }
  //chadchadchadchad
  if( v <0){
    ROS_INFO("the sampled velocity is %lf vtheta is %lf turning angle is %lf with a score of %lf", v, vtheta, turning_angle, res);
  }

  
  //ROS_INFO("TWIRLING_COST_FUNCTION");
  return res * twirling_scale_;  // add cost for making the robot spin
}

} /* namespace base_local_planner */
