#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;


void showHistograms(vector<Mat> bgr_planes, string name){
    
    Mat image;
    
    //! [Establish the number of bins]
    int histSize = 256;
    //! [Establish the number of bins]
    
    //! [Set the ranges ( for B,G,R) )]
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    //! [Set the ranges ( for B,G,R) )]
    
    //! [Set histogram param]
    bool uniform = true, accumulate = false;
    //! [Set histogram param]
    
    //! [Compute the histograms]
    Mat b_hist, g_hist, r_hist;
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
    //! [Compute the histograms]
    
    //! [Draw the histograms for B, G and R]
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    
    Mat histBlue( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    Mat histGreen( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    Mat histRed( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    
    //! [Draw the histograms for B, G and R]
    
    //! [Normalize the result to ( 0, histImage.rows )]
    normalize(b_hist, b_hist, 0, histBlue.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histGreen.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histRed.rows, NORM_MINMAX, -1, Mat() );
    //! [Normalize the result to ( 0, histImage.rows )]
    
    //! [Draw for each channel]
    for( int i = 1; i < histSize; i++ )
    {
        line( histBlue, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
             Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
             Scalar( 255, 0, 0), 2, 8, 0  );
        line( histGreen, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
             Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
             Scalar( 0, 255, 0), 2, 8, 0  );
        line( histRed, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
             Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
             Scalar( 0, 0, 255), 2, 8, 0  );
    }
    //! [Draw for each channel]
    
    imshow("Blue Histogram", histBlue);
    imshow("Green Histogram", histGreen);
    imshow("Red Histogram", histRed);
    
    merge(bgr_planes, image);
    imshow(name, image);
    
    cout << "FUNCTION FINISHED";
    
    waitKey();
    destroyAllWindows();
}



/**
 * @function main
 */
int main(int argc, char** argv)
{
    //! [Load image]
    CommandLineParser parser( argc, argv, "{@input | /Users/orkhanbayramli/Desktop/countryside.jpg | input image}" );
    Mat src = imread( samples::findFile( parser.get<String>( "@input" ) ), IMREAD_COLOR );
    if( src.empty() )
    {
        return EXIT_FAILURE;
    }
    //! [Load image]
    
    //! [Separate the image in 3 places ( B, G and R )]
    vector<Mat> bgr_planes;
    split( src, bgr_planes );
    //! [Separate the image in 3 places ( B, G and R )]
    
    //! [Separate the image in 3 places ( B, G and R )]
    vector<Mat> equalized_bgr_planes;
    split( src, equalized_bgr_planes );
    //! [Separate the image in 3 places ( B, G and R )]
    
    //! [Equalize the B, G, R channels of the image]
    equalizeHist(equalized_bgr_planes[0], equalized_bgr_planes[0]);
    equalizeHist(equalized_bgr_planes[1], equalized_bgr_planes[1]);
    equalizeHist(equalized_bgr_planes[2], equalized_bgr_planes[2]);
    //! [Equalize the B, G, R channels of the image]

    
    showHistograms(bgr_planes, "original image");
    showHistograms(equalized_bgr_planes, "equalized image");
    
    return EXIT_SUCCESS;
}
