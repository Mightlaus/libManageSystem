#include "read-data.h"

void write_csv(int n, int m, string* s) // ����һ����άstring���飬����֪����������
{
	// ������д��csv�ļ�
	fstream outFile;
	outFile.open("data.csv", ios::out);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			outFile << s[i * m + j] << ',';
		}
		outFile << endl;
	}


	outFile.close();
}

void read_csv()
{
	// ��csv�ļ��ж�ȡ����
	fstream inFile;
	inFile.open("librarydata_books.csv",ios::in);
	
	string bookInfo[9];
	vector<string*> data;
	string s;
	getline(inFile, s);
	for (int i=0;i<4;i++)
	{
		for (int j = 0; j < 8; j++)
		{
			getline(inFile, bookInfo[j], ',');
		}
		getline(inFile, bookInfo[8]);
		data.push_back(bookInfo);
		for (int k = 0; k < 9; k++)
		{
			cout << bookInfo[k] << "   ";
		}
		cout << endl;
	}

	inFile.close();
}