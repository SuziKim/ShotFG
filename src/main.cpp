#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Utils.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
	if(argc < 4 || argc > 7) {
		cout << "Incorrect parameter count." << endl;
		cout << "Please, use './ShotFG <videoFilePath> <shotSegmentationFile.csv> <AbsoluteOutputFolderPath> [<JPG|PNG> <VerticalResolution> <HorizontalResolution>]'" << endl;
		return 1;
	}	
	
	string videoPath = string(argv[1]);
	if(!Utils::checkFile(videoPath)) {
		cout << "The videoFilePath seems to be invalid or cannot be read" << endl;
		return 1;
	}
	
	string shotSegmentation = string(argv[2]);
	if(!Utils::checkFile(videoPath)) {
		cout << "The shotSegmentationFile seems to be invalid or cannot be read" << endl;
		return 1;
	}
	
	string outputFolder = string(argv[3]);
	if(outputFolder.back() != '/') {
		outputFolder =  outputFolder + '/';
	}
	if(!Utils::checkFolder(outputFolder)) {
		cout << "The outputFolderPath seems to be invalid or cannot be written (it is a folder? is the path really ABSOLUTE?)" << endl;
		return 1;
	}
	
	int fileFormat = 1;
	if(argc >= 5) {
		try {
			string format = string(argv[4]);
			if(format == "JPG" || format == "jpg") {
				fileFormat = 1;
			} else {
				if(format == "PNG" || format == "png") {
					fileFormat = 2;
				} else {
					throw runtime_error("Invalid option!");
				}
			}
		} catch (exception& e) {
			cout << "Invalid image format! Trying to use JPG..." << endl;
			fileFormat = 1;
		}
	}
	
	if(argc == 6) {
		cout << "Error! You must define both VerticalResolution and HorizontalResolution parameters." << endl;
		return 1;
	}
	
	int verticalRes = -1;
	int horizontalRes = -1;
	if(argc == 7) {
		try{
			if(stoi(string(argv[5])) > 0 && stoi(string(argv[6])) > 0) {
				verticalRes = stoi(string(argv[5]));
				horizontalRes = stoi(string(argv[6]));
			} else {
				throw runtime_error("Invalid value!");
			}
		} catch (exception& e) {
			cout << "At least one of the specified resolutions value is invalid. Ignoring." << endl;
			verticalRes = -1;
			horizontalRes = -1;
		}		
	}
	/*
	Get the shots.
	*/
	vector< pair<int,int> > shots = Utils::normalizePairs(Utils::parseCSV(shotSegmentation),-1);
	/*
	Generate and create the containing folders path.
	*/
	vector<string> folders = Utils::generateShotFoldersPath(outputFolder, shots.size());	
	for(int i = 0; i < folders.size(); i++) {
		mkdir(folders[i].c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}


	Mat frame;
	VideoCapture capture(videoPath);
	Size size(horizontalRes, verticalRes);
		
	for(int i = 0; capture.read(frame); i++) {
		if(verticalRes > 0) {
			resize(frame,frame,size);
		}
				
		if(i >= shots[shots.size()-1].second){
			break;
		}			
		/*
			For every frame, check the corresponding shot.
			
			TODO: optimize that!
		*/
		for(int s = 0; s < shots.size(); s++) {
			if(i < shots[s].first) {				
				break;
			}
			if(shots[s].first <= i && i <= shots[s].second) {
				Utils::saveFrame(frame, fileFormat, i+1, folders[s]);
			}
		}		
	}
	frame.release();
	capture.release();
	return 0;
}