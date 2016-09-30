/*************************************************************************
    > File Name: src/jointPointCloud.cpp
    > Author: Xiang gao
    > Mail: gaoxiang12@mails.tsinghua.edu.cn 
    > Created Time: 2015年07月22日 星期三 20时46分08秒
 ************************************************************************/
#include<iostream>
using namespace std;

#include "slamBase.h"

static ParameterReader cfg;
CAMERA_INTRINSIC_PARAMETERS camera = getDefaultCamera(cfg);
double goodMatchThreshold = atof( cfg.getData( "good_match_threshold" ).c_str() );
string detector = cfg.getData("detector");
string descriptor = cfg.getData("descriptor");
double gridsize = atof(cfg.getData("voxel_grid").c_str() );

int main( )
{
    //本节要拼合data中的两对图像
    // 声明两个帧，FRAME结构请见include/slamBase.h
    FRAME frame1, frame2;
    
    //读取图像
    frame1.rgb = imread( "./data/rgb1.png" );
    frame1.depth = imread( "./data/depth1.png", -1);
    frame2.rgb = imread( "./data/rgb2.png" );
    frame2.depth = imread( "./data/depth2.png", -1 );

    // 提取特征并计算描述子
    computeKeyPointsAndDesp( frame1, detector, descriptor );
    computeKeyPointsAndDesp( frame2, detector, descriptor );

    // 求解pnp
    RESULT_OF_PNP result = estimateMotion( frame1, frame2, camera ,goodMatchThreshold);
    cout<<"PnP result:"<<endl<<result.rvec<<endl<<result.tvec<<endl;

    // 处理result,将旋转向量转化为旋转矩阵,将平移向量和旋转矩阵转换成变换矩阵
    Eigen::Isometry3d T = cvMat2Eigen(result.rvec,result.tvec);

    // 转换点云
    PointCloud::Ptr cloud1 = image2PointCloud( frame1.rgb, frame1.depth, camera );
    // 合并点云
    PointCloud::Ptr output = joinPointCloud(cloud1,frame2,T,camera,gridsize);
    pcl::io::savePCDFile("data/result.pcd", *output);
    cout<<"Final result saved."<<endl;

    pcl::visualization::CloudViewer viewer( "viewer" );
    viewer.showCloud( output );
    while( !viewer.wasStopped() )
    {
        
    }
    return 0;
}
