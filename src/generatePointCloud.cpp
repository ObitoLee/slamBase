#include"slamBase.h"

// 相机内参
CAMERA_INTRINSIC_PARAMETERS camera={325.5,253.5,518.0,519.0,1000};

// 主函数 
int main( int argc, char** argv )
{
    Mat rgb, depth;
   	rgb = imread( "./data/rgb.png" );// rgb 图像是8UC3的彩色图像
    depth = imread( "./data/depth.png", -1 );// depth 是16UC1的单通道图像，注意flags设置-1,表示读取原始数据不做任何修改

    // 点云变量
    // 使用智能指针，创建一个空点云。这种指针用完会自动释放。
    PointCloud::Ptr cloud ( new PointCloud );
	cloud = image2PointCloud(rgb,depth,camera);

    cout << "point cloud size = "<< cloud->points.size() << endl;
    pcl::io::savePCDFile( "./data/pointcloud.pcd", *cloud );
    // 清除数据并退出
    cloud->points.clear();
    cout << "Point cloud saved." << endl;
    return 0;
}
