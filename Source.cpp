//#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main(int argc, char** argv){
//	if (argc != 2){
//		cout<<"Usage: pass imagename to command line"<<endl;
//		return -1;
//		}
//	Mat image;
//	std::string imageName( argv[1] );
//	image = imread(imageName,1);
//
//	if (!image.data){
//		cout<<"can't find image"<<endl;
//		}
//	//namedWindow( "Display window", WINDOW_AUTOSIZE );
//	imshow("Emiriyatan",image);
//
//    Mat samples(image.rows * image.cols, 3, CV_32F);
//    for( int y = 0; y < image.rows; y++ )
//      for( int x = 0; x < image.cols; x++ )
//        for( int z = 0; z < 3; z++)
//          samples.at<float>(y + x*image.rows, z) = image.at<Vec3b>(y,x)[z];
//
//	//cout<<samples(0)<<endl;
//
//    int clusterCount = 3;
//    Mat labels;
//    int attempts = 3;
//    Mat centers;
//    kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 1000, 0.001), attempts, KMEANS_PP_CENTERS, centers );
//
//
//    Mat new_image( image.size(), image.type() );
//    for( int y = 0; y < image.rows; y++ )
//      for( int x = 0; x < image.cols; x++ )
//    { 
//      int cluster_idx = labels.at<int>(y + x*image.rows,0);
//      new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
//      new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
//      new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
//    }
//	imshow( "clustered image", new_image );
//
//
//	waitKey(0);
//	return 0;
//	}