/**
	This basic script's purpose is to check for what purposes I can use the 
	raspberry pi with its camera module or some other simple camera. 
	
	It shows how many frames a seconds the pi can grab from the camera, 
	when using OpenCV. Results will be posted in the README. 

	I hope, that since I did it here, you don't have to. 
	
	Karsten Behrendt, 2014-05-11


*/


#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <time.h>
#include <cmath>

using namespace std;
using namespace cv;


/**
	Starts webcam on specified camIndex and grabs frames with a specified resolution. 
	If enabled, it also performs some small actions on each image. 
	It then returns how many frames the pi is able to process given that resolution. 

*/
double getFPS(int camIndex, int width, int height, int numFrames, bool extraWork)
{
	VideoCapture cap(camIndex); 

	if(cap.set(CV_CAP_PROP_FRAME_WIDTH, width))
	{
		cout << "could not set width" << endl; 
	}	
	if(cap.set(CV_CAP_PROP_FRAME_HEIGHT, height)) 
	{
		cout << "could not set heigh" << endl; 
	}
	
	if(!cap.isOpened())
	{
		cout << "Could not open camera " << camIndex << endl; 
		return -1; 
	}
	
	Mat frame; Mat binary; Mat gray; Mat canny; 
	time_t start, end; 
	
	time(&start); 
	for(int i = 0; i < numFrames; i++)
	{
		cap >> frame; 
	
		if(waitKey(0) >= 0)
		{
			break; 
		}
		
		if(extraWork)
		{ 
			// Yes, this can be done smarter, faster, ... 
			//this is supposed to represent some easy image manipulations
			cvtColor(frame, gray, CV_RGB2GRAY); 
			threshold(gray, binary, 0.0, 255.0, CV_THRESH_BINARY | CV_THRESH_OTSU); 
			Mat rect = getStructuringElement(MORPH_RECT, Size(5, 5)); 
			erode(binary, binary, rect); 
			dilate(binary, binary, rect); 
			Canny(binary, canny, 50, 100);
			
			for(int k = 0; k < frame.rows; k++)
			{
				for(int l = 0; l < frame.cols; l++)
				{
					for(int m = 0; m <3; m++)
					{
						frame.data[frame.step[0] * k + frame.step[1] * l + (k+l+m) % 3] = 255; 
					}
				}
			}
			
		}
		
	}
	time(&end); 
	
	return numFrames / (double)(end-start); 
}



/**
	Tests how many frames the pi can grab for various resolutions and in my
	case, on two different cameras. 
*/
int main()
{
	int raspicamIndex = 1;
	int baseWidth = 320; 
	int baseHeight = 240; 
	int numFrames = 1000; 
	bool extraWork = true; 
	
	double currentFrames; 
	string tab = "   "; 	
	
	cout << "Raspberry pi opencv webcam performance test: " << endl; 
	cout << "Frames per second are averaged over " << numFrames << " captured images." << endl; 
	for(int j=0; j<2; j++)
	{
		if(j != raspicamIndex)
		{
			cout << tab << "Testing frame rate for Logitech C270: " << endl; 
		}
		else
		{
			cout << tab << "Testing frame rate for RaspiCam: " << endl; 
		}
		
		for(int i=1; i<4; i++)
		{
			if( j != raspicamIndex && (i > 4))
			{
				continue; 
			}

			currentFrames = round(getFPS(0, baseWidth * i, baseHeight * i, numFrames, extraWork) * 100) / 100.0; 
			cout << tab << tab << currentFrames << " frames per second with an image size of " << baseWidth*i << "x" << baseHeight*i << endl; 
			if( i == 1)
			{
				currentFrames = round(getFPS(0, baseWidth / 2 * 3, baseHeight / 2 * 3, numFrames, extraWork) * 100) / 100.0; 
				cout << tab << tab << currentFrames << " frames per second with an image size of " << baseWidth / 2 * 3 << "x" << baseHeight / 2 * 3 << endl; 			
			}
		}
	}
		
    return 0;
	
}

