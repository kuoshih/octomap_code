
## Abstract
This sampel code is to deal with octomap data.
This code activate a node "octomap_data_node" 
This node publishe a topic, octomap_loaded. 
This code also demonstrates how to
 1. read .bt files
 2. read .pt files
 3. castray
 4. delete nodes (in fire function)
You can see the octomap in rviz.

## About us

Developer:   
* Kuo-Shih Tseng   
Contact: kuoshih@math.ncu.edu.tw   
Date: 2021/08/20  
License: Apache 2.0  


## Compile the code
$ cd catkin_ws/src  
$ git clone https://github.com/kuoshih/octomap_code 
$ cd ..  
$ catkin_make or catkin build

Or Download this this code to pi\catkin_ws\src.   
Unzip octomap_code.zip to replace the original code.
  
$cd catkin_ws  
$catkin_make or catkin build 

## Run the code   
# roscore  # Terminal 1
$ rosrun octomap_code main #Terminal 1

## rviz
$rviz  
Open the rviz configuration in /home/YOUR_NAME/catkin_ws/src/octomap/rviz/octomap_rviz.rviz
Then you will see the load octomap.
![alt text](https://github.com/kuoshih/octomap_code/blob/main/document/rviz.png)  

## Edit code  
You can edit src/main.cpp for your project.

