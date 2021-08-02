#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


Mat src; Mat dst;
int kernelSize;

static void on_trackbar( int, void* )
{
    if(cvRound(kernelSize) == 0){
        cout << "Invalid Kernel Size: 0. Min kernel size should be 1." << endl;
        kernelSize = 1;
    }
    else if (cvRound(kernelSize) % 2 == 0) {
        kernelSize -= 1;
    }
    cout << "KernelSize is " << kernelSize << endl;
    medianBlur(src, dst, kernelSize);
    imshow("Median Filter", dst);
    
}

void applyMedianFilter(Mat image){
    Mat dst;
    //![blur]
    //    int kernelSize = 0;
    cout << "Enter the kernel size (it must be odd and greater than 1):" << endl;
    //    cin >> kernelSize;
    //![blur]
    
    const int alpha_slider_max = 100;
    kernelSize = 1;
    namedWindow("Median Filter", WINDOW_AUTOSIZE); // Create Window
    imshow("Median Filter", src);
    createTrackbar( "Median Trackbar", "Median Filter", &kernelSize, alpha_slider_max, on_trackbar );
    
    //    imshow("Median Filter", dst);
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
    
    /// Load the source image
    const char* filename = argc >=2 ? argv[1] : "/Users/orkhanbayramli/Desktop/the-last-castle/computer-vision/lab-2/lab2_data_code/data/overexposed.jpg";
    
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

