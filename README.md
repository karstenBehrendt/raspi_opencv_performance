##### What to expect using a Raspberry Pi with OpenCV for analyzing images from a webcam. 

######The short answer is, you can do real time computer vision with OpenCV for very low resolution (320x240) images and with (more than likely) less then 10fps. You may want to look into the Pi's gpu as it offers way more computing power than its cpu. You can find detailed results below. 


I wanted to check what kind of computer vision tasks can be done on a Raspberry Pi in real-time. I tested OpenCV with a standard/cheap USB camera (Logitech C270) and the Raspberry Pi Camera Module (specifically the RaspiCam Noir, but that does not make a difference). 

First of all, getting the RaspiCam to work with OpenCV is possible in two ways. 1) Get a c/cpp script off github and use it to capture the images (replaces OpenCVs VideoCapture), or 2) get a RaspiCam driver for Video4Linux2 (linux-projects.org, not mine, not affiliated), which is way more convenient. This will give you a /dev/video* device. After installing the driver, the camera module pretty much works like it should. The frame grabbing speed of the USB camera, the custom VideoCapture and the RaspiCam driver pretty much do not differ at all. 

Now about the performance: I tested this script on Raspbian 3.12.18, with medium and without overclocking on May 14, 2014 on a standard Raspberry Pi Model B. Optimizations are set to -O3 and Wl,-O3 which greatly influence the performance. 

```
-------------------------------------------------------------------
Just capturing frames from the webcams, medium overclocking (Pi@900MHz). 
   Testing frame rate for RaspiCam: 
      30.3 frames per second with an image size of 320x240
      22.22 frames per second with an image size of 480x360
      12.66 frames per second with an image size of 640x480
      5.05 frames per second with an image size of 960x720
      4.85 frames per second with an image size of 1280x960
      4.83 frames per second with an image size of 1600x1200
   Testing frame rate for Logitech C270: 
      29.39 frames per second with an image size of 320x240
      22.73 frames per second with an image size of 480x360
      9.09 frames per second with an image size of 640x480
      5.03 frames per second with an image size of 960x720
      4.85 frames per second with an image size of 1280x960


With some very basic operations on each image. 
(Convert to gray scale, dilate, erode, thresholding, canny and one loop over each pixel. )
   Testing frame rate for RaspiCam: 
      13.16 frames per second with an image size of 320x240
      6.41 frames per second with an image size of 480x360
      3.98 frames per second with an image size of 640x480
      1.98 frames per second with an image size of 960x720
      1.06 frames per second with an image size of 1280x960
      1.06 frames per second with an image size of 1600x1200
   Testing frame rate for Logitech C270: 
      13.89 frames per second with an image size of 320x240
      7.46 frames per second with an image size of 480x360
      4.44 frames per second with an image size of 640x480
      1.98 frames per second with an image size of 960x720
      1.06 frames per second with an image size of 1280x960

------------------------------------------------------------------
Same tests without overclocking (Pi@700MHz). 
Just capturing frames: 
   Testing frame rate for RaspiCam:
      15.15 frames per second with an image size of 320x240
      14.71 frames per second with an image size of 480x360
      8.77 frames per second with an image size of 640x480
      6.67 frames per second with an image size of 960x720
      4.03 frames per second with an image size of 1280x960
      4.02 frames per second with an image size of 1600x1200
   Testing frame rate for Logitech C270:
      14.93 frames per second with an image size of 320x240
      14.71 frames per second with an image size of 480x360
      9.26 frames per second with an image size of 640x480
      6.67 frames per second with an image size of 960x720
      4.05 frames per second with an image size of 1280x960

Basic operations: 	  
   Testing frame rate for RaspiCam:
      11.36 frames per second with an image size of 320x240
      6.02 frames per second with an image size of 480x360
      3.47 frames per second with an image size of 640x480
      1.65 frames per second with an image size of 960x720
      0.91 frames per second with an image size of 1280x960
      0.91 frames per second with an image size of 1600x1200
   Testing frame rate for Logitech C270:
      11.63 frames per second with an image size of 320x240
      5.99 frames per second with an image size of 480x360
      3.47 frames per second with an image size of 640x480
      1.65 frames per second with an image size of 960x720
      0.91 frames per second with an image size of 1280x960
```

2014-05-15, Karsten Behrendt

