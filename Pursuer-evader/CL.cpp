#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "CL");

  ros::NodeHandle node;

   ros::Publisher vel_pub_=node.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 10);


  tf::TransformListener listener;

  ros::Rate rate(10.0);

  while (node.ok())
{
    tf::StampedTransform transform;
    try{
listener.lookupTransform("/robot_1/odom", "robot_0/odom",  ros::Time(0), transform);
/*ros::Time now = ros::Time::now();
ros::Time past = now - ros::Duration(5.0);

listener.waitForTransform("robot_1", now, "robot_0", past, "world", ros::Duration(1.0));
listener.lookupTransform("robot_1", now, "robot_0", past, "world" ,transform);*/
}

    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      //ros::Duration(1.0).sleep();
      //continue;
    }
    geometry_msgs::Twist vel;
    vel.angular.z = 4.0 * atan2(transform.getOrigin().y(),transform.getOrigin().x());
    vel.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2));
    vel_pub_.publish(vel);    

    rate.sleep();
}

  return 0;
}

