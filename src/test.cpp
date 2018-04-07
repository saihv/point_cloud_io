#include "point_cloud_io/Read.hpp"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl_conversions/pcl_conversions.h>
// define the following in order to eliminate the deprecated headers warning
#define VTK_EXCLUDE_STRSTREAM_HEADERS
#include <pcl/io/vtk_lib_io.h>

using namespace std;
using namespace ros;
using namespace pcl;
using namespace pcl::io;
using namespace pcl_conversions;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "read");
  	ros::NodeHandle n;
	ros::Publisher pub;
	ros::Rate loop_rate(10);
	ROS_INFO("Attempting to read PLY file");
    PointCloud<PointXYZRGBNormal> pointCloud;
    if (loadPLYFile("/home/sai/Dropbox/ICUAS/ICUAS tests/urbanSmall2/reconstruction_sequential/cloud_and_poses.ply", pointCloud) != 0) {
		ROS_ERROR("Unable to read ply file");
		return 1;
	}
    pub = n.advertise<sensor_msgs::PointCloud2> ("output", 1);

	while(ros::ok())
    {
		sensor_msgs::PointCloud2 pointCloudMessage;
    	// Define PointCloud2 message.
    	toROSMsg(pointCloud, pointCloudMessage);
		
		pointCloudMessage.header.stamp = ros::Time::now();
		pointCloudMessage.header.frame_id = "world";
		pub.publish (pointCloudMessage);
	    ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}