# Introduction
ShotFG (**S**hot **F**rame **G**enerator) is an utility application which generate the shot frames for a given video 

# Requirements
*   A C++ compiler, like g++
*   A functional OpenCV installation (version 2.4.x and above)
*   An appropriate set of CODECs

# Parameters
1.  The input video which frames will be extracted.
2.  A CSV file with the first and last frame of each shot.
3.  The absolute output folder path (it will be created).
4.  (Optional) JPG or PNG output frame format.
5.  (Optional) The vertical resolution of the output frames.
6.  (Optional) The horizontal resolution of the output frames.

# Output
The application will create the output folder and a sequential set of folders, one for each shot. 
Each folder will contain the frames of the specified shot (the first and last frame included) with the provided configuration 


By default, if the output frame format or resolution is not specified, each frame will be generated at native resolution in JPG format (lossy compression).


# Examples
	$ ./FAST video.avi shots.csv /home/user/outputfolder/
	$ ./FAST video.avi shots.csv /home/user/outputfolder/ PNG
	$ ./FAST video.avi shots.csv /home/user/outputfolder/ PNG 640 480
	$ cat shots.csv
		1,240
		241,500
		515,678
		679,800
		801,899

# Authors
ShotFG was developed by Tiago H. Trojahn under the coordination of Rudinei Goularte



