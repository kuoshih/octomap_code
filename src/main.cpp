/*
 Copyright 2018 NCU MATH.
 Developer: Kuo-Shih Tseng (kuoshih@math.ncu.edu.tw)
 Description: This code activate a node "octomap_data_node" 
 This node publishe a topic, octomap_loaded. 
 This code also demonstrates how to
 1. read .bt files
 2. read .ot files
 3. castray
 4. delete nodes
 $Revision: 1.0 $,  2021.08.20 
 

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

// %Tag(FULLTEXT)%
#include "ros/ros.h"
#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <octomap_msgs/conversions.h>
#include <octomap_msgs/Octomap.h>

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <list>
#include <cmath>

#define RAD2DEG(x) ((x)*180./M_PI)
using namespace octomap;
using namespace std;

//#define _GLIBCXX_USE_CXX11_ABI 0
octomap_msgs::Octomap octomap1;
ros::Publisher octomap_pub ;
octomap::ColorOcTree*  ptroctomap;
void fire(void);
void callback1(const ros::TimerEvent&);
int counter=0;

void print_query_info(point3d query, OcTreeNode* node) {
  if (node != NULL) {
    cout << "occupancy probability at " << query << ":\t " << node->getOccupancy() << endl;
  }
  else 
    cout << "occupancy probability at " << query << ":\t is unknown" << endl;    
}

void callback1(const ros::TimerEvent&)
{// update octomap and publish it. 


   octomap1.header.frame_id = "map";
   octomap1.header.stamp = ros::Time::now();
   octomap_msgs::fullMapToMsg(*ptroctomap, octomap1);

  	ROS_INFO("fire!!!");
	fire();
    octomap_pub.publish(octomap1);		
  	ROS_INFO("publish ot data");	
	
	counter++;
}



int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "octomap_data_node");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  // create a timer callback
  ros::Timer timer1 = n.createTimer(ros::Duration(0.5), callback1);
					
  ROS_INFO("Load .bt data and check for 3 points");			
  OcTree* tree = new OcTree("/home/kuoshih/catkin_ws/src/octomap_code/freiburg1_360.bt");
  point3d query (0., 0., 0.);
  OcTreeNode* result = tree->search (query);
  print_query_info(query, result);

  query = point3d(-1.,-1.,-1.);
  result = tree->search (query);
  print_query_info(query, result);

  query = point3d(1.,1.,1.);
  result = tree->search (query);
  print_query_info(query, result);

  ROS_INFO("castRay test");	
  const octomap::point3d origin(0., 0., 0.);
  const octomap::point3d d(1.,1.,1.); // direction
  point3d end;
  bool b=tree->castRay(origin,d,end,true,-1);
  ROS_INFO("origin=%2f,%2f,%2f",origin.x(),origin.y(),origin.z());
  ROS_INFO("dir=%2f,%2f,%2f",d.x(),d.y(),d.z());
  ROS_INFO("castRay=%d",b);
  ROS_INFO("end=%2f,%2f,%2f",end.x(),end.y(),end.z());
  tree->deleteNode(end.x(),end.y(),end.z(),0);
  tree->castRay(origin,d,end,true,-1);
  ROS_INFO("After deletion");
  ROS_INFO("end=%2f,%2f,%2f",end.x(),end.y(),end.z());/**/

  ROS_INFO("Load .ot file and publish it");
  octomap_pub = n.advertise<octomap_msgs::Octomap>("octomap_loaded", 1);
  octomap::AbstractOcTree* tree1 = AbstractOcTree::read("/home/kuoshih/catkin_ws/src/octomap_code/freiburg1_360.ot");
  ROS_INFO("size=%d",tree1->size());
  ptroctomap = dynamic_cast<octomap::ColorOcTree*>(tree1);
  ROS_INFO("address=%p",ptroctomap);

  ros::spin();
  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  return 0;
}

void fire(void)
{
	  for(int i=-50;i<50;i++)
	  {
			for(int j=-50;j<50;j++)
			{
			  const octomap::point3d origin(0,0,0);
			  const octomap::point3d d(i*1.0,j*1.0,2.0); // direction
			  point3d end;
			  bool b=ptroctomap->castRay(origin,d,end,true,2);
			  ptroctomap->deleteNode(end.x(),end.y(),end.z(),0);
			}
	  }
	    ROS_INFO("size=%d",ptroctomap->size());
}
