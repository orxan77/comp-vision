#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


Mat src; Mat dst;

void applyMedianFilter(Mat image){
    Mat dst;
    //![blur]
    int kernelSize = 0;
    cout << "Enter the kernel size (it must be odd and greater than 1):" << endl;
    cin >> kernelSize;
    medianBlur( src, dst, kernelSize);
    //![blur]
    imshow("Median Filter", dst);
    waitKey();
}

void applyGaussianBlur(Mat image){
    
    Mat dst;
    int kernelSize = 0;
    double sigmaSize = 0.0;
    
    cout << "Enter the kernel size (must be positive and odd):" << endl;
    cin >> kernelSize;
    
    cout << "Enter the sigma size (must be positive):" << endl;
    cin >> sigmaSize;
    
    GaussianBlur( image, dst, Size( kernelSize, kernelSize ), sigmaSize, sigmaSize );
   
    imshow("Gaussian Blur", dst);
    waitKey();

}

void applyBilateralFilter(Mat image) {
    Mat dst;
    
    int kernelSize = 5;
    double sigmaColor = 0.0;
    double sigmaSpace = 0.0;
    
    cout << "Enter the sigma color:" << endl;
    cin >> sigmaColor;
    
    cout << "Enter the sigma space size:" << endl;
    cin >> sigmaSpace;
    
    bilateralFilter (image, dst, kernelSize, sigmaColor, sigmaSpace);
    
    imshow("Bilateral Filter", dst);
    waitKey();
}

/**
 * function main
 */
int main( int argc, char ** argv )
{
    namedWindow( window_name, WINDOW_AUTOSIZE );
    
    /// Load the source image
    const char* filename = argc >=2 ? argv[1] : "/Users/orkhanbayramli/Desktop/portello.png";
    
    src = imread( samples::findFile( filename ), IMREAD_COLOR );
    if (src.empty())
    {
        printf(" Error opening image\n");
        printf(" Usage:\n %s [image_name-- default ] \n", argv[0]);
        return EXIT_FAILURE;
    }
    

    string filterName = "";
    cout << "Enter filter name. (m - madianFilter, g - GaussianBlur, b - bilateralFilter)" << endl;
    cin >> filterName;
    
    if (filterName == "m") {
        cout << "You entered medianfilter" << endl;
        applyMedianFilter(src);
    } else if (filterName == "g") {
        cout << "You entered Gaussian Filter" << endl;
        applyGaussianBlur(src);
    } else if (filterName == "b"){
        cout << "You entered Bilateral Filter" << endl;
        applyBilateralFilter(src);
    }
    
    return 0;
}
