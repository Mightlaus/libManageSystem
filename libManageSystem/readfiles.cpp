#include "readfiles.h"
void readcsv()
{
	// д�ļ�
	ofstream outFile;
	outFile.open("data.csv", ios::out); // ��ģʽ��ʡ��
	outFile << "name" << ',' << "age" << ',' << "hobby" << endl;
	outFile << "Mike" << ',' << 18 << ',' << "paiting" << endl;
	outFile << "Tom" << ',' << 25 << ',' << "football" << endl;
	outFile << "Jack" << ',' << 21 << ',' << "music" << endl;
	outFile.close();
}