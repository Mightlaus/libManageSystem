#include "io.h"
#include <Windows.h>

void io::write_csv(int n, int m, string* s) // 传入一个二维string数组，并告知行数和列数
{
	// 将数据写入csv文件
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

void io::add_user_from_file(Repo* repo)
{
	fstream inFile;
	inFile.open("users.csv", ios::in);
	while(1)
	{
		// dientity, name, key, exist
		string name, identity, key, exist;
		getline(inFile, identity, ',');
		if (identity.empty())
		{
			break;
		}
		getline(inFile, name, ',');
		getline(inFile, key, ',');
		getline(inFile, exist);
		repo->users.addUser(identity[0], name, key, stoi(exist));
	}
}

void io::save_user_to_file(Repo* repo)
{
	// 将数据写入csv文件
	fstream outFile;
	outFile.open("users.csv", ios::out);

	//student
	for (int i = 0; i < repo->users.p_student_repo->size(); i++)
	{
		string name, identity, key;
		int exist;
		name = repo->users.p_student_repo->at(i).user_name;
		identity = repo->users.p_student_repo->at(i).identity;
		key = repo->users.p_student_repo->at(i).key;
		exist = repo->users.p_student_repo->at(i).exist;
		outFile << identity << ',';
		outFile << name << ',';
		outFile << key << ',';
		outFile << exist;
		outFile << endl;
	}

	//admin
	for (int i = 0; i < repo->users.p_admin_repo->size(); i++)
	{
		string name, identity, key;
		int exist;
		name = repo->users.p_admin_repo->at(i).user_name;
		identity = repo->users.p_admin_repo->at(i).identity;
		key = repo->users.p_admin_repo->at(i).key;
		exist = repo->users.p_admin_repo->at(i).exist;
		outFile << identity << ',';
		outFile << name << ',';
		outFile << key << ',';
		outFile << exist;
		outFile << endl;
	}

	//visitor
	for (int i = 0; i < repo->users.p_visitor_repo->size(); i++)
	{
		string name, identity, key;
		int exist;
		name = repo->users.p_visitor_repo->at(i).user_name;
		identity = repo->users.p_visitor_repo->at(i).identity;
		key = repo->users.p_visitor_repo->at(i).key;
		exist = repo->users.p_visitor_repo->at(i).exist;
		outFile << identity << ',';
		outFile << name << ',';
		outFile << key << ',';
		outFile << exist;
		outFile << endl;
	}

	outFile.close();
}

void io::welcome()
{
	io::full_screen();
	fstream inFile;
	inFile.open("welcome.txt", ios::in);
	while (1)
	{
		string curLine;
		getline(inFile, curLine);
		if (curLine.empty())
		{
			break;
		}
		cout << curLine << endl;
	}
}

void io::bye()
{
	system("cls");
	system("mode con cols=75 lines=35");
	fstream inFile;
	inFile.open("bye.txt", ios::in);
	while (1)
	{
		string curLine;
		getline(inFile, curLine);
		if (curLine.empty())
		{
			break;
		}
		cout << curLine << endl;
	}
	Sleep(2500);
}

void io::full_screen()
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
	/* 设置窗口信息 最大化  */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE));
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

void io::click_back()
{
	string buffer;
	cout << "\n按任意键返回...";
	getline(cin, buffer);
	cin.ignore(20, '\n');
	system("cls");
}


vector<string*> io::read_csv(int n)
{
	// 从csv文件中读取数据
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