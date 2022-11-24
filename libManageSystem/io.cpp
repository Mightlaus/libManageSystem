#include "io.h"

void io::write_csv(int n, int m, string* s) // ����һ����άstring���飬����֪����������
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

void io::add_user_from_file(Repo* repo, int n)
{
	fstream inFile;
	inFile.open("users.csv", ios::in);
	for (int i = 0; i < n; i++)
	{
		// dientity name key
		string name, identity, key;
		getline(inFile, identity, ',');
		getline(inFile, name, ',');
		getline(inFile, key);
		repo->users.addUser(identity[0], name, key);
	}
}

vector<string*> io::read_csv(int n)
{
	// ��csv�ļ��ж�ȡ����
	fstream inFile;
	inFile.open("expand.csv", ios::in);
	vector<string*> data;
	string tmp;
	getline(inFile, tmp);
	for (int i = 0; i < n; i++)
	{
		string* bookInfo = new string[9];
		for (int j = 0; j < 8; j++)
		{
			getline(inFile, bookInfo[j], ',');
		}
		getline(inFile, tmp, '&');
		tmp.erase(tmp.end() - 1);
		bookInfo[8] = tmp;
		data.push_back(bookInfo);
	}

	inFile.close();
	return data;
}