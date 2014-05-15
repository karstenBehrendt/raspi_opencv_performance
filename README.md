I wanted to see if I could do real time, high resolution, multiple frames per second image processing on the raspberry pi with either the raspi camera module or a decent usb webcam. First I had to check, whether I could do this with my raspberry pi and opencv or not. 

First of all, getting the RaspiCam to work with OpenCV is possible in two ways. 1) Get a c/cpp script off github and use it to capture the images, or 2) raspicam driver for uv4l, which is way more convenient. This will give you a /dev/video* device. After installing the driver, the camera module pretty much works like it should. 

Now about the performance: 
I tested this script on Raspbian 3.12.18, with medium overclocking to 900Mhz on May 11, 2014 on a standard Raspberry Pi. 

 