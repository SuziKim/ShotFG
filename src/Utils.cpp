#include "Utils.hpp"

bool Utils::checkFolder(string path) {
	struct stat info;
	if( stat(path.c_str(),&info) == 0 && (info.st_mode & S_IFDIR)) {
		return true;
	}
	return false;	
}

bool Utils::checkFile(string name) {
  if(FILE *file = fopen(name.c_str(),"r")) {
		fclose(file);
		return true;
	}
	return false;
}

bool Utils::checkOutputFile(string name) {
	if(FILE *file = fopen(name.c_str(),"w")) {
		fclose(file);
		return true;
	}
	return false;	
}

vector< pair<int,int> > Utils::normalizePairs(vector< pair<int,int> > pairs, int val) {
	for(int i = 0; i < pairs.size(); i++) {
		pairs[i].first = pairs[i].first + val;
		pairs[i].second = pairs[i].second + val;
	}
	return pairs;
}

int Utils::calculateNumberOfDigits(int number) {
	int count = 2;
	int temp = 10;
	
	while(true) {
		if(number <= temp) {
			return count;
		}
		count++;
		temp = temp * 10;
	}
}

void Utils::saveFrame(Mat frame, int format, int number, string basePath) {
	ostringstream fullPath;
	fullPath << basePath;
	if(format == 1) {
		fullPath << number << ".jpg";
	} else {
		if(format == 2) {
			fullPath << number << ".png";
		}
	}
	imwrite(fullPath.str().c_str(), frame);
}

vector<string> Utils::generateShotFoldersPath(string rootFolder, int number) {
	int leadingZeroes = Utils::calculateNumberOfDigits(number);
	vector<string> folders;
	
	for(int i = 1; i <= number; i++) {
		ostringstream fullPath;		
		fullPath << rootFolder << setfill('0') << setw(leadingZeroes) << i << "/";
		folders.push_back(fullPath.str());
	}
	
	return folders;
}

vector< pair<int,int> > Utils::parseCSV(string filePath) {
	ifstream file(filePath.c_str());
	string line;
	string token;
	vector< pair<int,int> > ret;
	
	if(file.is_open()) {
		while(getline(file,line)) {
			istringstream str(line);
			vector<int> temp;
			while(getline(str,token,',')) {
				temp.push_back(atoi(token.c_str()));
			}
			ret.push_back(make_pair(temp[0],temp[1]));
			temp.clear();
		}
	}	
    file.close();
	return ret;
}