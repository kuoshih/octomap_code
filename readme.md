![alt text](https://github.com/Hypha-ROS/hypharos_minibot/blob/master/document/logo/HyphaROS_logo_2.png)  
![alt text](https://github.com/Hypha-ROS/hypharos_minibot/blob/master/document/HyphaROS_MiniBot_photo.jpg)  

## Abstract
This code is for final projects of MA5039 Perception and Estimation in Robotics.
It is a sample code based on HyphaROS Minibot.
This code activate a node "main" and the other sensor nodes. 
Main node subscribes three topics -- imu_data, odom, and scan. 
You can access data from three Callback functions in src/main.cpp.
There is a maker for landmarks or targets.
You can see it in rviz.

## About us

Developer:   
* Kuo-Shih Tseng   
Contact: kuoshih@math.ncu.edu.tw   
Date: 2018/10/22  
License: Apache 2.0  


## Compile the code
$ cd catkin_ws/src  
$ git clone https://github.com/kuoshih/hypharos_minibot   
$ cd ..  
$ catkin_make  

Or Download this this code to pi\catkin_ws\src.   
Unzip hypharos_minibot.zip to replace the original code.
  
$cd catkin_ws  
$catkin_make  

## Run the code   
$roslaunch hypharos_minibot project_sample.launch

## rviz
$rviz  
Press "Add" button in rviz, then select "Marker"  
Set fixed frame as "target"  
![alt text](https://github.com/kuoshih/hypharos_minibot/blob/master/document/target.png)  
## Edit code  
You can edit src/main.cpp for your project.

## About Minibot
More information about Minibot can be found https://github.com/Hypha-ROS/hypharos_minibot.   
