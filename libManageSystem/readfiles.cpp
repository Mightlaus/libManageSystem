#include "readfiles.h"
void readcsv()
{
	// 写文件
	ofstream outFile;
	outFile.open("data.csv", ios::out); // 打开模式可省略
	outFile << "name" << ',' << "age" << ',' << "hobby" << endl;
	outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;
	outFile << "Tom" << ',' << 25 << ',' << "football" << endl;
	outFile << "Jack" << ',' << 21 << ',' << "music" << endl;
	outFile.close();
}