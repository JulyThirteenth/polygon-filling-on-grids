#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include "../include/test/parse_csv.h"

using namespace JulyThirteenth;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test");
    ros::NodeHandle nh;
    std::string csv_path;
    nh.param<std::string>("/test_node/csv_path", csv_path, "src/test/src/polygon_obstacles.csv");
    ROS_INFO("csv_path: %s",csv_path.c_str());
    double padding;
    nh.param<double>("/test_node/padding", padding, 4.);
    ROS_INFO("padding: %f",padding);
    double resolution;
    nh.param<double>("/test_node/resolution", resolution, 0.1);
    ROS_INFO("resolution: %f",resolution);
    std::shared_ptr<struct GridMap> p = parseCsv(csv_path, padding, resolution);
    if (p == nullptr)
    {
        ROS_ERROR("The csv file not exists!");
        return 0;
    }
    nav_msgs::OccupancyGrid map;
    map.info.width = p->cols;
    map.info.height = p->rows;
    map.info.resolution = resolution;
    map.data.resize(p->cols * p->rows);
    for (int i = 0; i < p->cols; i++)
    {
        for (int j = 0; j < p->rows; j++)
        {
            map.data[i + j * p->cols] = (p->grids[i][j] == true ? 100 : 0);
        }
    }
    map.header.frame_id = "map";
    map.header.stamp = ros::Time::now();
    ros::Publisher pub_map = nh.advertise<nav_msgs::OccupancyGrid>("/test_map", 1, true);
    while (ros::ok())
    {
        pub_map.publish(map);
        ros::spinOnce();
    }
    return 0;
}