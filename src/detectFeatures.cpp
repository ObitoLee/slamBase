/*************************************************************************
    > File Name: detectFeatures.cpp
    > Author: xiang gao
    > Mail: gaoxiang12@mails.tsinghua.edu.cn
    > 特征提取与匹配
    > Created Time: 2015年07月18日 星期六 16时00分21秒
 ************************************************************************/

#include<iostream>
#include "slamBase.h"

using namespace std;
using namespace cv;

static ParameterReader cfg;
CAMERA_INTRINSIC_PARAMETERS C={	atof( cfg.getData( "camera.cx" ).c_str() ),
								atof( cfg.getData( "camera.cy" ).c_str() ),
								atof( cfg.getData( "camera.fx" ).c_str() ),
								atof( cfg.getData( "camera.fy" ).c_str() ),
								atof( cfg.getData( "camera.scale" ).c_str() )};
double goodMatchThreshold = atof( cfg.getData( "good_match_threshold" ).c_str() );
string detector = cfg.getData("detector");
string descriptor = cfg.getData("descriptor");

int main()
{
    // 声明并从data文件夹里读取两个rgb与深度图
	FRAME frame1,frame2;
    frame1.rgb = imread( "./data/rgb1.png");
    frame2.rgb = imread( "./data/rgb2.png");
    frame1.depth = imread( "./data/depth1.png", -1);
    frame2.depth = imread( "./data/depth2.png", -1);

	computeKeyPointsAndDesp(frame1,detector,descriptor);
    computeKeyPointsAndDesp(frame2,detector,descriptor);

	RESULT_OF_PNP result = estimateMotion(frame1,frame2,C,goodMatchThreshold);

    cout<<"inliers: "<<result.inliers<<endl
    	<<"R= "<<result.rvec<<endl
    	<<"t= "<<result.tvec<<endl;

    imshow("inlier matches",result.imgMatches);
    waitKey(0);

    return 0;
}
