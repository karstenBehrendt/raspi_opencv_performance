all: 
	g++ -pipe -O3 -Wall -I/usr/local/include/opencv2 main.cpp -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lopencv_nonfree
	
remove: 
	rm a.out