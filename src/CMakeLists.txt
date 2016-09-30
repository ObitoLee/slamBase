# 增加PCL库的依赖
FIND_PACKAGE(PCL REQUIRED COMPONENTS common io visualization filters)

# 增加opencv的依赖
FIND_PACKAGE(OpenCV REQUIRED)

# 添加头文件和库文件
INCLUDE_DIRECTORIES(${PCL_INCLUDE_DIRS})

# 添加自定义库
ADD_LIBRARY(slambase slamBase.cpp)

# 生成可执行文件并链接库

# ADD_EXECUTABLE(generate_pointcloud generatePointCloud.cpp)
# TARGET_LINK_LIBRARIES(generate_pointcloud slambase ${OpenCV_LIBS} ${PCL_LIBRARIES})

#ADD_EXECUTABLE(feature_detect detectFeatures.cpp)
#TARGET_LINK_LIBRARIES(feature_detect slambase ${OpenCV_LIBS} ${PCL_LIBRARIES})

ADD_EXECUTABLE(join_PointCloud joinPointCloud.cpp)
TARGET_LINK_LIBRARIES(join_PointCloud slambase ${OpenCV_LIBS} ${PCL_LIBRARIES})
