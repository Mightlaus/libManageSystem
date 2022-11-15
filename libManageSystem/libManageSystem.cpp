﻿#include "head.h"
#include "readfiles.h"
int main()
{
	cout << "********************菜单********************" << endl;
	cout << "1.管理员模式" << endl;
	cout << "2.用户模式" << endl;
	cout << "3.退出" << endl;
	readcsv();
	while (1)
	{
		cout << "请输入您的选择：";
		string option;
		cin >> option;
		if (option == "1")
		{
			cout << "请输入您的管理员账号和密码（默认账号为学号/教师编号，默认密码为123456）："
				<< endl << "账号：";
			string account;
			cin >> account;
			cout << "密码：";
			string password;
			cin >> password;


			cout << "欢迎您！管理员" << account << endl;
		}
		else if (option == "2")
		{
			cout << "请输入您的用户账号和密码（默认账号为学号/教师编号，默认密码为123456）："
				<< endl << "账号：";
			string account;
			cin >> account;
			cout << "密码：";
			string password;
			cin >> password;


			cout << "欢迎您！用户" << account << endl;
		}
		else if (option == "3")
		{
			return 0;
		}
		else
		{
			cout << "输入格式非法，请重试！" << endl;
		}
	}
	
	return 0;
}