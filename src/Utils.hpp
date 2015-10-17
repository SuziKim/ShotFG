#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iomanip>

using namespace std;
using namespace cv;

class Utils {
	public:
		static bool checkFile(string name);
		static bool checkOutputFile(string name);
		static vector< pair<int,int> > parseCSV(string filePath);
		static vector< pair<int,int> > normalizePairs(vector< pair<int,int> > pairs, int val);
		static bool checkFolder(string path);
		static int calculateNumberOfDigits(int number);
		static vector<string> generateShotFoldersPath(string rootFolder, int number);
		static void saveFrame(Mat frame, int format, int number, string basePath);
};