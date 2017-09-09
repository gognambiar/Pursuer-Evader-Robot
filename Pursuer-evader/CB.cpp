#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <turtlesim/Pose.h>

std::string turtle_name;

void topicCallbackOdometry(const nav_msgs::Odometry::ConstPtr& msg)
{
  static tf::TransformBroadcaster br;
  tf::Transform transform;
transform.setOrigin( tf::Vector3(msg->pose.pose.position.x,msg->pose.pose.position.y, 0.0) );
transform.setRotation( tf::Quaternion(0, 0, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w ));
br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name+"/odom"));
}

int main(int argc, char** argv){
  //ros::init(argc, argv, "my_tf_broadcaster");
   ros::init(argc, argv, "CB");
  if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  turtle_name = argv[1];

  ros::NodeHandle node;
//ros::Subscriber sub = node.subscribe("robot_0/base_pose_ground_truth", 10, &poseCallback);
//ros::Subscriber sub = node.subscribe("robot_0/odom", 10, &topicCallbackOdometry);
  ros::Subscriber sub = node.subscribe(turtle_name+"/odom", 10, &topicCallbackOdometry);


  ros::spin();
  return 0;
}
