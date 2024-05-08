/*
 * @Author: Shuyang Zhang
 * @Date: 2024-05-08 15:38:07
 * @LastEditors: ShuyangUni shuyang.zhang1995@gmail.com
 * @LastEditTime: 2024-05-08 16:13:01
 * @Description:
 *
 * Copyright (c) 2024 by Shuyang Zhang, All Rights Reserved.
 */

#include <nav_msgs/Odometry.h>
#include <ros/ros.h>

#include <fstream>
#include <string>

std::ofstream g_file;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
  double ts = msg->header.stamp.toSec();
  if (g_file.is_open()) {
    char char_buf[200];
    sprintf(char_buf, "%.6f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n", ts,
            msg->pose.pose.position.x, msg->pose.pose.position.y,
            msg->pose.pose.position.z, msg->pose.pose.orientation.x,
            msg->pose.pose.orientation.y, msg->pose.pose.orientation.z,
            msg->pose.pose.orientation.w);
    std::string str_buf = char_buf;
    g_file << str_buf;
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    ROS_INFO("Input argc: %d", argc);
    ROS_WARN("Usage: %s [savepath]", argv[0]);
    return 1;
  }

  std::string save_filename = argv[1];
  g_file.open(save_filename.c_str());
  if (g_file.is_open())
    ROS_INFO("Saving odometry file in %s", save_filename.c_str());

  ros::init(argc, argv, "odom_save_node");
  ros::NodeHandle nh("~");
  ros::Subscriber sub =
      nh.subscribe("/robot/dlio/odom_node/odom", 5, odomCallback);

  ros::spin();
  return 0;
}
